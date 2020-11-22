#include "image.h"

#include <stdio.h>
#include <stdlib.h>

PgmImage* new_img(int width, int height, int grayscale) {
	PgmImage* ref = (PgmImage*) malloc(sizeof(PgmImage));

	ref->width = width;
	ref->height = height;
	ref->grayscale = grayscale;

	ref->data = (int**) malloc(ref->width * sizeof(int*));

	for (int i=0; i<ref->width; i++) {
		ref->data[i] = (int*) calloc(ref->height, sizeof(int));
	}

	return ref;
}

void delete_img(PgmImage* ref) {
	for (int i=0; i<ref->width; i++) {
		free(ref->data[i]);
	}

	free(ref->data);
	free(ref);
}

void print_img(PgmImage* ref) {
	printf("P2\n%d %d\n%d\n", ref->width, ref->height, ref->grayscale);

	for (int i=0; i<ref->width; i++) {
		for (int j=0; j<ref->height; j++) {
			printf("%d ", ref->data[i][j]);
		}
		printf("\n");
	}
}

