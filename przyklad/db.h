#ifndef DB_H
#define DB_H

#include "image.h"

typedef struct image_db {
	int size;
	PgmImage** images;
} ImageDb;

ImageDb* new_db();

void add_to_db(ImageDb*, PgmImage*);

void set_in_db(ImageDb*, PgmImage*, int);

void delete_from_db(ImageDb*, int);

PgmImage* get_from_db(ImageDb*, int);

void print_db(ImageDb*);

void delete_db(ImageDb*);

#endif
