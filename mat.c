#include "mat.h"
#include <stdio.h>
#include <stdlib.h>

lab createLab(int n)  //funkcja dla stworzenia macierzy nxn dla labiryntu
{
	lab new = (lab) malloc(sizeof new); //alokacja pamięci dla new
	
	if(new != NULL)
	{	
		new->n = (n*2) + 3;
		new->mat = (elem**) malloc(sizeof(elem*) * new->n); //alokacja pamięci dla new->mat
		
		if(new->mat == NULL){
#ifdef DEBUG
			fprintf(stderr, "Błąd: nie alokowana pamięć dla new->mat");
#endif
			free(new);
			return NULL;
		}
		int i;
		for(i = 0; i < new->n; i++)
		{
			new->mat[i] = (elem*)malloc(sizeof(elem) * new->n); //alokacja pamięci dla każdego elementu tablicy new->mat
			if(new->mat[i] == NULL)
			{
				int j;
				for(j = 0; j < i; j++)
				{
					free(new->mat[j]);
				}
				free(new->mat);
				free(new);
#ifdef DEBUG
				fprintf(stderr, "Błąd: nie alokowana pamięć dla new->mat[%d]", i);
#endif
    return NULL;
			}
			
		}
	} else {
#ifdef DEBUG
		fprintf(stderr, "Błąd: nie alokowana pamięć dla new");
#endif
		return NULL;
	}

	return new;
}


void srodek(lab s, int *sr1, int *sr2) //funkcja dla szukania koordynat wejścia i wyjścia 
{
    double sr;
	int srr;
	int n = s->n;
	int n1 = (n-3) / 2;
	sr = n1 % 2;
	srr = n / 2;
	
	if(sr != 0)
	{
		*sr1 = srr;
		*sr2 = *sr1;
	} else if(sr == 0) {
		*sr1 = srr-1;
		*sr2 = *sr1+2;
	}
}


void fill_lab(lab s) //funkcja dla początkowego zapełnienia stworzonego labityntu
{	
	//szukanie wejścia i wyjścia w labiryncie 
	//  |
	//  v
	double sr;
	int sr1, sr2, srr;
	int n = s->n;
	int n1 = (n-3) / 2;
	sr = n1 % 2;
	srr = n / 2;
	
	if(sr != 0)
	{
		sr1 = srr;
		sr2 = sr1;
	} else if(sr == 0) {
		sr1 = srr-1;
		sr2 = sr1+2;
	}
 //zapełnienie macierzy zerami i jedynkami dalej do końca funkcji
	int i, j;
	for(i = 0; i < n; i++)
	{
		(s->mat[0][i]).x = 0;
		(s->mat[0][i]).waga = 0;
	}
	
	for(i = 0; i < n; i++)
	{
		(s->mat[n-1][i]).x = 0;
		(s->mat[n-1][i]).waga = 0;
	}
	
	for(i = 1; i < n-1; i++)
	{
		(s->mat[i][0]).x = 0;
		(s->mat[i][0]).waga = 0;
		(s->mat[i][n-1]).x = 0;
		(s->mat[i][n-1]).waga = 0;
	}

	for(i = 1; i < n-1; i++)
        {
                (s->mat[1][i]).x = 1;
                (s->mat[1][i]).waga = 0;
        }

        for(i = 1; i < n-1; i++)
        {
                (s->mat[n-2][i]).x = 1;
                (s->mat[n-2][i]).waga = 0;
        }

        for(i = 2; i < n-2; i++)
        {
                (s->mat[i][1]).x = 1;
                (s->mat[i][1]).waga = 0;
                (s->mat[i][n-2]).x = 1;
                (s->mat[i][n-2]).waga = 0;
        }



	for(i = 2; i < n-2; i++)
	{
		for(j = 2; j < n-2; j++)
		{
			if(i%2 != 0 && j%2 != 0){
				(s->mat[i][j]).x = 1;
			} else {
				(s->mat[i][j]).x = 3;
			}	
			(s->mat[i][j]).waga = 0;
		}
	}
	(s->mat[2][sr1]).x = 0;
	(s->mat[n-3][sr2]).x = 0;
}

void zamianaLab(lab s) //funkcja robi zamianę wszystkich trójek w labiryncie na jedynki

{
	int i, j;
	int n = s->n;
	for(j = 1; j < n - 1; j++)
	{
		for(i = 1; i < s->n - 1; i++)
		{
			if((s->mat[j][i]).x == 3)
			{
				(s->mat[j][i]).x = 0;
			} 
		}
	}
}


void zamianaLabSc(lab s) //funkcja robi zamianę wszystkich trójek i dwójek w labiryncie na zera
{
        int i, j;
        int n = s->n;
        for(j = 1; j < n - 1; j++)
        {
                for(i = 1; i < s->n - 1; i++)
                {
                        if((s->mat[j][i]).x == 3 || (s->mat[j][i]).x == 2)
                        {
                                (s->mat[j][i]).x = 0;
                        }
                }
        }
}



void zamianaLabZero(lab s) //funkcja która szuka wejście o wyjście z laniryntu i zamienia jedynkę na ścianę
{
	double sr; 
        int sr1, sr2, srr;
        int n = s->n;
        int n1 = (n-3) / 2;
        sr = n1 % 2;
        srr = n / 2;
    
        if(sr != 0)
        {
                sr1 = srr;
                sr2 = sr1;
        } else if(sr == 0) {
                sr1 = srr-1;
                sr2 = sr1+2;
        }

	(s->mat[1][sr1]).x = 0;
        (s->mat[n-2][sr2]).x = 0;

}

void zamiana(lab x) //zamiana wszystkich nie równych zeru liczb na jedynki
{
	int n = x->n;
	int i, j;
        for(i = 1; i < n-1; i++)
        {
                for(j = 1; j < n-1; j++)
                {
                        if((x->mat[i][j]).x != 0)
                        {
                                (x->mat[i][j]).x = 1;
                        }
                }
        }
}



void printLab(lab x) //drukowanie laniryntu
{
	int i, j;
	for(i = 0; i < x->n; i++)
	{
		for(j = 0; j < x->n; j++)
		{
			if((x->mat[i][j]).x == 1){
                		printf("\033[47m  \033[0m");  // Ściana
			} else if((x->mat[i][j]).x == 3){
            	    		printf("\e[41m  \e[0m");  // Przejście
            		} else {
				printf("  "); //przejście
			}
		}
		printf("\n");
	}
}



void freeLab(lab x) //zwolnienie pamięci dla alokowanej dla labiryntu
{
	int i;
	for(i = 0; i < x->n; i++)
	{
		free(x->mat[i]);
	}
	free(x->mat);
	free(x);
}





























