#include "labirynt.h"
#include "mat.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int randomKierunek(int a, int b, int c, int d) //funkcja która wybiera jedną z czterech podanych jako argumenty liczb(1 lub 0, najczęściej tak jest zaznaczany kierunek) i zwraca numer w rzędzie losowo wybranej liczby
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


int kierunek(int j, int i, lab s, int* p, int* pk, int o) //szukanie możliwych kierunków i wybór losowego spośród możliwych 
{
	int n = s->n;
	int act;
    //tutaj wybieramy losowo jeżeli jest możliwość czy będziemy powracać czy idziemy wprost w labiryncie
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
		case 1: //przypadek kiedy idziemy wprost
			if(i > 2){		
				if((s->mat[j][i-2]).x == 1 || (s->mat[j][i-1]).x == 1) //sprawdzenia czy można iść w lewo
				{
					a = 0;
				} else {
					a = 1;
				}
			} else {
				a = 0;
			}
			if(j < n-3){
				if((s->mat[j+2][i]).x == 1 || (s->mat[j+1][i]).x == 1) //sprawdzenia czy można iść w dół
				{
					b = 0;
				} else {
					b = 1;
				}
			} else {
				b = 0;
			}
			
			if(i < n-3){
				if((s->mat[j][i+2]).x == 1 || (s->mat[j][i+1]).x == 1) //sprawdzenie czy można iść w prawo
				{
					c = 0;
				} else {
					c = 1;
				}
			} else {
				c = 0;
			}

			if(j > 2){
				if((s->mat[j-1][i]).x == 1 || (s->mat[j-2][i]).x == 1) //sprawdzenie czy można iść do góry
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
			
		case 2: //tutaj sprawdzamy czy można powracać. powracać można zawsze w dwa sposoby dla zprawdzane są obydwie możliwości 
			int a1, a2, b1, b2, c1, c2, d1, d2;
			
			if(j < n-1 && i > 1){ 
				if((s->mat[j+1][i-1]).x == 1 || (s->mat[j+1][i]).x == 1) //sprawdzenie czy można powracać w lewo w dół jednym sposobem
				{
					a1 = 0;
				} else {
					a1 = 1;
				}
				
				if((s->mat[j+1][i-1]).x == 1 || (s->mat[j][i-1]).x == 1)//sprawdzenie czy można powracać w lewo w dół drugim sposobem
				{
					a2 = 0;
				} else {
					a2 = 1;
				}
				
				a = randomKierunek(a1, a2, 0, 0);  //losowy wybór spośród dwóch możliwych sposobów powrotów w lewo w dół
			
 //zaznaczenie wybranego sposobu powrotu
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
				if((s->mat[j+1][i+1]).x == 1 || (s->mat[j][i+1]).x == 1)  //sprawdzenie czy można powracać w prawo w dół jednym sposobem
				{
					b1 = 0;
				} else {
					b1 = 1;
				}
				
				if((s->mat[j+1][i+1]).x == 1 || (s->mat[j+1][i]).x == 1) //sprawdzenie czy można powracać w prawo w dół drugim sposobem
				{
					b2 = 0;
				} else {
					b2 = 1;
				}

				b = randomKierunek(b1, b2, 0, 0);
				//zaznaczenie wybranego losowo sposobu powrotu
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
				if((s->mat[j-1][i+1]).x == 1 || (s->mat[j][i+1]).x == 1) //sprawdzenie czy można powracać w prawo w górę jednym sposobem
				{
					c1 = 0;
				} else {
					c1 = 1;
				}
				
				if((s->mat[j-1][i+1]).x == 1 || (s->mat[j-1][i]).x == 1) //sprawdzenie czy można powracać w prawo w górę drugim sposobem
				{
					c2 = 0;
				} else {
					c2 = 1;
				}
				
				c = randomKierunek(c1, c2, 0, 0);
                //zaznaczenie wybranego losowo sposobu powrotu
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
				if((s->mat[j-1][i-1]).x == 1 || (s->mat[j][i-1]).x == 1)  //sprawdzenie czy można powracać w lewo w górę jednym sposobem
				{
					d1 = 0;
				} else {
					d1 = 1;
				}
				
				if((s->mat[j-1][i-1]).x == 1 || (s->mat[j-1][i]).x == 1) //sprawdzenie czy można powracać w lewo w górę drugim sposobem
				{
					d2 = 0;
				} else {
					d2 = 1;
				}
				
				d = randomKierunek(d1, d2, 0, 0);
				//zaznaczenie losowo wybranego sposobu powrotu 
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
	
	int k = randomKierunek(a, b, c, d); //tutaj jest wybierany jeden kierunek spośród możliwych za pomocy funkcji
	if(k == 0 && *p == 2){
		kierunek(j, i, s, p, pk, 1); //jeżeli losowo wybrany powrót nie ma możliwych kierunków to rekurencyjnie wywołujemy funkcje jeszcze jeden raz żeby sprawdzić czy jest możliwy ruch wprost 
	} else if (k == 0 && *p == 1) {
		kierunek(j, i, s, p, pk, 2); //jeżeli losowo wybrany ruch wprost nie ma możliwych kierunków to rekurencyjnie wywołujemy funkcje jeszcze jeden raz żeby sprawdzić czy jest możliwy powrót 
	} else if(k != 0) { //jeżeli istnieje kierunek wybrany losowo
		switch(*p){ //to sprawdzamy czy to jest powrót:
			case 1: //jeżeli nie to zaznaczamy to i zwracamy wybrany kierunek ruchu wprost
				*pk = 0;
				return k;
				break;
			case 2: //jeżeli tak to zaznaczamy jakim sposobem powracamy i zwracamy numer kierunku powrotu
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



void ruch(int *j, int *i, lab s) //funkcja dla ruchu w labiryncie  w wybranym kierunku
{
	int p;
	int pk;
	int k = kierunek(*j, *i, s, &p, &pk, 0); //wybór kierunku losowego spośród możliwych
	if(k == 0)
	{
		return;
	}
    //tutaj w wybranym kierunku powrotu lub ruchu wprost zmieniamy jedynki na zera i potem zmieniamy za pomocy wskaźników wartość i oraz j
	switch(k){ //poruszamy się w zależności od kierunku
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






void sprawdzenie(lab s) //funkcja jaka sprawdza czy trzeba budować ścianę
{
	int n = s->n-1;
	
	int i, j; //tutaj przechodzimy przez każdą początkową jedynkę i sprawdzamy prosty przypadek kiedy musimy zbudować ścianę
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




void rysowanie(lab s) //funkcja która tworzy pierwszy etap labiryntu
{
	int r;
	double sr; //szukamy koordynaty z których będziemy zaczynać "rysowanie" labiryntu
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
	int i = sr1; //tutaj koordynaty już są ustawione
    
	for(r = 0; r < n1*n1*n1*10; r++) // pętla która jest powtarzana bardzo dużo razy żeby labirynt został "narysowany" (wiem że można było zrobić to lepiej ale nie miałem dużo czasu na optymizację 
	{
		ruch(&j, &i, s); //ruch
		sprawdzenie(s);  //i odrazu sprawdzenie 
	}
}





















