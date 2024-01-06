#ifndef _SCIANA_H_
#define _SCIANA_H_

#include "mat.h"

typedef struct el {
	int j;
	int i;
} el;

int randoms(lab s);
void randoml(lab s, int *j, int *i);
int sprs(lab s, int j, int i, int* stan, int bl);
void ruchzam(lab s, int *j, int *i, int k, int l);
void zamianaSciany(lab s, int j, int i, int l);
int zamianas(lab s);
void tworzenieWektora(lab s, el** elem, int* a, int* aa, int sz);
int sprss(lab s, int j, int i);
void ruchsz(lab s, int j, int i, int k, int h, int r);
void rysowanieScian(lab s);

#endif
