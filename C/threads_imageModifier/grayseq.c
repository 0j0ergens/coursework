#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "hw6.h"

void print_ppm(struct image *image){
    printf("P3\n%d %d\n255\n", image->width, image->height); 
    for (int i=0; i < image->width * image->height; i++){
        printf("%d %d %d\n", image->pixels[i].red, image->pixels[i].green, \
        image->pixels[i].blue); 
    }
}

int main(int argc, char *argv[])
{   
    FILE *fp;
    if (argv[1]) {
        fp = fopen(argv[1], "r");
    } else {
        fp = stdin;
    }
    
    struct image *new = read_image(fp); 
    grayscale_seq(new);
    print_ppm(new); 
    fclose(fp);
    free(new); 

return 0; 
}
