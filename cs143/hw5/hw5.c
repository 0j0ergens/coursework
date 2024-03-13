#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "hw5.h"

student *student_new(uint32_t ucid, char *cnet, uint32_t ssn, \
char *lname, char *fname){
student *new = malloc(sizeof(student));
new->ucid = ucid; 
new->cnet = strdup(cnet); 
new->ssn = ssn; 
new->lname = strdup(lname);
new->fname = strdup(fname); 

return new; 
}

void student_free(student *stu){
free(stu->cnet);
free(stu->lname);
free(stu->fname);
free(stu); 
}

uint32_idx *ui_singleton(uint32_t key, student *stu){

uint32_idx *new = malloc(sizeof(uint32_idx)); 
new->key = key; 
new->stu = stu; 
new->left = NULL; 
new->right = NULL; 

return new; 
}

void ui_insert(uint32_idx *ui, uint32_t key, student *stu) {
if (ui == NULL) return;
if(key != stu->ssn && key != stu->ucid) return; 
if (key > ui->key) {
 if (ui->right == NULL) ui->right = ui_singleton(key, stu); 
 else ui_insert(ui->right, key, stu); 
}
else if (key < ui->key) {
 if (ui->left == NULL) ui->left = ui_singleton(key, stu);
 else ui_insert(ui->left, key, stu); 
 }
}

student *ui_find(uint32_idx *ui, uint32_t n){
if (ui == NULL) return NULL;
if (ui->key == n) return ui->stu;
else if (n < ui->key){
 if (ui->left == NULL) return NULL; 
  return ui_find(ui->left, n);
}
else { 
 if (ui->right == NULL) return NULL; 
 return ui_find(ui->right, n);
 }
}

string_idx *si_singleton(char *key, student *stu){
string_idx *new = malloc(sizeof(string_idx)); 
new->key = key; 
new->stu = stu; 
new->left = NULL; 
new->right = NULL; 

return new; 
}

void si_insert(string_idx *si, char *key, student *stu){
if(si == NULL) return; 
if(strcmp(key, stu->cnet) != 0) return; 

if (strcmp(si->key, key) > 0){
 if(si->right == NULL) si->right = si_singleton(strdup(key), stu); 
 else si_insert(si->right, key, stu); 
}

else if (strcmp(si->key, key) < 0){
 if (si->left == NULL) si->left = si_singleton(strdup(key), stu);
 else si_insert(si->left, key, stu); 
}
}

student *si_find(string_idx *si, char *s){
 if (si == NULL) return NULL; 
 if (!strcmp(si->key, s)) return si->stu; 

 else if (strcmp(si->key, s) < 0){
  if (si->left == NULL) return NULL; 
  return si_find(si->left, s); 
 }

 else {
  if (si->right == NULL) return NULL; 
  return si_find(si->right, s); 
 }
}

student_db *db_new(){ 
student_db *new = malloc(sizeof(student_db)); 
new->count = 0; 
new->ucid_idx = NULL; 
new->cnet_idx = NULL; 
new->ssn_idx = NULL; 
return new; 
}

uint32_t db_num_entries(student_db *db){
return db->count; 
}

void db_insert(student_db *db, student *stu){ 
if (si_find(db->cnet_idx, stu->cnet) ){
fprintf(stderr, "Student [%s] already exists", stu->cnet); 
return; 
} 
db->count ++; 
if (!db->cnet_idx) {
 db->cnet_idx = si_singleton(stu->cnet, stu); 
 db->ucid_idx = ui_singleton(stu->ucid, stu); 
 db->ssn_idx = ui_singleton(stu->ssn, stu); 
}

si_insert(db->cnet_idx, stu->cnet, stu); 
ui_insert(db->ucid_idx, stu->ucid, stu);
ui_insert(db->ssn_idx, stu->ssn, stu); 

}

student *find_by_ucid(student_db *db, uint32_t ucid){
 return ui_find(db->ucid_idx, ucid); 
}

student *find_by_cnet(student_db *db, char *cnet){
 return si_find(db->cnet_idx, cnet); 
}

student *find_by_ssn(student_db *db, uint32_t ssn){
 return ui_find(db->ssn_idx, ssn); 
}

void uidx_free(uint32_idx *ucid_idx){
 if (!ucid_idx->left && !ucid_idx->right){
  free(ucid_idx); 
  return; 
 }
 if (ucid_idx->left) uidx_free(ucid_idx->left); 
 if (ucid_idx->right) uidx_free(ucid_idx->right); 
}

void sidx_free(string_idx *string_idx){
 if (!string_idx->left && !string_idx->right){
  free(string_idx); 
  return;
 }
 if (string_idx->left) sidx_free(string_idx->left); 
 if (string_idx->right) sidx_free(string_idx->right); 
}

void db_free(student_db *db){
if (!db) return; 
while(db->ssn_idx){
 uint32_idx *cur = db->ssn_idx; 
 db->ssn_idx = db->ssn_idx->left; 
 student_free(cur->stu);
 free(cur);  
}

while(db->cnet_idx){
 string_idx *cur = db->cnet_idx; 
 db->cnet_idx = db->cnet_idx->left; 
 student_free(cur->stu);
 free(cur);  
}

while(db->ucid_idx){
 uint32_idx *cur = db->ucid_idx; 
 db->ucid_idx = db->ucid_idx->left; 
 student_free(cur->stu);
 free(cur);  
}

free(db); 
}



