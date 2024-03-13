#include <stdio.h> 
#include <math.h>

int main(int argc, char* argv[]){
 char* perm = argv[1]; 
 int dec = 0;
 int oct = 0;

 for(int i = 0; i < 9; i++){
   if (perm[i] != '-'){ 
     dec += pow(2, (8-i)); 
  }
 } 
 
 for(int i = 0; i < 3; i++){
   oct += dec % 8 * pow(10, i);
   dec = floor(dec/8);    
 } 

 printf("%d", oct); 
 return 0; 
}

