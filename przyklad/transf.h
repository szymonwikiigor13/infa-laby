#ifndef TRANSF_H
#define TRANSF_H

#include "image.h"

PgmImage* rotate(PgmImage*, int);

int histogram(PgmImage*, int*);

void negative(PgmImage*);

void salt_pepper(PgmImage*);

PgmImage* gauss(PgmImage*);

#endif
