#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

struct image {
    unsigned int width;
    unsigned int height;
    struct rgb *pixels;
};

typedef struct rgb rgb;
typedef struct image img;

void print_ppm(img image){
    printf("P4\n%d %d\n255\n", image.width, image.height); 
    for (int i=0; i < image.width * image.height; i++){
        putchar(image.pixels[i].r); 
        putchar(image.pixels[i].g); 
        putchar(image.pixels[i].b);
    }
}

int main(int argc, char *argv[]) {
    char ftype[3], w[4], h[4]; 
    FILE *fp;

    if (argc > 1) {
        fp = fopen(argv[1], "r");
    } else {
        fp = stdin;
    }
    
    fscanf(fp, "%3s%4s%4s", ftype, w, h);
    int width = atoi(w);
    int height = atoi(h);
    
    img *new = malloc(sizeof(img)); 
    new->width = width; 
    new->height = height; 

    rgb *pixels = malloc(sizeof(rgb) * width * height);

    for (int i = 0; i<5; i++){
        getc(fp); 
    }
    for(int i = 0; i<width*height; i++){
        rgb *new_pixel = malloc(sizeof(rgb)); 

        if(!strcmp(ftype, "P3")){
        int cur_int = 0;
        int color_val = 0;
        while (color_val < 3) {
        char cur_char = getc(fp);
        if (cur_char == ' ' || cur_char == '\n') {
            if (!color_val) new_pixel->r = cur_int;
            else if (color_val == 1) new_pixel->g = cur_int;
            else new_pixel->b = cur_int;
            cur_int = 0;
            color_val++;
            } 
        else cur_int = cur_int * 10 + (cur_char - '0');
            
        }
        pixels[i] = *new_pixel; 
    }

    else{
        new_pixel->r = getc(fp);
        new_pixel->g = getc(fp);
        new_pixel->b = getc(fp);
        pixels[i] = *new_pixel; 
    } 

    free(new_pixel); 
    new->pixels = pixels;
    }
    print_ppm(*new); 
}