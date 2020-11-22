#ifndef IMAGE_H
#define IMAGE_H

typedef struct pgm_image {
	int width;
	int height;
	int grayscale;

	int** data;
} PgmImage;

PgmImage* new_img(int, int, int);

void delete_img(PgmImage*);

void print_img(PgmImage*);

#endif
