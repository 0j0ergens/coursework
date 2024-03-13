#include <stdio.h>
#include <stdlib.h>
#include <time.h>
enum opt_command {NONE=0, LEFT=1, UP=2, RIGHT=3, DOWN=4, HELP=5, QUIT=6};
enum opt_command get_command(){
 char c = getchar();  
 if (c == 'w')
  return UP;  
 else if (c == 'a')
  return LEFT; 
 else if (c == 's')
  return DOWN; 
 else if (c == 'd')
  return RIGHT;
 else if (c == 'h')
  return HELP; 
 else if (c == 'q')
  return QUIT;
 else 
  return NONE;  
}

char *board_new(){
 char *arr;
 arr = (char *)malloc(16); 
 char hex[2]; 
 for (int i=0;i<15;i++){
  sprintf(hex, "%X", i+1); 
  arr[i] = hex[0]; 
}
arr[15] = '_'; 
return(arr); 
}

int empty_cell(char *board){
int i = 0; 
 while(i<16){
  if(board[i] == '_') 
    return i;
  i++;
}
}

int up_neighbor(int i){
if (i < 4)
   return -1; 
 else
   return i-4; 
}

int down_neighbor(int i){
 if (i > 11)
   return -1; 
 else
   return i+4; 
}

int left_neighbor(int i){
 if (i%4 == 0) 
   return -1; 
 else
  return i-1; 
}

int right_neighbor(int i){
 if (i%4 == 3)
   return -1; 
 else 
  return i+1; 
}

void swap(char *board, int idx1, int idx2) {
 char tmp = board[idx1]; 
 board[idx1] = board[idx2];
 board[idx2] = tmp; 
}
 
void slide_left(char *board){
 int idx1 = empty_cell(board);
 int idx2 = left_neighbor(idx1); 
 if (idx2 != -1)
   swap(board, idx1, idx2); 
}

void slide_right(char *board){
 int idx1 = empty_cell(board); 
 int idx2 = right_neighbor(idx1); 
 if (idx2 != -1)
   swap(board, idx1, idx2); 
}

void slide_up(char *board){ 
 int idx1 = empty_cell(board); 
 int idx2 = up_neighbor(idx1); 
 if (idx2 != -1)
   swap(board, idx1, idx2); 
}

void slide_down(char *board){
 int idx1 = empty_cell(board); 
 int idx2 = down_neighbor(idx1); 
 if (idx2 != -1)
   swap(board, idx1, idx2); 
}

void shuffle(char *board, unsigned int n){ 
  srand(time(NULL));
  
  for(int i=0;i<n;i++){
     int rand_com = rand()%4; 
     if (rand_com == 1)
       slide_up(board);  
     else if (rand_com == 2)
       slide_left(board); 
     else if (rand_com == 3)
       slide_down(board);
     else 
       slide_right(board);  
   }
  }      

void show_board(char *board){ 
 for(int i=0; i<16;i++){
   putchar(board[i]); 
   if ((i+1)%4==0)
    putchar('\n'); 
 }
}

int solved(char *board){
 char *finished = board_new(); 
 for(int i=0; i<16;i++){
  if (board[i] != finished[i])
   return 0;  
 }
free(finished); 
return 1; 
}

void display_help() {
printf("w: slide up (if possible)\n");
printf("d: slide right (if possible)\n");
printf("s: slide down (if possible)\n");
printf("a: slide left (if possible)\n");
printf("h: help\n");
printf("q: quit\n");
printf("\n");
}

int main(int argc, char *argv[]){
int shuf_n; 
if (argc > 1)
 shuf_n = atoi(argv[1]);
else 
 shuf_n = 1000;  

char *board = board_new(); 
shuffle(board, shuf_n);
system("figlet slide15");
show_board(board); 

while(1){
int dir = get_command();
if(solved(board)){
 system("figlet GAME WON"); 
 break; 
}

if (dir == QUIT){
 printf("%s", "QUIT GAME"); 
 break; 
}
else if (dir == HELP){
 display_help();
 show_board(board);  
} 

else if (dir == LEFT){ 
 slide_left(board);
 show_board(board); 
}
 
else if (dir == UP){
 slide_up(board);  
 show_board(board); 
}

else if (dir == RIGHT){
 slide_right(board);
 show_board(board); 
}

else if (dir == DOWN){ 
 slide_down(board);
 show_board(board); 
}
}

free(board);
return 0;   
}
