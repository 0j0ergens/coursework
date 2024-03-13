#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>

void draw_line(int width, int color){ 

 int r = color >> 16; 
 int g = color >> 8 & 0xFF; 
 int b = color & 0xFF;   

 for(int i = 0; i < width; i ++){
    printf("%d %d %d\n", r, g, b); 
 }
}

int main(int argc, char* argv[]){
 int w_arr = atoi(argv[1]); 
 int h_arr = atoi(argv[2]); 
 int w_pane = atoi(argv[3]); 
 int h_pane = atoi(argv[4]); 
 int border = atoi(argv[5]); 
 int col_pane = 16777215;
 int col_bord = 0;

 if (argc == 7)
   col_pane = atoi(argv[6]); 

 int w = w_arr*w_pane + (w_arr+1)*border; 
 int h = h_arr*h_pane + (h_arr+1)*border;
 
 printf("P3\n%d %d\n255\n", w, h);

 for(int i=0; i<h_arr*2+1; i++){  
  if(i % 2 == 0)
   draw_line(w*border, col_bord);  
 
  else{
   for(int k=0; k < h_pane; k++){
    if(k > 0)
      draw_line(border, col_bord);  
    for(int j=0; j < w_arr; j++){
      draw_line(border, col_bord); 
      draw_line(w_pane, col_pane);
    }
   }
   draw_line(border, col_bord);  
  }  
 }   
}
