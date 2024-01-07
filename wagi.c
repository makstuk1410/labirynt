#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mat.h"
#include "labirynt.h"
#include "sciana.h"
#include "wagi.h"



void insert(Node **root, int i, int j, double waga)
{
	Node* new_node = malloc(sizeof(Node));

	if(new_node == NULL)
	{
		exit(1);
	}


	new_node->next = NULL;
	new_node->waga = waga;
	new_node->j = j;
	new_node->i = i;

	if(*root == NULL)
	{
		*root = new_node;
		return;
	}

	Node* curr = *root;
	while(curr->next != NULL)
	{
		curr = curr->next;
	}
	curr->next = new_node;
}


void remove_element(Node **root, int j, int i)
{
	if(*root == NULL)
	{
		return;
	}

	if((*root)->i == i && (*root)->j == j)
	{
		Node* tmp = *root;
		*root = (*root)->next;
		free(tmp);	
		return;
	}

	Node* curr = *root;
	
	while(curr->next != NULL)
	{
		if(curr->next->j == j && curr->next->i == i)
		{
			Node* tmp = curr->next;
			curr->next = curr->next->next;
			free(tmp);
			return;
		}
		curr = curr->next;
	}
	

	return;
}


void dealloc(Node** root)
{
	Node* curr = *root;
	while(curr != NULL)
	{
		Node* aux = curr;
		curr = curr->next;
		free(aux);
	}
	*root = NULL;

}




double randomWaga(void)
{
	srand(clock());
	
	double r = 10 * ((double)rand()/RAND_MAX);
	
	return r;
}

void wagiLab(lab s)
{
	int n = s->n;
	int j, i;
	for(j = 2; j < n-2; j++)
	{
		for(i = 2; i < n-2; i++)
		{
			if((s->mat[j][i]).x == 0){
				double r = randomWaga();
				(s->mat[j][i]).waga = r;
			}	
		}
	}
}


void printWagi(lab s)
{
	int i, j;
        for(i = 0; i < s->n; i++)
        {
                for(j = 0; j < s->n; j++)
                {
                        if ((s->mat[i][j]).x == 1)
                        {
                                printf("\033[47m  \033[0m");  // Ściana
                        } else {
                                printf("%g ", (s->mat[i][j]).waga);  // Przejście
                        }
                }
                printf("\n");
        }

}




void najmniejszaSciezka(lab s)
{
	int n = s->n;
	int sr1, sr2;
	srodek(s, &sr1, &sr2);
	int j = 2;
	int i = sr1;
	(s->mat[j-1][i]).x = 1;
	(s->mat[n-2][sr2]).x =1;
	el **elem;
	elem = (el**)malloc(sizeof *elem * (10*n * n));
	int g;
	for(g = 0; g < 10*n*n; g++)
	{
		elem[g] = (el*)malloc(sizeof *(elem[g]) * 10*n*n);
	}
	
	int *a = malloc(sizeof *a * n * n * 10); //wektor dla ilości koordynat
	double *aa = malloc(sizeof *aa * n * n*10); //wektor dla zapisywanie wagi ścieżki
	
	int t;
	int u;
	for(t = 0; t < n*n*10; t++)
	{
		j = 2;
		i = sr1;
		Node* root = NULL;
		insert(&root, sr1, 1, 0);
		insert(&root, sr1, 2, (s->mat[2][sr1]).waga);
		while(j != n-3 || i != sr2){
			ruchSciezki(&j, &i, s, &root, 0, sr1);
		}
		insert(&root, sr2, n-2, 0);
		zapisywanieDoWektora(s, elem, a, aa, t, &root);
		zamianaLabSc(s);
		dealloc(&root);
	}

	sciezka wagisciezki[n*10*n];

	(wagisciezki[0]).waga = aa[0];
	(wagisciezki[0]).numer = 0;
	int w;
	int m = 1;
	int p;
	int b;
	for(w = 1; w < t; w++)
	{
		p = 0;
		for(b = 0; b < m; b++)
		{
			if(aa[w] == (wagisciezki[b]).waga)
			{
				p = 1;
				break;
			}
		}
	
		if(p == 0){
			(wagisciezki[m]).numer = w;
                        (wagisciezki[m]).waga = aa[w];
			m++;
		}
	}

	int gg;
	for(gg = m; gg < n*n*10; gg++)
	{
		(wagisciezki[gg]).numer = 1000000;
		(wagisciezki[gg]).waga = 1000000;
	}
	
	printf("\nTutaj są wyświetlone wszystkie ścieżki:\n");

	double yy = 0;
	int hh = 0;
	for(p = 0; p < m; p++)
	{
		if(yy != (wagisciezki[p]).waga){
			hh++;
			printf("Scieżka numer %d ma wagę: %f\n", hh, (wagisciezki[p]).waga);
			int numer = (wagisciezki[p]).numer;
			for(u = 0; u < a[numer]; u++)
	        	{
        	        	(s->mat[(elem[numer][u]).j][(elem[numer][u]).i]).x = 3;
        		}
			printLab(s);
			zamianaLabSc(s);
		}
		yy = (wagisciezki[p]).waga;
	}
	
	printf("\nCzyli w labiryncie są %d ścieżek\n", hh);

	int numer = 0;
	double x = (wagisciezki[0]).waga;
	
	for(p = 1; p < m; p++)
	{
		if((wagisciezki[p]).waga < x){
			x = (wagisciezki[p]).waga;
			numer = (wagisciezki[p]).numer;
		}
	}

	
	
	for(u = 0; u < a[numer]; u++)
	{
		(s->mat[(elem[numer][u]).j][(elem[numer][u]).i]).x = 3;
	}
	
	printf("\n najmniejsza waga scieżki w labiryncie to %g\n", x);

	printLab( s );

	int h;
	for(h = 0; h < n*n*10; h++)
	{
		free(elem[h]);
	}
	free(a);	
	free(aa);
	free(elem);
}



void zapisywanieDoWektora(lab s, el** elem, int* a, double* aa, int t, Node **root)
{	
	int g = 0;
	double waga = 0;
	for(Node* curr = *root; curr != NULL; curr = curr->next)
	{
		(elem[t][g]).j = curr->j;
		(elem[t][g]).i = curr->i;
		waga += curr->waga; 
		g++;
	}
	a[t] = g;
	aa[t] = waga;
}



int kierunekSciezki(int j, int i, lab s, int mode, int* mod, int* bl)
{
	int n = s->n;
	int a, b, c, d;
	
	if(i > 2){		
		if((s->mat[j][i-2]).x == 1 || (s->mat[j][i-1]).x == 1 || (s->mat[j][i-2]).x == 2 || (s->mat[j][i-1]).x == 2)
		{
			a = 0;
		} else {
			if((s->mat[j][i-2]).x == 3 || (s->mat[j][i-1]).x == 3){ 
				if((s->mat[j][i-2]).x == 3 && (s->mat[j][i-1]).x == 0){
					a = 0;
				} else if(mode == 0){
					a = 0;
				} else {
					if(*bl == 1){
						a = 0;
					} else {
						a = 1;
					}
				}
			} else {
				a = 1;
			}
		}
	} else {
		a = 0;
	}

	if(j < n-3){
		if((s->mat[j+2][i]).x == 1 || (s->mat[j+1][i]).x == 1 || (s->mat[j+2][i]).x == 2 || (s->mat[j+1][i]).x == 2)
		{
			b = 0;
		} else {
			if((s->mat[j+2][i]).x == 3 || (s->mat[j+1][i]).x == 3){ 
				if((s->mat[j+2][i]).x == 3 && (s->mat[j+1][i]).x == 0){
					b = 0;
				} else if(mode == 0){ 
					b = 0;
				} else {
					if(*bl == 2){ 
                                                b = 0;
                                        } else {	
                                                b = 1;
                                        } 
				}   
			} else {
				b = 1;
			}
		}
	} else {
		b = 0;
	}
	
	if(i < n-3){
		if((s->mat[j][i+2]).x == 1 || (s->mat[j][i+1]).x == 1 || (s->mat[j][i+2]).x == 2 || (s->mat[j][i+1]).x == 2)
		{
			c = 0;
		} else {
			if((s->mat[j][i+2]).x == 3 || (s->mat[j][i+1]).x == 3){ 
				if((s->mat[j][i+2]).x == 3 && (s->mat[j][i+1]).x == 0){
					c = 0;
				} else if(mode == 0){ 
					c = 0;
				} else {
					if(*bl == 3){ 
                                                c = 0;
                                        } else {
						
                                                c = 1;
                                        } 
				}   
			} else {
				c = 1;
			}

		}
	} else {
		c = 0;
	}

	if(j > 2){
		if((s->mat[j-1][i]).x == 1 || (s->mat[j-2][i]).x == 1 || (s->mat[j-1][i]).x == 2 || (s->mat[j-2][i]).x == 2)
		{
			d = 0;
		} else {
			if((s->mat[j-1][i]).x == 3 || (s->mat[j-2][i]).x == 3){ 
				if((s->mat[j-1][i]).x == 0 && (s->mat[j-2][i]).x == 3){
					d = 0;
				} else if(mode == 0){ 
					
					d = 0;
				} else {
					if(*bl == 4){ 
                                                d = 0;
                                        } else {
                                                d = 1;
                                        } 
				}   
			} else {
				d = 1;
			}

		}
	} else {
		d = 0;
	}

	
	int k = randomKierunek(a, b, c, d);
	
	if(k == 0 && mode == 0)
	{
		return k;
	} else if (mode == 1){
		if(k == 1)
		{
			*bl = 3;
		} else if(k == 2){
			*bl = 4;
		} else if(k == 3){
			*bl = 1;
		} else if(k == 4){
			*bl = 2;
		}	
		*mod = 1;
	} else if(k != 0 && mode == 0)
	{
		*bl = 0;
		*mod = 0;
	}
	
	return k;
}



void ruchSciezki(int *j, int *i, lab s, Node** root, int bl, int sr)
{
	int mod = 0;
	int bll = 0;
	int k = kierunekSciezki(*j, *i, s, 0, &mod, &bll);
	
	if(k == 0)
	{
		k = kierunekSciezki(*j, *i, s, 1, &mod, &bl);
	}
	switch(k){
                case 1:
			if(mod == 0){
				insert(root, (*i)-2, (*j), (s->mat[*j][(*i)-2]).waga);
				insert(root, (*i)-1, (*j), 0);
				(s->mat[(*j)][(*i)-1]).x = 3;
                       		(s->mat[*j][(*i)-2]).x = 3;	
			} else {
				remove_element(root, *j, *i);
				remove_element(root, (*j), (*i)-1);
				(s->mat[(*j)][(*i)]).x = 2;
			}

			*i = (*i) - 2;
			break;
                case 2:
			if(mod == 0){
				insert(root, (*i), (*j)+2, (s->mat[(*j)+2][(*i)]).waga);
				insert(root, (*i), (*j)+1, 0);
				(s->mat[(*j)+1][(*i)]).x = 3;
                        	(s->mat[(*j)+2][(*i)]).x = 3;
			} else {
                                remove_element(root, *j, *i);
				remove_element(root, (*j)+1, *i);
				(s->mat[(*j)][(*i)]).x = 2;
			}

			*j = (*j) + 2;

                        break;
                case 3:
			if(mod == 0){
				insert(root, (*i)+2, (*j), (s->mat[(*j)][(*i)+2]).waga);
				insert(root, (*i)+1, (*j), 0);
				(s->mat[(*j)][(*i)+1]).x = 3;
                        	(s->mat[(*j)][(*i)+2]).x = 3;
			} else {
                                remove_element(root, *j, *i);
				remove_element(root, *j, (*i)+1);
				(s->mat[(*j)][(*i)]).x = 2;
			}

			*i = (*i) + 2;
            
                        break;
                case 4:
			if(mod == 0){
				insert(root, (*i), (*j)-2, (s->mat[(*j)-2][(*i)]).waga);
				insert(root, (*i), (*j)-1, 0);
				(s->mat[(*j)-1][(*i)]).x = 3;
	                        (s->mat[(*j)-2][(*i)]).x = 3;
			} else {
                        	remove_element(root, *j, *i);
				remove_element(root, (*j)-1, *i);
				(s->mat[(*j)][(*i)]).x = 2;
			}

			*j = (*j) - 2;

                        break;
        }
	
	
	
	if(*j == 2 && *i == sr)
	{
		return;
	} else if(mod == 1){
		ruchSciezki(j, i, s, root, bl, sr);
	} else {
		return;
	}
}











