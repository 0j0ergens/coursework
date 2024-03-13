#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
 int r = atoi(argv[1]) << 16;
 int g = atoi(argv[2]) << 8; 
 int b = atoi(argv[3]);  
 int dec = r + g + b;
 printf("%d", dec);  
return 0;
}


