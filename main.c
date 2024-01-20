#include "mat.h"
#include "labirynt.h"
#include "sciana.h"
#include "wagi.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
	int error = blad(argc, argv); //sprawdza argument wywołania 
	
	if(error == 1){
		return 1;
	}
	
	int n = argc > 1 ? atoi(argv[1]) : 11;
	
	lab l = createLab( n ); //tworzy potrzebną macierz
	if (l == NULL)
		return 1;
	
	fill_lab(l); //zapełnia labirynt początkowymi wartościami
	rysowanie( l ); //pierwsza część algorytmu
	zamianaLabZero( l ); //zamiana dla przejścia w labiryncie
	zamianaLab( l ); //zamiana wszystkich trójek na 0
	rysowanieScian( l ); //końcowy etap budowania labiryntu
	zamiana( l ); //zamiana wszystkich liczb innych od 0 na 1
	printLab( l ); //drykowanie labiryntu
	wagiLab( l ); //nadanie wagi każdemu wierzchołku
	najmniejszaSciezka( l ); //wypisywanie ścieżek i szukanie ich do tego
	zamianaLabZero( l ); 
	freeLab( l ); //zwolnienie pamięci 

	return 0; //zwraca zero kiedy wszystko jest w porządku
}
