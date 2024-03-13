#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hw4.h"

char* stralloc(int start, int end, char *string){  
 int len = (end - start);
 char* str = (char*)malloc(len+1); 
 for(int i=0; i<len; i++){
 str[i] = string[start+i]; 
 } 
 str[len] = '\0'; 
 printf("STR: %s ", str); 
 return str; 
}

char **split_at(char sep, char *string, unsigned int *len) { 
 int size = 0;
 int i = 0; 
 while(i < strlen(string)){
  if (string[i] == sep)
   size++;
  i++; 
 }
 int start = 0, end = 0, a = 0; 
 char** arr = (char**)malloc(size*sizeof(char*)); 
 while(end < strlen(string)){ 
  if(string[end] == sep){
   arr[a] = stralloc(start, end, string); 
   start = end + 1; 
   a ++;  
  }
  end ++; 
 }
 arr[a]  = stralloc(start, end, string); 
 *len = size + 1;  
 return arr; 
}

char *join(char j, char **strings, unsigned int len){
 int l = 0; 
 for(int i=0; i<len; i++)
  l += strlen(strings[i]); 
 char *joined = (char*)malloc(l+len); 
 int a = 0, b = 0;
 for(int i = 0; i < len; i++){
  for(int j = 0; j < strlen(strings[i]); j++){
   joined[a] = strings[i][b];
   a++; 
   b++; 
  }
 if(a<l)
  joined[a] = j;
 b = 0; 
 a++; 
 }
joined[a] = '\0'; 
return joined; 
}

slist* sl_cons(char *s, slist *strings){
 slist* res = (slist*)malloc(sizeof(slist));
 if(res == NULL){
  fprintf(stderr, "cons: allocation failed\n");
  exit(1);
 }
 char* str = (char*)malloc(strlen(s) + 1); 
 for(int i = 0; i < strlen(s); i++)
  str[i] = s[i];
 str[strlen(s)] = '\0'; 
 res->s = str;
 res->next = strings;
 return res;
}

unsigned int sl_total_length(slist *strings){
 int sum = 0; 
 while(strings){
  sum += strlen(strings->s);
  strings = strings -> next; 
 }
 return sum; 
}

 slist* singletons(char* s) {
 slist* res = NULL;
 for (int i = strlen(s) - 1; i >= 0; i--) {
  char* str = (char*)malloc(sizeof(char) * 2); 
  str[0] = s[i];
  str[1] = '\0'; 
  res = sl_cons(str, res); 
 }
  return res;
}

int sl_contains(char *s, slist *strings){
 while(strings){ 
 if (strcmp(s, strings->s)==0){
 return 1; 
 }
 strings = strings->next; 
 } 
 return 0;
}

char *sl_concat_all(slist *strings){
 int size = sl_total_length(strings); 
 char *conc = (char*)malloc(size+1); 
 char* pos = conc; 

 while(strings){
  strcpy(pos, strings->s); 
  pos += strlen(strings->s); 
  strings = strings->next; 
 }
 *pos = '\0'; 
 return conc; 
}

unsigned int sl_count(char c, slist *strings){ 
 int count = 0; 
 while(strings){ 
  for(int i=0;i < strlen(strings->s); i++){
  if((strings->s)[i] == c)
  count ++; 
  }
  strings = strings->next; 
 }
 return count;
}

void reverse_string(char *string){
 int i = 0; 
 while(i<(strlen(string)/2)){
  char cur = string[i];  
  string[i] = string[strlen(string)-1-i]; 
  string[strlen(string)-i-1] = cur;
  i++; 
 }
}

void sl_reverse_in_place(slist *strings){
 while(strings){
  reverse_string(strings->s); 
  strings = strings->next; 
 }
}

slist *sl_reverse_new(slist *strings){
 slist* new = NULL; 
 while(strings){
  int length = strlen(strings->s); 
  char *str = (char*)malloc(length+1); 
 for (int i=0; i<length; i++) {
  str[i]= strings->s[length-i-1];  
 }
 str[length] = '\0';
 if(!new)
  new = sl_cons(str, NULL); 
 new = sl_cons(str, new);
 strings = strings->next;
 new = new->next;
 }
 return new; 
}

slist* sl_from_array(char** strings, unsigned int len) {
 slist* new = NULL;
 for (int i = len - 1; i >= 0; i--) {
  char* str = strdup(strings[i]);
  new = sl_cons(str, new);
 }
 return new;
}

slist *sl_shallow_copy(slist *strings){
 slist *res  = NULL;
 slist *tail = NULL;
 while (strings) {
  slist* new = (slist*)malloc(sizeof(slist));
  new->s = strings->s; 
  new->next = NULL;
 if (res)
  tail->next = new; 
 else 
  res = new;
 tail = new;
 strings = strings->next;
 }
return res;
}

slist *sl_deep_copy(slist *strings){
 slist* out = NULL;
 slist* tail; 
 while (strings) {
  slist* item = sl_cons(strings->s, NULL);
  if (out) { 
  tail->next = item;
 } else { 
  out = item;
 }
  strings = strings->next;
  tail = item;
}
return out;
}

void sl_free(slist *strings){
slist* next;
while (strings) {
 next = strings->next;
 free(strings->s);
 free(strings); strings = next;
}
}

void sl_shallow_free(slist *strings){
slist* next;
while (strings) {
next = strings->next;
free(strings);
strings = next;
}
}


