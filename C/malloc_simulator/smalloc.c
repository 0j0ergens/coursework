#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "smalloc.h"
void *heap_space;
void *first_pointer; 
void *FINAL_POINTER;
struct header {
    int size;
    int is_alloc;
    struct header* prev;
    struct header* next;
}; 
struct header *h_first;
int my_init(int size_of_region) {
    int size; 
    int fd = open("/dev/zero", O_RDWR);
    if(size_of_region % 4096 == 0){
        size = size_of_region; 
    }
    else{
        size = 4096 * (size_of_region / 4096 + 1);
    }
    heap_space = mmap(NULL, size, PROT_READ | PROT_WRITE,
                      MAP_ANONYMOUS | MAP_PRIVATE, fd, 0);
    if (heap_space == MAP_FAILED) {
        return 1;
    }
    h_first = (struct header*)heap_space;
    first_pointer = heap_space; 
    h_first->size = size;
    h_first->is_alloc = 0;
    h_first->prev = NULL;
    h_first->next = NULL;
 
    return 0;
}
void *print_hstruct(struct header *header){
    printf("pointer: %p\nsize: %d\nis_alloc: %d\n\n", (void*)header, header->size, header->is_alloc);
}
void print_hlist(){
    struct header* h_cur = h_first; 
    int cnt = 0;
    while(h_cur){
        printf("H ELEMENT %d\n", cnt);
        print_hstruct(h_cur);
        h_cur = h_cur->next; 
        cnt +=1;
        if (h_cur == NULL) return; 
    }
}
int get_hops(void *hdr) {
    int hop = 0;
    struct header* h_cur = h_first;
    while ((void*)h_cur != hdr) {
        if (h_cur->next == NULL) {
            return -1; 
        }
        if (!h_cur->is_alloc) {
            hop++; 
        }
        h_cur = h_cur->next;
    }
    return hop;
}
void *smalloc(int size_of_payload, Malloc_Status *status){
    int p_size; 
    int offset = 0; 
    if(size_of_payload %8 == 0){
        p_size = size_of_payload;
    }
    else{
        p_size = 8 * (size_of_payload / 8 + 1); 
    }
    int block_size = p_size + 24; 
    struct header *h_cur = (struct header *)h_first; 
    struct header *cur_head = (struct header *)h_first; 
    while(cur_head->size < p_size || cur_head->is_alloc == 1){
        cur_head = cur_head->next; 
        if (cur_head == NULL){
            status->success = 0; 
            status->payload_offset = -1; 
            status->hops = -1; 
            return NULL; 
        }
    }
    if (cur_head->size > block_size) {
        struct header *new_free = (struct header *)((void *)cur_head + block_size);
        new_free->is_alloc = 0;
        cur_head->is_alloc = 1; 
        new_free->size = cur_head->size - block_size; 
        cur_head->size = block_size; 
        new_free->next = cur_head->next; 
        new_free->prev = cur_head; 
        if (cur_head->next != NULL) {
            cur_head->next->prev = new_free;
        }
        cur_head->next = new_free; 
        offset = (void *)cur_head - heap_space; 
    }
    if(cur_head->size == block_size){
        cur_head->is_alloc = 1; 
        offset = (void *)cur_head - heap_space; 
    }
    status->payload_offset = offset + 24; 
    status->success = 1; 
    status->hops = get_hops(cur_head);
    /*    print_hlist(); 
    */
    return (void *)((void *)cur_head + 24);
}
void merge_hlist() {
    struct header *cur = h_first;
    while (cur != NULL && cur->next != NULL) {
        // printf("&&&&&&&&&&&&&&&&&&&&&&%p\n", (void*)cur);
        if (cur->is_alloc == 0 && cur->next->is_alloc == 0) {
            //  printf("----------------------\n";
            cur->size += cur->next->size;
            cur->next = cur->next->next;
        } else {
            cur = cur->next;
        }
    }
}
void sfree(void *ptr){
    if(ptr == NULL) return;
    void *block_start = (void*)ptr - 24;
    struct header *cur_head = h_first;
    while(cur_head != NULL && (void *)cur_head != block_start){
        cur_head = cur_head->next;
    }
    if(cur_head != NULL){
        cur_head->is_alloc = 0;
        if((void*)cur_head + cur_head->size == (void*)(cur_head->next)) merge_hlist();
    }
}