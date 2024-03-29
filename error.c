#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include <math.h>


int blad(int argc, char **argv) //funkcja która sprawdza podany argument wywołania 
{
	if(argc > 2) //sprawdza cz czasem nie jest więcej niż jeden argument 
	{
		fprintf(stderr, "%s: może być tylko jedyn argument podany\n", argv[0]);
		return 1;
	} else if (argc < 2){ //sprawdza czy w ogóle jest podany argument 
		fprintf(stderr, "%s: nie podano formatu labiryntu", argv[0]);
		return 1;
	}
	
	char *endp;
	double x = strtod(argv[1], &endp);
	
	int y = x*1;
	double u = fmod(x, (double)y);
	//dalej jest sprawdzenie czy argument nie jest słowem czy liczbą mniejszą od dwóch i czy nie jest ta liczba zmiennoprzecinkowa 
	if(strlen(endp) == 0 && u == 0.0)
	{
		if(x < 2)
        	{
                	fprintf(stderr, "%s: to jest niemożliwe zbudować labirynt %d x %d\n", argv[0], y, y); 
                	return 1;
        	} else {
			return 0;
		}
	} else if(strlen(endp) != 0) {
		fprintf(stderr, "%s: podana jakaś bzdura zamiast liczby: %s\n", argv[0], argv[1]);
		return 1;
	} else if(u != 0.0){
		fprintf(stderr, "%s: podana jakaś zmiennoprzecinkowa liczba a nie całkowita: %s\n", argv[0], argv[1]);
		return 1;
	}
}
