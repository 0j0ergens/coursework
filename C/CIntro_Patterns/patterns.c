#include <stdio.h>


void draw_line(int ncols, int side){ 
 putchar('\n');
 for(int i = 0; i < ncols; i++){
   putchar('_'); 
   for(int j = 0; j < side; j++){
      putchar('_'); 
   }         
 }
 putchar('_');  
 putchar('\n');
}

void pattern(int nrows, int ncols, int side, char c1, char c2){
 if (ncols > 0){
  draw_line(ncols, side);
 
  for(int i = 0; i < nrows; i++){
    for (int j = 0; j < side; j++) {  
      putchar('\n');
      putchar('|');
      for(int k = 0; k < ncols; k++){
        if((i+k) % 2 == 0){
          for(int l = 0; l < side; l++){
            putchar(c1);
          }
          putchar('|'); 	 
	 }   
         else{
           for(int l = 0; l < side; l++){
             putchar(c2);
           }
	     putchar('|'); 
         } 
       }
     }
  draw_line(ncols, side);    
  }
 } 
}

int main()
{
    pattern(1,1,1,'X','O');
    pattern(2,2,2,'X','O');
    pattern(2,2,2,'O','X');
    pattern(0,0,0,'X','Y');
    pattern(4,2,2,'X','O');
    pattern(2,4,2,'X','O');
    pattern(7,7,8,'a','b');
    return 0;
}

