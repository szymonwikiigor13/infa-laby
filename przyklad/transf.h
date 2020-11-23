#ifndef TRANSF_H
#define TRANSF_H

#include "image.h"

PgmImage* rotate_k90_deg(PgmImage*, int);

int histogram(PgmImage*, int*);

void negative(PgmImage*);

void salt_pepper(PgmImage*, int);

PgmImage* gauss_blur(PgmImage*);

#endif
