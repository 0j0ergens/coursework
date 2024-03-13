#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include "hw6.h"
// some helpers for testing
int same_rgb(struct rgb c1, struct rgb c2)
{
return c1.red==c2.red && c1.green==c2.green && c1.blue==c2.blue;
}
struct image *color_square(int n, struct rgb c)
{
struct image *img = (struct image *)malloc(sizeof(struct image));
img->width = n;
img->height = n;
img->pixels = (struct rgb *)malloc(n*n*sizeof(struct rgb));
for (int i=0; i<n*n; i++) {
img->pixels[i].red = c.red;
img->pixels[i].green = c.green;
img->pixels[i].blue = c.blue;
}
return img;
}
void image_free(struct image *img)
{
if (img) {
free(img->pixels);
free(img);
} else {
fprintf(stderr,"warning: attempting to free NULL image");
}
}
// tests
Test(hw6_luminance, lum00)
{
struct rgb c = {0,0,0};
cr_assert(luminance(c)==0);
}
Test(hw6_grayscale, gray00)
{
struct rgb c = {0,0,0};
struct rgb g = {0,0,0};
cr_assert(same_rgb(grayscale(c),g));
}
Test(hw6_same_image, same_image00)
{
struct rgb c = {11,22,33};
struct image *img1 = color_square(100,c);
struct image *img2 = color_square(100,c);
cr_assert(same_image(img1,img2));
image_free(img1);
image_free(img2);
}
Test(hw6_is_grayscale, is_gray00)
{
struct rgb c = {123,123,123};
struct image *img1 = color_square(100,c);
cr_assert(is_grayscale(img1));
image_free(img1);
}
Test(hw6_read_image, read00)
{
// read_image: not tested here; just testing for existence
struct image *(*f)(FILE *f) = &read_image;
cr_assert(f!=NULL);
}
Test(hw6_grayscale_seq, gseq00)
{
struct rgb c = {123,123,123};
struct image *img1 = color_square(100,c);
grayscale_seq(img1);
cr_assert(1);
image_free(img1);
}
Test(hw6_grayscale_par, gpar00)
{
struct rgb c = {123,123,123};
struct image *img1 = color_square(100,c);
grayscale_par(img1,2);
cr_assert(1);
image_free(img1);
}
