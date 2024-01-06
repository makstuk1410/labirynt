#ifndef _WAGI_H_
#define _WAGI_H_

#include "mat.h"
#include "labirynt.h"
#include "sciana.h"

typedef struct Node{
        double waga;
        int i;
        int j;
        struct Node* next;
} Node;

typedef struct sciezka{
	double waga;
	int numer;
} sciezka;

void insert(Node **root, int i, int j, double waga);

void remove_element(Node **root, int j, int i);

void dealloc(Node** root);

double randomWaga(void);

void wagiLab(lab s);

void printWagi(lab s);

void zapisywanieDoWektora(lab s, el** elem, int* a, double* aa, int t, Node **root);

int kierunekSciezki(int j, int i, lab s, int mode, int* mod, int* bl);

void ruchSciezki(int *j, int *i, lab s, Node** root, int bl, int sr);

void najmniejszaSciezka(lab s);


#endif
