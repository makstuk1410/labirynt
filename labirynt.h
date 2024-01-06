#ifndef _LABIRYNT_H_
#define _LABIRYNT_H_

#include "mat.h"

int randomKierunek(int a, int b, int c, int d);

int kierunek(int j, int i, lab s, int* p, int* pk, int o);

void ruch(int *j, int *i, lab s);

void sprawdzenie(lab s);
	
void rysowanie(lab s);

#endif
