#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/time.h> // for gettimeofday
#include "hw6.h"

int luminance(struct rgb c){
    return floor(0.2126*c.red + 0.7152*c.green + 0.0722*c.blue);
}

struct rgb grayscale(struct rgb c){
    int lum = luminance(c);
    c.red = lum; 
    c.green = lum; 
    c.blue = lum; 
    return c; 
}

int same_pixel(struct rgb pix1, struct rgb pix2){
    if (pix1.red != pix2.red || pix1.green != pix2.green || pix1.blue != pix2.blue)
        return 0; 
    return 1; 
}

int same_image(struct image *img1, struct image *img2){
    if(img1->width != img2->width || img1->height != img2->height) 
        return 0; 
    for(int i=0; i < img1->width*img1->height; i++){
        if (!same_pixel(img1->pixels[i], img2->pixels[i]))
            return 0; 
    }
    return 1; 
}

int is_grayscale(struct image *img){
    for(int i=0; i<img->width*img->height; i++){
        if(img->pixels[i].red != img->pixels[i].green \
        || img->pixels[i].red != img->pixels[i].blue) 
            return 0; 
    }
    return 1; 
}

struct image *read_image(FILE *f) {
    char ftype[3];
    int width, height;
    fscanf(f, "%s %d %d", ftype, &width, &height);
    struct image *new = malloc(sizeof(struct image)); 
    new->width = width; 
    fprintf(stderr, "WIDTH: %d\n", new->width);
    new->height = height; 
    fprintf(stderr, "HEIGHT: %d\n", new->height);
    int dim = new->width * new->height; 
    struct rgb *pixels = malloc(sizeof(struct rgb) * dim);

    for (int i = 0; i < 5; i++) {
        getc(f); 
    }

    struct rgb *new_pixel = malloc(sizeof(struct rgb)); 
    for (int i = 0; i < dim; i++) {
        if (!strcmp(ftype, "P3")) {
            int cur_int = 0;
            int color_val = 0;
            while (color_val < 3) {
                char cur_char = getc(f);
                if (cur_char == ' ' || cur_char == '\n') {
                    if (!color_val) new_pixel->red = cur_int;
                    else if (color_val == 1) new_pixel->green = cur_int;
                    else new_pixel->blue = cur_int;
                    cur_int = 0;
                    color_val++;
                } 
                else cur_int = cur_int * 10 + (cur_char - '0'); 
            }
            pixels[i] = *new_pixel; 
        } 
        else {
            new_pixel->red = getc(f);
            new_pixel->green = getc(f);
            new_pixel->blue = getc(f);
            pixels[i] = *new_pixel; 
        }
    }

    free(new_pixel);
    new->pixels = pixels;
    return new; 
}
void grayscale_seq(struct image *img){
    if (!is_grayscale(img)){

    for(int i=0; i<img->width*img->height; i++){
        img->pixels[i] = grayscale(img->pixels[i]); 
    }
  }
}

struct params{struct image *img; int start; int end;};
typedef struct params params; 

void *make_gray(void* arg){
    params *p = (params*)arg;
    struct image* img = p->img;
    int start = p->start; 
    int end = p->end; 
  
    for(int j=start; j < end; j++){
        img->pixels[j] = grayscale(img->pixels[j]);        
    }
    
    return; 
}


void grayscale_par(struct image *img, unsigned int n_threads) {
    pthread_t tids[n_threads];
    params* params_arr[n_threads];

    for (int i = 0; i < n_threads; i++) {
        params *p = malloc(sizeof(params));
        params_arr[i] = p;
        int seg = (img->width * img->height) / n_threads;
        int start = i * seg;
        int end = (i+1) * seg;
        if (i == n_threads - 1) end = img->width * img->height; 
        p->img = img;
        p->start = start;
        p->end = end;
        fprintf(stderr, "THREAD # %d START: %d END: %d \n", i, start, end);
        pthread_create(&tids[i], NULL, make_gray, p);
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(tids[i], NULL);
        free(params_arr[i]);
    }
}




