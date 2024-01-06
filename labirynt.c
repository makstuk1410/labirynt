#include "labirynt.h"
#include "mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int randomKierunek(int a, int b, int c, int d)
{
        int s[] = {a, b, c, d}; 
        int suma = 0;
        int i, j;
        for(j = 0; j < 4; j++)
        {
                suma += s[j];
        }
    
        if(suma == 0)
        {
                return 0;
        } else {
                srand(clock());
                int x[5];
                int f = 0;
                for(i = 1; i <= 4; i++)
                {
                        if(s[i-1] == 1)
                        {
                                x[f++] = i;
                        }
                }
                int r = f*((double)rand()/(RAND_MAX));
                int k = x[r];
                return k;
        }
}


int kierunek(int j, int i, lab s, int* p, int* pk, int o)
{
	int n = s->n;
	int act;
	if(o == 0){
		act = randomKierunek(1, 1, 0, 0);
	} else if(o == 1){
		act = 1;
	} else if(o == 2){
		act = 2;
	}
	int a, b, c, d;
	int pki[4];
	switch(act){
		case 1:
			if(i > 2){		
				if((s->mat[j][i-2]).x == 1 || (s->mat[j][i-1]).x == 1)
				{
					a = 0;
				} else {
					a = 1;
				}
			} else {
				a = 0;
			}
			if(j < n-3){
				if((s->mat[j+2][i]).x == 1 || (s->mat[j+1][i]).x == 1)
				{
					b = 0;
				} else {
					b = 1;
				}
			} else {
				b = 0;
			}
			
			if(i < n-3){
				if((s->mat[j][i+2]).x == 1 || (s->mat[j][i+1]).x == 1)
				{
					c = 0;
				} else {
					c = 1;
				}
			} else {
				c = 0;
			}

			if(j > 2){
				if((s->mat[j-1][i]).x == 1 || (s->mat[j-2][i]).x == 1)
				{
					d = 0;
				} else {
					d = 1;
				}
			} else {
				d = 0;
			}


			*p = 1;
			*pk = 0;
			break;
			
		case 2:
			int a1, a2, b1, b2, c1, c2, d1, d2;
			
			if(j < n-1 && i > 1){
				if((s->mat[j+1][i-1]).x == 1 || (s->mat[j+1][i]).x == 1)
				{
					a1 = 0;
				} else {
					a1 = 1;
				}
				
				if((s->mat[j+1][i-1]).x == 1 || (s->mat[j][i-1]).x == 1)
				{
					a2 = 0;
				} else {
					a2 = 1;
				}
				
				a = randomKierunek(a1, a2, 0, 0);
			
			
				switch(a){
					case 0:
						pki[0] = 0;
						break;
					case 1:
						pki[0] = 1;
						break;
					case 2: 
						a = 1;
						pki[0] = 2;
						break;
				}
			} else {
				a = 0;
				pki[0] = 0;
			}
			

			if(j < n-1 && i < n-1){
				if((s->mat[j+1][i+1]).x == 1 || (s->mat[j][i+1]).x == 1)
				{
					b1 = 0;
				} else {
					b1 = 1;
				}
				
				if((s->mat[j+1][i+1]).x == 1 || (s->mat[j+1][i]).x == 1)
				{
					b2 = 0;
				} else {
					b2 = 1;
				}

				b = randomKierunek(b1, b2, 0, 0);
				
				switch(b){
					case 0:
						pki[1] = 0;
						break;
					case 1:
						pki[1] = 1;
						break;
					case 2:
						b = 1;
						pki[1] = 2;
						break;
				}
			} else {
				b = 0;
				pki[1] = 0;
			}
		

			if(j > 1 && i < n-1){
				if((s->mat[j-1][i+1]).x == 1 || (s->mat[j][i+1]).x == 1)
				{
					c1 = 0;
				} else {
					c1 = 1;
				}
				
				if((s->mat[j-1][i+1]).x == 1 || (s->mat[j-1][i]).x == 1)
				{
					c2 = 0;
				} else {
					c2 = 1;
				}
				
				c = randomKierunek(c1, c2, 0, 0);

				switch(c){
					case 0:
						pki[2] = 0;
						break;
					case 1:
						pki[2] = 1;
						break;
					case 2:
						c = 1;
						pki[2] = 2;
						break;
				}
			} else {
				c = 0;
				pki[2] = 0;
			}
			


			if(j > 1 && i > 1){
				if((s->mat[j-1][i-1]).x == 1 || (s->mat[j][i-1]).x == 1)
				{
					d1 = 0;
				} else {
					d1 = 1;
				}
				
				if((s->mat[j-1][i-1]).x == 1 || (s->mat[j-1][i]).x == 1)
				{
					d2 = 0;
				} else {
					d2 = 1;
				}
				
				d = randomKierunek(d1, d2, 0, 0);
				
				switch(d){
					case 0:
						pki[3] = 0;
						break;
					case 1:
						pki[3] = 1;
						break;
					case 2:
						d = 1;
						pki[3] = 2;
						break;
				}

				*p = 2;
			} else {
				d = 0;
				pki[3] = 0;
			}
			break;

	}
	
	int k = randomKierunek(a, b, c, d);
	if(k == 0 && *p == 2){
		kierunek(j, i, s, p, pk, 1);
	} else if (k == 0 && *p == 1) {
		kierunek(j, i, s, p, pk, 2);
	} else if(k != 0) {
		switch(*p){
			case 1:
				*pk = 0;
				return k;
				break;
			case 2: 
				switch(k){
					case 1:
						*pk = pki[0];
						break;
					case 2: 
						*pk = pki[1];
						break;
					case 3:
						*pk = pki[2];
						break;
					case 4:
						*pk = pki[3];
						break;
				}
				return k;
				break;
		}
	}
	return k;
}



void ruch(int *j, int *i, lab s)
{
	int p;
	int pk;
	int k = kierunek(*j, *i, s, &p, &pk, 0);
	if(k == 0)
	{
		return;
	}
	switch(k){
                case 1:
    			if(p == 1)
			{
				(s->mat[(*j)][(*i)-1]).x = 0;
				(s->mat[*j][(*i)-2]).x = 0;
				*i = (*i) - 2;
			} else if(p == 2) {
				switch(pk){
					case 1:
						(s->mat[(*j)+1][(*i)-1]).x = 0;
						(s->mat[(*j)+1][(*i)]).x = 0;
						*i = (*i) - 1;
						*j = (*j) + 1;
						break;
					case 2:
						(s->mat[(*j)+1][(*i)-1]).x = 0;
                                                (s->mat[(*j)][(*i)-1]).x = 0;
                                                *i = (*i) - 1;
                                                *j = (*j) + 1;
                                                break;
				}
			}
                        break;
                case 2:
    			if(p == 1)
                        {
                                (s->mat[(*j)+1][(*i)]).x = 0;
                                (s->mat[(*j)+2][(*i)]).x = 0;
                                *j = (*j) + 2;
                        } else if(p == 2) {
                                switch(pk){
                                        case 1:
                                                (s->mat[(*j)+1][(*i)+1]).x = 0;
                                                (s->mat[(*j)][(*i)+1]).x = 0;
                                                *i = (*i) + 1;
                                                *j = (*j) + 1;
                                                break;
                                        case 2:
                                                (s->mat[(*j)+1][(*i)]).x = 0;
                                                (s->mat[(*j)+1][(*i)+1]).x = 0;
                                                *i = (*i) + 1;
                                                *j = (*j) + 1;
                                                break;
                                }

                        }

                        break;
                case 3:
    			if(p == 1)
                        {
                                (s->mat[(*j)][(*i)+1]).x = 0;
                                (s->mat[(*j)][(*i)+2]).x = 0;
                                *i = (*i) + 2;
                        } else if(p == 2) {
                                switch(pk){
                                        case 1:
                                                (s->mat[(*j)][(*i)+1]).x = 0;
                                                (s->mat[(*j)-1][(*i)+1]).x = 0;
                                                *i = (*i) + 1;
                                                *j = (*j) - 1;
                                                break;
                                        case 2:
                                                (s->mat[(*j)-1][(*i)]).x = 0;
                                                (s->mat[(*j)-1][(*i)+1]).x = 0;
                                                *i = (*i) + 1;
                                                *j = (*j) - 1;
                                                break;
                                }

                        }

                        break;
                case 4:
    			if(p == 1)
                        {
                                (s->mat[(*j)-1][(*i)]).x = 0;
                                (s->mat[(*j)-2][(*i)]).x = 0;
                                *j = (*j) - 2;
                        } else if(p == 2) {
				switch(pk){
                                        case 1:
                                                (s->mat[(*j)][(*i)-1]).x = 0;
                                                (s->mat[(*j)-1][(*i)-1]).x = 0;
                                                *i = (*i) - 1;
                                                *j = (*j) - 1;
                                                break;
                                        case 2:
                                                (s->mat[(*j)-1][(*i)]).x = 0;
                                                (s->mat[(*j)-1][(*i)-1]).x = 0;
                                                *i = (*i) - 1;
                                                *j = (*j) - 1;
                                                break;
                                }
                                
                        }

                        break;
        }
	
}






void sprawdzenie(lab s)
{
	int n = s->n-1;
	
	int i, j;
	for(j = 3; j < n-2; j += 2)
	{
		for(i = 3; i < n-2; i += 2)
		{
			int m = 0;
			if((s->mat[j][i+1]).x == 0 && (s->mat[j+1][i+1]).x == 0 && (s->mat[j-1][i+1]).x == 0){
				if((s->mat[j-1][i]).x == 0){
					m++;
				} else if ((s->mat[j-1][i]).x == 1){
					m--;
				}
				
				if((s->mat[j-1][i-1]).x == 0)
					m++;
				
				if((s->mat[j+1][i]).x == 0){
                                        m++;
				} else if((s->mat[j+1][i]).x == 1){
					m--;
				}

				if((s->mat[j+1][i-1]).x == 0)
                                        m++;
				
				if(m > 2)
				{
					(s->mat[j][i-1]).x = 1;
				}
			} 
			m = 0;
			if((s->mat[j+1][i+1]).x == 0 && (s->mat[j+1][i]).x == 0 && (s->mat[j+1][i-1]).x == 0){ 
                                if((s->mat[j][i+1]).x == 0){
                                        m++;
				} else if((s->mat[j][i+1]).x == 1) {
					m--;
				}
                     
                                if((s->mat[j][i-1]).x == 0){
                                        m++;
				} else if ((s->mat[j][i-1]).x == 1){
					m--;
				}

                                if((s->mat[j-1][i+1]).x == 0)
                                        m++;

                                if((s->mat[j-1][i-1]).x == 0)
                                        m++;

                                if(m > 2)
                                {
                                        (s->mat[j-1][i]).x = 1;
                                }
                        }
			m = 0;
			if((s->mat[j][i-1]).x == 0 && (s->mat[j+1][i-1]).x == 0 && (s->mat[j-1][i-1]).x == 0){ 
                                if((s->mat[j+1][i]).x == 0){
                                        m++;
				} else if ((s->mat[j+1][i]).x == 1) {
					m--;
				}
                     
                                if((s->mat[j+1][i+1]).x == 0)
                                        m++;

                                if((s->mat[j-1][i]).x == 0){
                                        m++;
				} else if((s->mat[j-1][i]).x == 1){
					m--;
				}

                                if((s->mat[j-1][i+1]).x == 0)
                                        m++;

                                if(m > 2)
                                {
                                        (s->mat[j][i+1]).x = 1;
                                }
                        }
			m = 0;
			if((s->mat[j-1][i+1]).x == 0 && (s->mat[j-1][i]).x == 0 && (s->mat[j-1][i-1]).x == 0){ 
                                if((s->mat[j][i-1]).x == 0){
                                        m++;
				} else if((s->mat[j][i-1]).x == 1){
					m--;
				}
                     
                                if((s->mat[j][i+1]).x == 0){
                                        m++;
				} else if((s->mat[j][i+1]).x == 1) {
					m--;
				}

                                if((s->mat[j+1][i+1]).x == 0)
                                        m++;

                                if((s->mat[j+1][i-1]).x == 0)
                                        m++;

                                if(m > 2)
                                {
                                        (s->mat[j+1][i]).x = 1;
                                }
                        }			
		}
	}
}




void rysowanie(lab s)
{
	int r;
	double sr; 
        int sr1, srr;
        int n = s->n;
        int n1 = (n-1) / 2;
        sr = n1 % 2;
        srr = n / 2;
    
        if(sr != 0)
        {
                sr1 = srr;
        } else if(sr == 0) {
                sr1 = srr-1;
        }

	int j = 2;
	int i = sr1;

	for(r = 0; r < n1*n1*n1*10; r++)
	{
		ruch(&j, &i, s);
		sprawdzenie(s);
	}
}





















