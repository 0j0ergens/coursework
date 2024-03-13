#ifndef _HW6_HEADER_H_
#define _HW6_HEADER_H_
#include <stdio.h>
struct rgb {
unsigned char red;
unsigned char green;
unsigned char blue;
};

struct image {
unsigned int width;
unsigned int height;
struct rgb *pixels;
};
int luminance(struct rgb c);
// compute the luminance of the given color (see PDF for formula)
struct rgb grayscale(struct rgb c);
// compute the grayscale projection of given color (see PDF)
int same_image(struct image *img1, struct image *img2);
// test if two images are logically the same
int is_grayscale(struct image *img);
// return true if every pixel in image is a shade of gray
struct image *read_image(FILE *f);
// read a P3 or P6 from given file (possibly stdin)
// allocate and populate an image struct, return pointer to it
void grayscale_seq(struct image *img);
// convert image to grayscale in place
// no allocations, no threads
void grayscale_par(struct image *img, unsigned int n_threads);
// convert image to grayscale in place in parallel
// no allocations, as many threads as specified
#endif /* _HW6_HEADER_H_ */