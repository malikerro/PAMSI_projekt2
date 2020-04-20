#include <iostream>
#include <cstdlib>
#include <cmath>

template <int Rozmiar_tab>
class Algorytm {

    int *Pomocnicza;

    public:

    // konstruktor klasy Algorytm
    Algorytm(){
        Pomocnicza = new int[Rozmiar_tab];
    }

    // destruktor klasy algorytm
    ~Algorytm(){
        delete[] Pomocnicza;
    }



    /**************************************************************/
    // funkcje używane w algorytmie merge sort:
    /*-----------------------------------------------------------*/


    // funkcja "merge" scalająca posortowane podtablice
    void merge (int *Tab_wej, int LewyInd, int SrodInd, int PrawyInd, bool Odwrocenie) {

        // przypisanie wartości tablicy wejściowej do tablicy pomocniczej
        for (int i = LewyInd; i <= PrawyInd; i++) {
            Pomocnicza[i] = Tab_wej[i];
        }

        // LewyElem i PrawyElem - indeksy porównywanych wyrazów
        int LewyElem = LewyInd, PrawyElem = SrodInd + 1;

        if(!Odwrocenie) {   // wariant posortowania w kolejności od min do max wartości
            for(int biezacy = LewyInd; biezacy <= PrawyInd; biezacy++) {
                if(LewyElem <= SrodInd) { // i = LewyElem, j = PrawyElem, k = biezacy
                    if(PrawyElem <= PrawyInd) {
                        if(Pomocnicza[PrawyElem] < Pomocnicza[LewyElem]) {
                            Tab_wej[biezacy] = Pomocnicza[PrawyElem++];
                        } else { Tab_wej[biezacy] = Pomocnicza[LewyElem++]; }
                    } else { Tab_wej[biezacy] = Pomocnicza[LewyElem++]; }
                } else { Tab_wej[biezacy] = Pomocnicza[PrawyElem++]; }
            }

        } else {    // wariant posortowania w odwrotnej kolejności
            for(int biezacy = PrawyInd; biezacy >= LewyInd; biezacy--) {
                if(LewyElem <= SrodInd) { // i = LewyElem, j = PrawyElem, k = biezacy
                    if(PrawyElem <= PrawyInd) {
                        if(Pomocnicza[PrawyElem] < Pomocnicza[LewyElem]) {
                        Tab_wej[biezacy] = Pomocnicza[PrawyElem++];
                        } else { Tab_wej[biezacy] = Pomocnicza[LewyElem++]; }
                    } else { Tab_wej[biezacy] = Pomocnicza[LewyElem++]; } // jeśli coś nie będzie działało,
                } else { Tab_wej[biezacy] = Pomocnicza[PrawyElem++]; }    // to w tych dwóch linijkach trzeba zamienić LewyInd z PrawyInd
            }
        }
        
        //delete[] Pomocnicza;
    }


    // funkcja dokonująca podziału tablicy na podtablice
    // i właściwego sortowania przez scalanie
    // wywoływana rekurencyjnie
    void m_sort (int *Tab_wej, int LewyInd, int PrawyInd, bool Odwrocenie) {
	    
	    if(PrawyInd <= LewyInd) return; // sytuacja gdy został już tylko jeden element 
	
	    int SrodInd = (PrawyInd + LewyInd)/2;  // indeks elementu środkowego, zostanie zaokrąglony w dół
	
	    //  podział tablicy na dwie części
	    m_sort(Tab_wej, LewyInd, SrodInd, 0); 
	    m_sort(Tab_wej, SrodInd + 1, PrawyInd, 0);
	
        //  scalanie posortowanych tablic
	    merge(Tab_wej, LewyInd, SrodInd, PrawyInd, Odwrocenie);
    }


    // ostateczna funkcja wywołująca i ustalająca parametry
    // funkcji m_sort, tak żeby można ją było łatwo wywołać w mainie
    void merge_sort (int Tab_wej[Rozmiar_tab], bool Odwrocenie) {

        // wywołanie funkcji m_sort przy użyciu parametrów podanych funkcji merge_sort
        // potrzebne do wyznaczenia parametrów: "LewyInd" i "PrawyInd" w pierwszym
        // wywołaniu funkcji
        m_sort(Tab_wej, 0, Rozmiar_tab - 1, Odwrocenie);
    }

    /**************************************************************/
    /**************************************************************/




    /**************************************************************/
    // funkcje używane w algorytmie quick sort:
    /*-----------------------------------------------------------*/


    // właściwa funkcja sortująca q_sort wywoływana rekurencyjnie
    void q_sort (int *Tab_wej, int LewyInd, int PrawyInd, bool Odwrocenie) {
    
        int lewy, prawy, pivot, PivotInd;
        int n = PrawyInd - LewyInd + 1;

        if(LewyInd < PrawyInd) {
            if(!Odwrocenie) {

                // indeks pivota jest losowany z zakresu od LewyInd do n + LewyInd,
                // czyli od pierwszego, do ostatniego indeksu sortowanej tablicy
                PivotInd = rand() % n + LewyInd;
                pivot = Tab_wej[PivotInd];

                // zamieniamy pivot z pierwszym elementem
                Tab_wej[PivotInd] = Tab_wej[LewyInd];
                Tab_wej[LewyInd] = pivot;

                lewy = LewyInd;
                prawy = PrawyInd;

                while(lewy < prawy) {
                    while(Tab_wej[lewy] <= pivot && lewy < PrawyInd) {
                        lewy++;
                    }
                    while(Tab_wej[prawy] > pivot && prawy > LewyInd) {
                        prawy--;
                    }
                    if(lewy < prawy) {
                        // ustawiamy wszystkie elementy mniejsze i większe od pivota
                        // po dwóch stronach - zamieniamy jeśli są po złej stronie
                        std::swap(Tab_wej[lewy], Tab_wej[prawy]);
                    }
                }
        
                // ustawienie pivota na prawidłowej pozycji
                std::swap(Tab_wej[LewyInd], Tab_wej[prawy]);

                // wywołanie q_sort dla prawej i lewej podtablicy
                q_sort(Tab_wej, LewyInd, prawy - 1, Odwrocenie);
                q_sort(Tab_wej, prawy + 1, PrawyInd, Odwrocenie);
                
            } else {

                // indeks pivota jest losowany z zakresu od LewyInd do n + LewyInd,
                // czyli od pierwszego, do ostatniego indeksu sortowanej tablicy
                PivotInd = rand() % n + LewyInd;
                pivot = Tab_wej[PivotInd];

                // zamieniamy pivot z pierwszym elementem
                Tab_wej[PivotInd] = Tab_wej[PrawyInd];
                Tab_wej[PrawyInd] = pivot;

                lewy = LewyInd;
                prawy = PrawyInd;

                while(lewy < prawy) {
                    while(Tab_wej[lewy] > pivot && lewy < PrawyInd) {
                        lewy++;
                    }
                    while(Tab_wej[prawy] <= pivot && prawy > LewyInd) {
                        prawy--;
                    }
                    if(lewy < prawy) {
                        // ustawiamy wszystkie elementy mniejsze i większe od pivota
                        // po dwóch stronach - zamieniamy jeśli są po złej stronie
                        std::swap(Tab_wej[lewy], Tab_wej[prawy]);
                    }
                }
        
                // ustawienie pivota na prawidłowej pozycji
                std::swap(Tab_wej[PrawyInd], Tab_wej[lewy]);

                // wywołanie q_sort dla prawej i lewej podtablicy
                q_sort(Tab_wej, LewyInd, lewy - 1, Odwrocenie);
                q_sort(Tab_wej, lewy + 1, PrawyInd, Odwrocenie);      
            }
            
        }
        return;
    }


    void quick_sort (int Tab_wej[Rozmiar_tab], bool Odwrocenie) {
    
        //  wywołanie funkcji q_sort przy użyciu parametrów podanych funkcji quick_sort,
        //  dla ułatwienia rekurencyjności, analogicznie jak w merge_sort
        q_sort(Tab_wej, 0, Rozmiar_tab - 1, Odwrocenie);
    }

    /**************************************************************/
    /**************************************************************/




    /**************************************************************/
    // funkcje używane w algorytmie intro sort:
    /*-----------------------------------------------------------*/


    // sortowanie przez wstawianie wykorzystywane w głównym algorytmie
    // sortowania introspektywnego
    void insert_sort (int *Tab_wej, int LewyInd, int PrawyInd, bool Odwrocenie) {
        int pomocnicza, j;
        int n = PrawyInd - LewyInd + 1;

        for (int i = LewyInd + 1; i < LewyInd + n; ++i) {
            if (!Odwrocenie) {
                if (Tab_wej[i] < Tab_wej[i - 1]) {
                    j = i;
                    pomocnicza = Tab_wej[i];
                    while (pomocnicza < Tab_wej[j - 1] && j > LewyInd ) {
                        Tab_wej[j] = Tab_wej[j - 1];
                        --j;
                    }
                    Tab_wej[j] = pomocnicza;
                }
            } else {
                if (Tab_wej[i] > Tab_wej[i - 1]) {
                    j = i;
                    pomocnicza = Tab_wej[i];
                    while (pomocnicza > Tab_wej[j - 1] && j > LewyInd ) {
                        Tab_wej[j] = Tab_wej[j - 1];
                        --j;
                    }
                    Tab_wej[j] = pomocnicza;
                }
            }
        }
    }


    // podfunkcja sortowania przez kopcowanie porządkująca kopiec w taki sposób,
    // aby był kopcem maksymalnym
    void KopiecMax (int *Tab_wej, int Rozmiar, int RodzicInd, bool Odwrocenie) {
        int maxInd = RodzicInd;
        int leweDzieckoInd = RodzicInd*2 + 1;
        int praweDzieckoInd = RodzicInd*2 + 2;

        if (!Odwrocenie) {
            if(leweDzieckoInd < Rozmiar && Tab_wej[leweDzieckoInd] > Tab_wej[maxInd]) {
                maxInd = leweDzieckoInd;
            }

            if(praweDzieckoInd < Rozmiar && Tab_wej[praweDzieckoInd] > Tab_wej[maxInd]) {
                maxInd = praweDzieckoInd;
            }

            if(maxInd != RodzicInd) {
                std::swap(Tab_wej[maxInd], Tab_wej[RodzicInd]);
                KopiecMax(Tab_wej, Rozmiar, maxInd, Odwrocenie);
            }
        } else {
            if(leweDzieckoInd < Rozmiar && Tab_wej[leweDzieckoInd] < Tab_wej[maxInd]) {
                maxInd = leweDzieckoInd;
            }

            if(praweDzieckoInd < Rozmiar && Tab_wej[praweDzieckoInd] < Tab_wej[maxInd]) {
                maxInd = praweDzieckoInd;
            }

            if(maxInd != RodzicInd) {
                std::swap(Tab_wej[maxInd], Tab_wej[RodzicInd]);
                KopiecMax(Tab_wej, Rozmiar, maxInd, Odwrocenie);
            }
        }
    }


    // sortowanie przez kopcowanie wykorzystywane w głównym algorytmie
    // sortowania introspektywnego 
    void heap_sort (int *Tab_wej, int LewyInd, int PrawyInd, bool Odwrocenie) {
        int n = PrawyInd - LewyInd + 1;

        for (int i = LewyInd + (n/2) - 1; i >= LewyInd; i--) {
            KopiecMax(Tab_wej, n, i, Odwrocenie);
        }
        
        for (int i = LewyInd + n - 1; i > LewyInd; i--) {
            std::swap(Tab_wej[LewyInd], Tab_wej[i]);
            --n;
            KopiecMax(Tab_wej, n, LewyInd, Odwrocenie);
        }
    }


    // przekształcone sortowanie szybkie z wyeliminowanym wywoływaniem rekurencyjnym
    // zwracające indeks pivota 
    int q_sort_dla_i_sorta (int *Tab_wej, int LewyInd, int PrawyInd, bool Odwrocenie) {
    
        int lewy, prawy, pivot, PivotInd;
        int n = PrawyInd - LewyInd + 1;

        if(LewyInd < PrawyInd) {
            if(!Odwrocenie) {

                // indeks pivota jest losowany z zakresu od LewyInd do n + LewyInd,
                // czyli od pierwszego, do ostatniego indeksu sortowanej tablicy
                PivotInd = rand() % n + LewyInd;
                pivot = Tab_wej[PivotInd];

                // zamieniamy pivot z pierwszym elementem
                Tab_wej[PivotInd] = Tab_wej[LewyInd];
                Tab_wej[LewyInd] = pivot;

                lewy = LewyInd;
                prawy = PrawyInd;

                while(lewy < prawy) {
                    while(Tab_wej[lewy] <= pivot && lewy < PrawyInd) {
                        lewy++;
                    }
                    while(Tab_wej[prawy] > pivot && prawy > LewyInd) {
                        prawy--;
                    }
                    if(lewy < prawy) {
                        // ustawiamy wszystkie elementy mniejsze i większe od pivota
                        // po dwóch stronach - zamieniamy jeśli są po złej stronie
                        std::swap(Tab_wej[lewy], Tab_wej[prawy]);
                    }
                }
        
                // ustawienie pivota na prawidłowej pozycji
                std::swap(Tab_wej[LewyInd], Tab_wej[prawy]);

                // zwracamy indeks pivota
                return prawy;     

            } else {

                // indeks pivota jest losowany z zakresu od LewyInd do n + LewyInd,
                // czyli od pierwszego, do ostatniego indeksu sortowanej tablicy
                PivotInd = rand() % n + LewyInd;
                pivot = Tab_wej[PivotInd];

                // zamieniamy pivot z ostatnim elementem
                Tab_wej[PivotInd] = Tab_wej[PrawyInd];
                Tab_wej[PrawyInd] = pivot;

                lewy = LewyInd;
                prawy = PrawyInd;

                while(lewy < prawy) {
                    while(Tab_wej[lewy] > pivot && lewy < PrawyInd) {
                        lewy++;
                    }
                    while(Tab_wej[prawy] <= pivot && prawy > LewyInd) {
                        prawy--;
                    }
                    if(lewy < prawy) {
                        // ustawiamy wszystkie elementy mniejsze i większe od pivota
                        // po dwóch stronach - zamieniamy jeśli są po złej stronie
                        std::swap(Tab_wej[lewy], Tab_wej[prawy]);
                    }
                }
        
                // ustawienie pivota na prawidłowej pozycji
                std::swap(Tab_wej[PrawyInd], Tab_wej[lewy]);

                // zwracamy indeks pivota
                return lewy;     
            }

        } else {   
            // zwracamy indeks pojedynczego elementu, bo nie dokonane zostały
            // żadne podziały i nie został wylosowany pivot
            return LewyInd;
        }
        
    }


    // trzon algorytmu sortowania introspektywnego
    void i_sort (int *Tab_wej, int LewyInd, int PrawyInd, int Glebokosc, bool Odwrocenie) {
        int PivotInd;
        if (Glebokosc <= 0) {
            heap_sort(Tab_wej, LewyInd, PrawyInd, Odwrocenie);
            return;
        }

        PivotInd = q_sort_dla_i_sorta(Tab_wej, LewyInd, PrawyInd, Odwrocenie);

        if (PivotInd > (LewyInd + 9)) {
            i_sort(Tab_wej, LewyInd, PivotInd - 1, Glebokosc - 1, Odwrocenie);
        }

        if ((PrawyInd - PivotInd) > 9) {
            i_sort(Tab_wej, PivotInd + 1, PrawyInd, Glebokosc - 1, Odwrocenie);
        }
    }


    // główna funkcja organizująca dla sortowania introspektywnego
    void intro_sort (int Tab_wej[Rozmiar_tab], bool Odwrocenie) {
        int Glebokosc = (2*log(Rozmiar_tab))/(log(2));
        i_sort(Tab_wej, 0, Rozmiar_tab - 1, Glebokosc, Odwrocenie);
        insert_sort(Tab_wej, 0, Rozmiar_tab - 1, Odwrocenie);
    }


};