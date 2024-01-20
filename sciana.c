#include "sciana.h"
#include "mat.h"
#include "labirynt.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randoms(lab s) //losowy wybór maksymalnej ilości ścian w labiryncie
{
	int n = (s->n - 3) / 2;
	n = n / 2;
	
	srand(clock());
	
	int r = 1 + n * ((double)rand()/RAND_MAX);
	return r;
}

void randoml(lab s, int *j, int *i) //losowy wybór elementu z jedynką
{
	int n = ((s->n - 3)/2)-1;
		
	srand(clock());
	while(n != 0){
	
		int r1 = n*((double)rand()/RAND_MAX);
		
		*j = 3 + (r1*2);
		
		int r2 = n*((double)rand()/RAND_MAX);
		
		*i = 3 + (r2*2);
		
		if((s->mat[*j][*i]).x == 1){
			break;
		} else {
			continue;
		}

	}	
}


int sprs(lab s, int j, int i, int* stan, int bl) //szukanie możliwego kierunku dla zamiany ściany z jedynki na inną liczbę
{
	int n = s->n;
	int a[4];
	if(i > 0){
		if((s->mat[j][i-1]).x == 1){ //lewa strona
	 		a[0] = 1;
		} else {
			a[0] = 0;
		}
	} else {
		a[0] = 0;
	}
	
	if(j < n){
		if((s->mat[j+1][i]).x == 1){ //dolna strona
                	a[1] = 1;
        	} else {
               		a[1] = 0;
        	}   
	} else {
		a[1] = 0;
	}	

	if(i < n){
		if((s->mat[j][i+1]).x == 1){ //prawa strona
			a[2] = 1;
		} else {
			a[2] = 0;
		}   
	} else {
		a[2] = 0;
	}


	if(j > 0){	
		if((s->mat[j-1][i]).x == 1){ //gorna strona
                	a[3] = 1;
        	} else {
                	a[3] = 0;
        	}   
	} else {
		a[3] = 0;
	}
	
	int y;
	int suma = 0;
	for(y = 0; y < 4; y++)
	{
        if(y+1 == bl)
        {
            a[y] = 0;        
        }
		suma += a[y];
	}
	
	int k; //wybieramy losowo kierunek z móżliwych dalej 
	if(suma == 1)
	{
		k = randomKierunek(a[0], a[1], a[2], a[3]);
		*stan = 1;
	} else if(suma > 1){
		k = randomKierunek(a[0], a[1], a[2], a[3]);
		*stan = 2;
	} else {
		k = 0; 
		*stan = 0;
	}
	
	return k; //zwracamy wybrany spośród możliwych losowo kierunek
}





void zamianaSciany(lab s, int j, int i, int l)
{
	int stan;
	int k = sprs(s, j, i, &stan, 0);
	int bl = k;
	if(stan == 1)
	{	
		ruchzam(s, &j, &i, k, l);
	} else {
		k = sprs(s, j, i, &stan, bl);
		ruchzam(s, &j, &i, k, l);
	}
	
	k = sprs(s, j, i, &stan, 0);
	
	if(stan != 0)
	{
		zamianaSciany(s, j, i, l);
	}
}


int zamianas(lab s) //tutaj zamiana wszystkich wybranych ścian na pewne liczby zamiast jedynki
{
	int sc = randoms(s); //maksymalna ilość ścian w środku 
	
	
	int sr1, sr2;
	
	srodek(s, &sr1, &sr2);
	int j = 1;
	int i;

	zamianaSciany(s, j, sr1-1, 2);
	zamianaSciany(s, j, sr1+1, 3);

	
	int r;
	for(r = 4; r < sc+3; r++)
	{
		randoml(s, &j, &i);
		zamianaSciany(s, j, i, r);
	}
	
	int l = sc+2;
	return l; //zwraca ilosc ścian
}

void ruchzam(lab s, int *j, int *i, int k, int l) //ruch który zamienia jakąś ścianę z jedynki na inną liczbę wybraną
{
	int stan;
    int bl = k;
	switch(k) //jest sprawdzany kierunek i poruszamy się w nim
	{
		case 1:
			while((s->mat[*j][(*i)-1]).x == 1)
			{
				k = sprs(s, *j, (*i)-1, &stan, 0);
                		if(stan == 2)
                		{
                                k = sprs(s, *j, (*i)-1, &stan, bl);
                    			zamianaSciany(s, *j, (*i)-1, l); //jeżeli istnieje nie jeden kierunek możliwy w pewnym przypadku to spoczątku zmieniamy liczby w w tym powrocie a potem tylko idziemy w początkowym kierunku
                		}
				s->mat[(*j)][(*i)-1].x = l;
				(*i)--;                
			}
			break;
		case 2:
			while((s->mat[(*j)+1][*i]).x == 1)
                        {
				k = sprs(s, (*j)+1, (*i), &stan, 0);
                                if(stan == 2)
                                { 
                                k = sprs(s, (*j)+1, (*i), &stan, bl);
                                        zamianaSciany(s, (*j)+1, (*i), l);
                                }

				
                        	(s->mat[(*j)+1][*i]).x = l;
				(*j)++;
			}
                        break;
		case 3:
			while((s->mat[*j][(*i)+1]).x == 1)
                        {
				k = sprs(s, *j, (*i)+1, &stan, 0); 
                                if(stan == 2)
                                {
                                k = sprs(s, *j, (*i)+1, &stan, bl);
                                        zamianaSciany(s, *j, (*i)+1, l); 
                                }
				
                        	(s->mat[*j][(*i)+1]).x = l;
				(*i)++;       
			}
                        break;
		case 4:
			while((s->mat[(*j)-1][(*i)]).x == 1) 
                        {
				k = sprs(s, (*j)-1, (*i), &stan, 0); 
                                if(stan == 2)
                                {
                                k = sprs(s, (*j)-1, (*i), &stan, bl);
                                        zamianaSciany(s, (*j)-1, (*i), l); 
                                }
				
                        	(s->mat[(*j)-1][(*i)]).x = l;
				(*j)--;
			}
                        break;
	}
}



void tworzenieWektora(lab s, el** elem, int* a, int* aa, int sz) //tutaj jest tworzenie pewnego wektora dla którego jest już alokowana pamięć 
{	
	int j, i; 
	int r;
	int h = 2;
	for(r = 0; r < sz; r++){
		int u = 0;
		aa[r] = h;
		a[r] = 0;
		for(j = 1; j < s->n -1; j++)
		{
			for(i = 1; i < s->n -1; i++)
			{
				if((s->mat[j][i]).x == h){
					(elem[r][u]).j = j;
					(elem[r][u]).i = i;

					a[r]++;
					u++;
				}
			}
		}
		h++;

	}
}


void rysowanieScian(lab s){ //to jest ogólna funkcja która łączy ściany
	zamianas(s);

	int sz = zamianas(s); //losowo ustawiamy malsymalną ilość ścian w labiryncie 
	el **elem;
	elem = (el**)malloc(sizeof *elem * (sz+1));
	int g;
	for(g = 0; g < sz+1; g++)
	{
		elem[g] = (el*)malloc(sizeof *(elem[g]) * 10000);
	}
	srand(clock());
	int *a = malloc(sizeof *a * (sz+1));
	int *aa = malloc(sizeof *aa * (sz+1));
	tworzenieWektora(s, elem, a, aa, sz); //alokacja pamięci dla pewnego wektora i jego zapełnienie 
	int h, r;
	for(h = 0; h < s->n*s->n*10; h++){
		for(r = 0; r < sz; r++){
			int k = 1;
			while(k != 0) //dopóki nie będzie łączona choczaż jedna ściana to pętla się powtarza 
			{
				int i, j;
				int rr = a[r] * ((double)rand()/RAND_MAX); //losowo wybieramy jedną pojedynczą ścianę  która jest zaznaczona pewną cyfrą z wektora stworzonego wcześniej 
				j = (elem[r][rr]).j;
				i = (elem[r][rr]).i;
				
				k = sprss(s, j, i); //sprawdzenie czy możem złączyć ścianę jeżeli jesteśmy w pewnej ścianie pojedynczej 
				ruchsz(s, j, i, k, aa[r], r); //pojedyncze łączenie ściany
				zamianaSciany(s, j, i, aa[r]); //zrobienia tego żeby złączona ściana miała tylko jedną liczbę
						
				tworzenieWektora(s, elem, a, aa, sz);	 //dopełnienie wektora który ma koordynaty każdej pojedynczej ściany z jednej całkowitej ściany
			}
		}
	}
	
	for(h = 0; h < sz+1; h++)
	{
		free(elem[h]);
	}
	free(a);	
	free(aa);
	free(elem);
	

}


int sprss(lab s, int j, int i) //sprawdzenie czy możemy złączyć ścianę i jeżeli możemy to losowo wybieramy kierunek spośród możliwych 
{
	int n = s->n;
	int a[4];
	if(i > 2){
		if((s->mat[j][i-2]).x == 1){ //lewa strona
			a[0] = 1;
		} else {
			a[0] = 0;
		}
	} else {
		a[0] = 0;
	}
	
	if(j < n-2){
		if((s->mat[j+2][i]).x == 1){ //dolna strona
			a[1] = 1;
		} else {
			a[1] = 0;
		}   
	} else {
		a[1] = 0;
	}

	if(i < n-2){	
		if((s->mat[j][i+2]).x == 1){ //prawa strona
			a[2] = 1;
		} else {
			a[2] = 0;
		}   
	} else {
		a[2] = 0;
	}

	if(j > 2){	
		if((s->mat[j-2][i]).x == 1){ //gorna strona
			a[3] = 1;
		} else {
			a[3] = 0;
		}   
	} else {
		a[3] = 0;
	}
	
	
	int k = randomKierunek(a[0], a[1], a[2], a[3]); //losowy wybór kierunku spośród możliwych
		
	return k;
}


void ruchsz(lab s, int j, int i, int k, int h, int r) //łączenie pojedyncze w wybranym kierunku
{
	switch(k)
	{
		case 1:
			(s->mat[j][i-1]).x = h;
			zamianaSciany(s, j, i-2, h);	
			break;
		case 2:
                        (s->mat[j+1][i]).x = h;
                        zamianaSciany(s, j+2, i, h);
			break;
		case 3:
                        (s->mat[j][i+1]).x = h;
                        zamianaSciany(s, j, i+2, h);
			break;
		case 4:
                        (s->mat[j-1][i]).x = h;
                        zamianaSciany(s, j-2, i, h);
			break;
	}
}











