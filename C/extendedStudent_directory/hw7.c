#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <math.h> 
#include "hw7.h"

student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, char *lname, char
*fname){
student *new = malloc(sizeof(student));
new->ucid = ucid; 
new->cnet = strdup(cnet); 
new->ssn = ssn; 
new->lname = strdup(lname); 
new->fname = strdup(fname); 
new->next = NULL; 
return new; 
}

student *student_from_string(char *csv_row){
char* str_ucid = (char*)malloc(sizeof(char)*20); 
char *cnet = (char*)malloc(sizeof(char)*20); 
char* str_ssn = (char*)malloc(sizeof(char)*20); 
char *lname = (char*)malloc(sizeof(char)*30); 
char *fname = (char*)malloc(sizeof(char)*30); 
int var_num = 0; 
int var_idx = 0; 

for(int i=0; i<strlen(csv_row); i++){
    if (csv_row[i] == ','){ 
        if (!var_num) str_ucid[var_idx] = '\0'; 
        else if (var_num==1) cnet[var_idx] = '\0'; 
        else if (var_num==2) str_ssn[var_idx] = '\0'; 
        else if (var_num==3) lname[var_idx] = '\0'; 
        var_num ++; 
        var_idx = 0; 
        continue; 
    }

    if (!var_num) str_ucid[var_idx] = csv_row[i];;
    if (var_num==1) cnet[var_idx] = csv_row[i]; 
    if (var_num==2) str_ssn[var_idx] = csv_row[i];
    if (var_num==3) lname[var_idx] = csv_row[i];  
    if (var_num==4) fname[var_idx] = csv_row[i];  
    var_idx ++; 
    }

fname[var_idx] = '\0';
student *new = malloc(sizeof(student));
new->ucid = atoi(str_ucid); 
new->cnet = strdup(cnet); 
new->ssn = atoi(str_ssn); 
new->lname = strdup(lname); 
new->fname = strdup(fname); 
new->next = NULL; 
free(str_ucid);
free(cnet);
free(str_ssn);
free(lname);
free(fname);
return new; 
}

void student_free(student *stu){
    free(stu->cnet);
    free(stu->lname);
    free(stu->fname);
    if(stu->next){
    student_free(stu->next);
    }
    free(stu);
}

ihi *ihi_new(uint32_t n_buckets, uint64_t(*h)(uint32_t n)){
    ihi *new = malloc(sizeof(ihi));
    new->hash = h;
    new->n_buckets = n_buckets; 
    new->buckets = (entry**)malloc(n_buckets * sizeof(entry*));
    for (int i = 0; i < n_buckets; i++) {
        new->buckets[i] = NULL;
    }
    
    return new; 
}

entry *ent_new(int hash_code, student *stu){
    entry *new = malloc(sizeof(entry));
    new->hash_code = hash_code; 
    new->stu = stu; 
    new->next = NULL; 
    return new; 
}

void ihi_insert_by_ucid(ihi *idx, student *stu) {
    uint32_t ucid = stu->ucid;
    int index = idx->hash(ucid);
    entry *current = idx->buckets[index];

    if (!current) {
        idx->buckets[index] = ent_new(ucid, stu);
        return;
    }
    while (1) {
        if (!current->next) {
            current->next = ent_new(ucid, stu);
            return;
        }
        current = current->next;
    }
}

void ihi_insert_by_ssn(ihi *idx, student *stu){
    uint32_t ssn= stu->ssn;
    int index = idx->hash(ssn);
    entry *current = idx->buckets[index];

    if (!current) {
        idx->buckets[index] = ent_new(ssn, stu);
        return;
    }
    while (1) {
        if (!current->next) {
            current->next = ent_new(ssn, stu);
            return;
        }
        current = current->next;
    }
}

entry* ucid_match(entry* student, uint32_t n) {
    if (!student) return NULL;
    else if (student->stu->ucid == n)
        return student;
    return ucid_match(student->next, n);
}

student* ihi_find_by_ucid(ihi* idx, uint32_t n) {
    int h_idx = idx->hash(n);
    if (idx->buckets[h_idx] == NULL)
        return NULL;
    entry* current = idx->buckets[h_idx];
    if (!ucid_match(current, n)) return NULL; 
    return ucid_match(current, n)->stu;
}

entry* ssn_match(entry* student, uint32_t n) {
    if (!student) return NULL;
    else if (student->stu->ssn == n)
        return student;
    return ssn_match(student->next, n);
}

student *ihi_find_by_ssn(ihi *idx, uint32_t n){
    int h_idx = idx->hash(n);
    if (idx->buckets[h_idx] == NULL)
        return NULL;
    entry* current = idx->buckets[h_idx];
    if (!ssn_match(current, n)) return NULL; 
    return ssn_match(current, n)->stu; 
}

shi *shi_new(uint32_t n_buckets, uint64_t(*h)(char *s)){
    shi *new = malloc(sizeof(shi));
    new->hash = h;
    new->n_buckets = n_buckets; 
    new->buckets = (entry**)malloc(n_buckets * sizeof(entry*));
    for (int i = 0; i < n_buckets; i++) {
        new->buckets[i] = NULL;
    }
    return new; 
}


void shi_insert_by_cnet(shi *idx, student *stu){
    char* cnet= stu->cnet; 
    int index = idx->hash(cnet);
    entry *current = idx->buckets[index];
    if (!current) {
        idx->buckets[index] = ent_new(*cnet, stu);
        return;
    } 
    while (1) {
        if (!current->next) {
            current->next = ent_new(*cnet, stu);
            return;
        }
        current = current->next;
    }
}

void shi_insert_by_lname(shi *idx, student *stu){
    char* lname= stu->lname; 
    int index = idx->hash(lname);
    entry *current = idx->buckets[index];
    if (!current) {
        idx->buckets[index] = ent_new(*lname, stu);
        return;
    } 
    while (1) {
        if (!current->next) {
            current->next = ent_new(*lname, stu);
            return;
        }
        current = current->next;
    } 
}

void shi_insert_by_fname(shi *idx, student *stu){
    char* fname= stu->fname; 
    int index = idx->hash(fname);
    entry *current = idx->buckets[index];
    if (!current) {
        idx->buckets[index] = ent_new(*fname, stu);
        return;
    } 
    while (1) {
        if (!current->next) {
            current->next = ent_new(*fname, stu);
            return;
        }
        current = current->next;
    } 
}

entry* string_match(entry* student, char* n, int type) {
    if (!student) return NULL;
    if (!type)
        if (!strcmp(student->stu->cnet, n)) return student; 
    if (type == 1)
        if (!strcmp(student->stu->lname, n)) return student; 
    if (type == 2)
        if (!strcmp(student->stu->fname, n)) return student; 
    return string_match(student->next, n, type);
}
student *shi_find_by_cnet(shi *idx, char *s){
    int h_idx = idx->hash(s);
    if (idx->buckets[h_idx] == NULL)
        return NULL;
    entry* current = idx->buckets[h_idx];
    if (!string_match(current, s, 0)) return NULL; 
    return string_match(current, s, 0)->stu; 
    return NULL; 
}

student *shi_find_by_lname(shi *idx, char *s){
    int h_idx = idx->hash(s);
    if (idx->buckets[h_idx] == NULL)
        return NULL;
    entry* current = idx->buckets[h_idx];
    if (!string_match(current, s, 1)) return NULL; 
    return string_match(current, s, 1)->stu; 
    return NULL; 
}

student *shi_find_by_fname(shi *idx, char *s){
    int h_idx = idx->hash(s);
    if (idx->buckets[h_idx] == NULL)
        return NULL;
    entry* current = idx->buckets[h_idx];
    if (!string_match(current, s, 2)) return NULL; 
    return string_match(current, s, 2)->stu; 
    return NULL; 
}

student_db *db_new(uint32_t n_buckets, uint64_t(*int_hash)(uint32_t n),
uint64_t(*string_hash)(char *)){
    student_db *new = malloc(sizeof(student_db));
    new->count = 0; 
    ihi *ucid_idx = ihi_new(n_buckets, int_hash); 
    new->ucid_idx = ucid_idx; 
    shi *cnet_idx = shi_new(n_buckets, *string_hash);
    new->cnet_idx = cnet_idx; 
    ihi *ssn_idx = ihi_new(n_buckets, *int_hash);
    new->ssn_idx = ssn_idx; 
    shi *lname_idx = shi_new(n_buckets, *string_hash);
    new->lname_idx = lname_idx;
    shi *fname_idx = shi_new(n_buckets, *string_hash);
    new->fname_idx = fname_idx; 

return new; 
}

void db_insert(student_db *db, student *stu) {
    if (ihi_find_by_ucid(db->ucid_idx, stu->ucid) ||
        shi_find_by_cnet(db->cnet_idx, stu->cnet) ||
        ihi_find_by_ssn(db->ssn_idx, stu->ssn)) {
        fprintf(stderr, "A user with this info already exists");
        return;
    }

    ihi_insert_by_ucid(db->ucid_idx, stu);
    shi_insert_by_cnet(db->cnet_idx, stu);
    ihi_insert_by_ssn(db->ssn_idx, stu);
    shi_insert_by_lname(db->lname_idx, stu);
    shi_insert_by_fname(db->fname_idx, stu);
    db->count += 1;
}

void strip(char* csv_row){
    for(int i=0; i<strlen(csv_row); i++){
        if (csv_row[i] == '\r' || csv_row[i] == '\n'){
            csv_row[i] = '\0';
        }
    }
}

student_db *db_from_file(char *filename, uint64_t (*int_hash)(uint32_t n), uint64_t (*string_hash)(char *)) {
    FILE *f = fopen(filename, "r");
    char csv_row[100]; 
    student_db *new_db = db_new(10, int_hash, string_hash);
   
    while (fgets(csv_row, sizeof(csv_row), f)) {
        strip(csv_row);
        db_insert(new_db, student_from_string(csv_row));
    }

    fclose(f);
    return new_db;
}



student *find_by_ucid(student_db *db, uint32_t ucid){
    return ihi_find_by_ucid(db->ucid_idx, ucid); 
}

student *find_by_cnet(student_db *db, char *cnet){
     return shi_find_by_cnet(db->cnet_idx, cnet); 
}

student *find_by_ssn(student_db *db, uint32_t ssn){
    return ihi_find_by_ssn(db->ssn_idx, ssn); 
}

student *find_by_lname(student_db *db, char *lname){
     return shi_find_by_lname(db->lname_idx, lname);  
}

student *find_by_fname(student_db *db, char *fname){
     return shi_find_by_fname(db->fname_idx, fname); 
}

void swap(char **cnet_arr, int idx1, int idx2){
    char* tmp = cnet_arr[idx1];
    cnet_arr[idx1] = cnet_arr[idx2];
    cnet_arr[idx2] = tmp; 
}

void sort(char** cnet_arr, int len){
    int sorted; 
    do {
        sorted = 1; 

        for(int i=1; i < len; i++){
            if(strcmp(cnet_arr[i-1], cnet_arr[i])> 0){
                swap(cnet_arr, i-1, i);
                sorted = 0; 
            }
        }
        len--; 
    } while(!sorted);
}

char **cnets_asc(student_db *db) {
    shi *str_idx = db->cnet_idx;
    char **cnet_arr = malloc(db->count * sizeof(char*)); 
    int idx = 0; 

    for (int i = 0; i < str_idx->n_buckets; i++) {
        entry *cur = str_idx->buckets[i]; 
        while (cur) {
            cnet_arr[idx] = strdup(cur->stu->cnet);
            cur = cur->next; 
            idx++; 
        }
    }
  
    sort(cnet_arr, idx);
    return cnet_arr;
}

student_db *db_resize(student_db *db, uint32_t n_buckets) {
    student_db *new_db = db_new(n_buckets, db->ucid_idx->hash, db->cnet_idx->hash);
    char **cnet_arr = cnets_asc(db);
    int idx = db->count;
    for (int i = 0; i < idx; i++) 
        db_insert(new_db, shi_find_by_cnet(db->cnet_idx, cnet_arr[i]));
    free(cnet_arr);
    return new_db;
}

void db_free(student_db *db){
    for(int i=0; i<db->ucid_idx->n_buckets; i++){
    entry *cur = db->ucid_idx->buckets[i];
    while(cur){
        entry *next = cur->next; 
        student_free(cur->stu); 
        free(cur); 
        cur = next; 
    }
    }

    free(db->ucid_idx->buckets);
    free(db->cnet_idx->buckets);
    free(db->ssn_idx->buckets);
    free(db->lname_idx->buckets);
    free(db->fname_idx->buckets);
    free(db->ucid_idx);
    free(db->cnet_idx);
    free(db->ssn_idx);
    free(db->lname_idx);
    free(db->fname_idx);
    free(db);
    }

uint64_t one(char *s) {return 1;}
uint64_t zero(uint32_t n) {return 0;}
