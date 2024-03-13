#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int dec2rgb(int rgb){ 
 int r = rgb >> 16; 
 int g = rgb >> 8 & 0xFF; 
 int b = rgb & 0xFF;
 return 0;  
}

int main(int argc, char *argv[]){
 int w = atoi(argv[1]); 
 int h = atoi(argv[2]);

 int bottom = atoi(argv[4]); 
 int r_bot = bottom >> 16; 
 int g_bot = bottom >> 8 & 0xFF; 
 int b_bot = bottom & 0xFF; 

 int top = atoi(argv[3]); 
 int r_top = top >> 16; 
 int g_top = top >> 8 & 0xFF; 
 int b_top = top & 0xFF;   
 printf("P3\n%d %d\n255\n",w,h);

 for(int i=0; i<h*w; i++){  
   int row = floor(i/w);   
   int r = floor(r_top*(1-(row/(float)(h-1))) +  r_bot*(row/(float)(h-1))); 
   int g = floor(g_top*(1-(row/(float)(h-1))) +  g_bot*(row/(float)(h-1)));  
   int b = floor(b_top*(1-(row/(float)(h-1))) +  b_bot*(row/(float)(h-1))); 
  printf("%d %d %d\n", r, g, b);
 
  }
 return 0;  
}
