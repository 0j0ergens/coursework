#include <stdio.h>
#include <stdlib.h>

void bytestring(int byte) {
  char *result = malloc(10);
  result[10] = '\0';
  for(int i = 0; i < 9; i ++){ 
   if((byte>>(8-i))&1){
     result[i] = '1';
     if(i%3 == 0){
       putchar('r');
     }
     else if(i%3 == 1){
       putchar('w'); 
     }
     else{
       putchar('x');
     }
    }
 
   else {
     result[i] = '0'; 
     putchar('-'); 
   } 
  }
 free(result);  
}

int main(int argc, char* argv[]){
  int dec = strtol(argv[1], NULL, 8);
  bytestring(dec);    
  return 0; 
}   
 
  
 
  
