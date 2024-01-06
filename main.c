#include "mat.h"
#include "labirynt.h"
#include "sciana.h"
#include "wagi.h"
#include "error.h"
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char **argv)
{
	int error = blad(argc, argv);
	
	if(error == 1){
		return 1;
	}
	
	int n = argc > 1 ? atoi(argv[1]) : 11;
	
	lab l = createLab( n );
	if (l == NULL)
		return 1;
	
	fill_lab(l);
	rysowanie( l );
	zamianaLabZero( l );
	zamianaLab( l );
	rysowanieScian( l );
	zamiana( l );
	printLab( l );
	wagiLab( l );
	najmniejszaSciezka( l );
	zamianaLabZero( l );
	printLab( l );
	freeLab( l );

	return 0;
}
