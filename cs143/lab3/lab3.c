#include <stdio.h>
#include <stdlib.h>
#include "lab3.h"

// in this file, write implementations of the functions
// whose headers appear in lab3.h

// please refrain from including string.h

// important: don't write a main function
// this is a module meant to be imported

unsigned int len(char *s) { 
 int i = 0; 
 while(s[i] != '\0'){
  ++i;
 } 
 return i; 
}

char *repeat_char(char c, unsigned int n); 

//unsigned int 
