#include "db.h"
#include "image.h"

#include <stdio.h>
#include <stdlib.h>

ImageDb* new_db() {
	ImageDb* ref = (ImageDb*) malloc(sizeof(ImageDb));

	ref->size = 0;
	ref->images = NULL;

	return ref;
}

void add_to_db(ImageDb* db, PgmImage* image) {
	if (db->size == 0) {
		db->images = (PgmImage**) malloc(sizeof(PgmImage*));
		db->images[0] = image;

		db->size = 1;
		
	} else {
		db->size++;
		PgmImage** new = (PgmImage**) realloc(db->images, db->size * sizeof(PgmImage*));
		if (new == NULL) {
			exit(-1);
		}

		new[db->size - 1] = image;
		db->images = new;
	}
}

void set_in_db(ImageDb* db, PgmImage* image, int index) {
	if (db->size < 0 || db->size < index) return;

	delete_img(db->images[index]);
	db->images[index] = image;
}


void delete_from_db(ImageDb* db, int index) {
	if (db->size < 1 || db->size < index) {
		return;

	} else if (db->size == 1) {
		delete_img(db->images[0]);
		free(db->images);

		db->images = NULL;
		db->size = 0;

	} else {
		delete_img(db->images[index]);

		for (int i=index; i<db->size - 1; i++) {
			db->images[i] = db->images[i+1];
		}

		db->size--;

		PgmImage** new = (PgmImage**) realloc(db->images, db->size * sizeof(PgmImage*));
		if (new == NULL) {
			exit(-1);
		}

		db->images = new;
	}
}

PgmImage* get_from_db(ImageDb* db, int index) {
	if (index < 0 || index > db->size) return NULL;

	return db->images[index];
}

void print_db(ImageDb* db) {
	for (int i=0; i<db->size;i++) {
		printf("Image id: %d\n", i);

		print_img(db->images[i]);
	}
}

void delete_db(ImageDb* db) {
	for (int i=0; i<db->size; i++) {
		delete_img(db->images[i]);
	}

	free(db->images);
	free(db);
}

