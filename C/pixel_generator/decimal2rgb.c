#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]){
 int rgb = atoi(argv[1]); 
 int r = rgb >> 16; 
 int g = rgb >> 8 & 0xFF; 
 int b = rgb & 0xFF;
 printf("%d %d %d", r, g, b);   
}
