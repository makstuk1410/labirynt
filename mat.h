#ifndef _MAT_H_
#define _MAT_H_

#include <stdlib.h>
#include <stdio.h>


typedef struct elem {
	int x;
	double waga;
} elem;

typedef struct lab {
	int n;
	elem** mat;
} *lab;


lab createLab(int n);

void fill_lab(lab s);

void zamiana(lab s);

void zamianaLab(lab s);

void zamianaLabSc(lab s);

void sciany(lab s);

void zamianaLabZero(lab s);

void printLab(lab x);
	
void freeLab(lab x);

#endif
