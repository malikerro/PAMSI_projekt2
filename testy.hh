#include "algorytmy.hh"
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <conio.h>

// stałe definiujące wszystkie warianty rozmiarów tablic
// do przeprowadzenia testów
#define ROZMIAR_1 10000
#define ROZMIAR_2 50000
#define ROZMIAR_3 100000
#define ROZMIAR_4 500000
#define ROZMIAR_5 1000000
#define IL_ROZM 5
#define ROZMIAR_GRANICZNY 2000000 
// ROZMIAR_GRANICZNY był używany do rozdzielenia metod sortowania
// między mniejszymi a większymi rozmiarami tablic, jednak ostatecznie
// wszystkie tablice sortowane są w ten sam sposób

// stałe definiujące warianty wstępnego posortowania tablic
#define PROCENT_25 0.25
#define PROCENT_50 0.50
#define PROCENT_75 0.75
#define PROCENT_95 0.95
#define PROCENT_99 0.99
#define PROCENT_997 0.997
#define IL_WAR 6
#define IL_WAR_ALL 8

// stałe wykorzystywane do tworzenia dynamicznych tablic trój-wymiarowych
// o zadanych wymiarach
#define ROZM_X 8
#define ROZM_Y 3
#define ROZM_Z 100


template <int Rozmiar_tab>
class Testy {

    const double Tab_Warianty[IL_WAR] = {PROCENT_25, PROCENT_50, PROCENT_75, PROCENT_95, PROCENT_99, PROCENT_997};
    std::string Tab_Opisy[ROZM_X] = {"nieposortowanej ", "posortowanej w 25% ", "posortowanej w 50% ", "posortowanej w 75% ", "posortowanej w 95% ", "posortowanej w 99% ", "posortowanej w 997% ", "posortowanej w odwrotnej kolejnosci "};
    std::string Tab_Nazwy_sortowan[ROZM_Y] = {"merge sort", "quick sort", "intro sort"};
    int ***Tab_testowa;
    Algorytm<Rozmiar_tab> Algorytm_1;

    public:

    
    // konstruktor klasy Testy
    Testy () {
        // Jeśli rozmiar n będzie mniejszy niż 500 000, alokujemy pamięć na tablicę o wymiarach [8][100][n]
        if(Rozmiar_tab < ROZMIAR_GRANICZNY) {

            Tab_testowa = new int**[ROZM_X];

            for(int x = 0; x < ROZM_X; x++) {
                Tab_testowa[x] = new int *[ROZM_Z];
                for(int z = 0; z < ROZM_Z; z++) {
                    Tab_testowa[x][z] = new int[Rozmiar_tab];
                }
            }
        } else if(Rozmiar_tab >= ROZMIAR_GRANICZNY) {
        // Dla rozmiaru 500 000 i 1 000 000, alokujemy pamięć na tablicę o wymiarach [8][3][n], 
        // gdzie [n] to właściwy sortowany wymiar tablicy
            Tab_testowa = new int**[ROZM_X];

            for(int x = 0; x < ROZM_X; x++) {
                Tab_testowa[x] = new int *[ROZM_Y];
                for(int y = 0; y < ROZM_Y; y++) {
                    Tab_testowa[x][y] = new int[Rozmiar_tab];
                }
            }
        }
        // informacja o wykonaniu się poleceń kontruktora
        std::cout << "Stworzony rozm: " << Rozmiar_tab << "\n";
    }


    // destruktor klasy Testy
    ~Testy () {
        if(Rozmiar_tab < ROZMIAR_GRANICZNY) {
            // pętla zwalniająca zaalokowaną pamięć dla tablicy testowej
            for(int x = 0; x < ROZM_X; x++) {
                for(int z = 0; z < ROZM_Z; z++) {
                    delete [] Tab_testowa[x][z];
                }
                delete [] Tab_testowa[x];
            }
            delete [] Tab_testowa;
            Tab_testowa = NULL;

        } else if(Rozmiar_tab >= ROZMIAR_GRANICZNY) {
            // pętla zwalniająca zaalokowaną pamięć dla tablicy testowej
            for(int x = 0; x < ROZM_X; x++) {
                for(int y = 0; y < ROZM_Y; y++) {
                    delete [] Tab_testowa[x][y];
                }
                delete [] Tab_testowa[x];
            }
            delete [] Tab_testowa;
            Tab_testowa = NULL;
        }
        // informacja o wykonaniu się poleceń destruktora
        std::cout << "Usuniety rozm: " << Rozmiar_tab << "\n";
    }


    void Inicjuj_tab_losowe () {

        //wariant dla mniejszych tablic, n < ROZMIAR_GRANICZNY
        if(Rozmiar_tab < ROZMIAR_GRANICZNY) {

            for(int i = 0; i < ROZM_Z; i++) {
                for (int j = 0; j < Rozmiar_tab; j++) {   
                //int wylosowana_liczba =( std::rand() % ile_liczb_w_przedziale ) + startowa_liczba;
                // czyli losujemy liczbę całkowitą z zakresu: -50 000 do 50 000
                Tab_testowa[0][i][j] = (rand() * rand() + rand()) % 100001  - 50000;
                }
            }

            for (int i = 0; i < IL_WAR; i++) {
                int Uporzadkowane = (int) std::floor(Rozmiar_tab*Tab_Warianty[i]);

                for(int j = 0; j < ROZM_Z; j++) {

                    for (int k = 0; k < Uporzadkowane ; k++) {
                        Tab_testowa[i + 1][j][k] = k;
                    }
                 
                    for (int l = Uporzadkowane; l < Rozmiar_tab ; l++) {
                        Tab_testowa[i + 1][j][l] = Uporzadkowane + (rand() * rand() + rand()) % 100001;
                    }
                }
            }

            for(int i = 0; i < ROZM_Z; i++) {
                
                for(int j = 0; j < Rozmiar_tab; j++) {
                    // kopiujemy zawartość tablicy z losowymi wartościami
                    Tab_testowa[7][i][j] = Tab_testowa[0][i][j];
                }

                Algorytm_1.quick_sort(Tab_testowa[7][i], 1);
            }


        //wariant dla większych tablic, n >= ROZMIAR_GRANICZNY
        } else if(Rozmiar_tab >= ROZMIAR_GRANICZNY) {

            for(int n = 0; n < Rozmiar_tab; n++) {
                //int wylosowana_liczba =( std::rand() % ile_liczb_w_przedziale ) + startowa_liczba;
                // czyli losujemy liczbę całkowitą z zakresu: -50 000 do 50 000
                Tab_testowa[0][0][n] = (rand() * rand() + rand()) % 100001  - 50000;
                Tab_testowa[0][1][n] = Tab_testowa[0][0][n];
                Tab_testowa[0][2][n] = Tab_testowa[0][0][n];
            }

            for (int i = 0; i < IL_WAR; i++) {
                int Uporzadkowane = (int) std::floor(Rozmiar_tab*Tab_Warianty[i]);
                for (int k = 0; k < Uporzadkowane ; k++) {
                    Tab_testowa[i + 1][0][k] = k;
                }
                 
                for (int l = Uporzadkowane; l < Rozmiar_tab ; l++) {
                    Tab_testowa[i + 1][0][l] = Uporzadkowane + (rand() * rand() + rand()) % 100001;
                }

                for (int m = 0; m < Rozmiar_tab; m++) {
                    Tab_testowa[i + 1][1][m] = Tab_testowa[i + 1][0][m];
                    Tab_testowa[i + 1][2][m] = Tab_testowa[i + 1][0][m];
                }
            }

            for(int p = 0; p < Rozmiar_tab; p++) {
                // kopiujemy zawartość tablicy z losowymi wartościami
                Tab_testowa[7][0][p] = Tab_testowa[0][0][p];
            }

            // przygotowujemy tablice posortowane w odwrotnej kolejności
            Algorytm_1.merge_sort(Tab_testowa[7][0], 1);

            for(int s = 0; s < Rozmiar_tab; s++) {
                // kopiujemy odwrotnie sortowaną tablicę 2 razy
                Tab_testowa[7][1][s] = Tab_testowa[7][0][s];
                Tab_testowa[7][2][s] = Tab_testowa[7][0][s];
            }
        }
    }


    void Wyswietl_zawartosc_tablic () {

        //wariant dla mniejszych tablic, n < ROZMIAR_GRANICZNY
        if(Rozmiar_tab < ROZMIAR_GRANICZNY) {

            int dodatnie1 = 0;
            int ujemne1 = 0;
    
            std::cout << "\n\n";
    
            for (int j = 0; j < ROZM_X; j++) {
                for (int k = 0; k < ROZM_Z; k++) {
                    dodatnie1 = 0;
                    ujemne1 = 0;
                    std::cout << "\nTab_testowa[" << j << "][" << k << "][n]: \n";
                    for (int i = 0; i < Rozmiar_tab; i++) {
                        std::cout << Tab_testowa[j][k][i] << " ";
                        if(Tab_testowa[j][k][i] >= 0) {
                            dodatnie1++;
                        } else {
                            ujemne1++;
                        }
                    }
                    std::cout << "\ndodatnie: " << dodatnie1 << std::endl;
                    std::cout << "ujemne: " << ujemne1 << std::endl << std::endl;
                }
                std::cout << std::endl << std::endl;
            }
        
        //wariant dla większych tablic, n >= ROZMIAR_GRANICZNY
        } else if(Rozmiar_tab >= ROZMIAR_GRANICZNY) {

            int dodatnie = 0;
            int ujemne = 0;
    
            std::cout << "\n\nTab_testowa[0][0][n]: \n";
            for (int i = 0; i < Rozmiar_tab; i++) {
                if(Tab_testowa[0][0][i] >= 0) {
                    dodatnie++;
                } else {
                    ujemne++;
                }
                std::cout << Tab_testowa[0][0][i] << " ";
            }

            std::cout << "\ndodatnie: " << dodatnie << std::endl;
            std::cout << "ujemne: " << ujemne << std::endl << std::endl;
    
            for (int j = 0; j < ROZM_X; j++) {
                for (int k = 0; k < ROZM_Y; k++) {
                    std::cout << "\nTab_testowa[" << j << "][" << k << "][n]: \n";
                    for (int i = 0; i < Rozmiar_tab; i++) {
                        std::cout << Tab_testowa[j][k][i] << " ";
                    }
                }
                std::cout << std::endl << std::endl;
            }
        }

    }


    // Parametr Sortowanie jest wykorzystywany tylko w przypadku mniejszych tablic,
    // dla których nie dysponujemy kopiami do różnych algorytmów sortowań
    void Petla_testujaca (std::fstream &plik, std::fstream &plik2, int Sortowanie) {

        //wariant dla mniejszych tablic, n < ROZMIAR_GRANICZNY
        if(Rozmiar_tab < ROZMIAR_GRANICZNY) {

            for(int i = 0; i < IL_WAR_ALL; i++) {

                auto poczatek0 = std::chrono::high_resolution_clock::now();
                // sortowanie stu tablic
                for(int j = 0; j < ROZM_Z; j++) {
                    if(Sortowanie == 1) { Algorytm_1.merge_sort(Tab_testowa[i][j], 0);
                    } else if(Sortowanie == 2) { Algorytm_1.quick_sort(Tab_testowa[i][j], 0);
                    } else if(Sortowanie == 3) { Algorytm_1.intro_sort(Tab_testowa[i][j], 0);
                    }
                }

                auto koniec0 = std::chrono::high_resolution_clock::now();
                // obliczenie czasu trwania operacji w [s]
                std::chrono::duration<long double> dlugosc0 = koniec0 - poczatek0;
                // zapis do pliku
                plik << "Dla tablicy " << Tab_Opisy[i] << ":\n";
                plik << Tab_Nazwy_sortowan[Sortowanie - 1] << ": " << dlugosc0.count() << " sekund\n";
                
                // wyświetlenie informacji na standardowym wyjściu
                // dzięki temu mamy dokładniejsze informacje o postępie testów
                std::cout << "Dla tablicy " << Tab_Opisy[i] << ":\n";
                std::cout << Tab_Nazwy_sortowan[Sortowanie - 1] << ": " << dlugosc0.count() << " sekund\n";
            }
            plik << "\n\n";
            std::cout << "\n\n";

        //wariant dla większych tablic, n >= ROZMIAR_GRANICZNY
        // prawdopodobnie nie działa - wszystkie wyniki są równe 0 s.
        // stąd też rezygnacja z zastosowania ROZMIARU_GRANICZNEGO
        } else if(Rozmiar_tab >= ROZMIAR_GRANICZNY) {
        
            int Il_powtorzen = ROZM_Z;
            int Suma_winikow[IL_WAR_ALL][ROZM_Y];

            for (int i = 0; i < IL_WAR_ALL; i++) {
                for (int j = 0; j < ROZM_Y; j++) {
                    Suma_winikow[i][j] = 0;
                }
            }

            for (int i = 0; i < Il_powtorzen; i++) {
                for (int j = 0; j < IL_WAR_ALL; j++) {

                    // Zainicjowanie tablic do sortowania
                    Inicjuj_tab_losowe();
                    
                    // zapis czasu pocz.
                    // sortowanie
                    // zapis czasu końc.
                    // dodanie czasu do wyniku zbiorowego

                    auto poczatek0 = std::chrono::high_resolution_clock::now();
                    Algorytm_1.merge_sort(Tab_testowa[j][0], 0);
                    auto koniec0 = std::chrono::high_resolution_clock::now();

                    // obliczenie czasu trwania operacji w [s]
                    std::chrono::duration<long double> dlugosc0 = koniec0 - poczatek0;
                    Suma_winikow[j][0] += dlugosc0.count();

                    auto poczatek1 = std::chrono::high_resolution_clock::now();
                    Algorytm_1.quick_sort(Tab_testowa[j][1], 0);
                    auto koniec1 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<long double> dlugosc1 = koniec1 - poczatek1;
                    Suma_winikow[j][1] += dlugosc1.count();

                    auto poczatek2 = std::chrono::high_resolution_clock::now();
                    Algorytm_1.intro_sort(Tab_testowa[j][2], 0);
                    auto koniec2 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<long double> dlugosc2 = koniec2 - poczatek2;
                    Suma_winikow[j][2] += dlugosc2.count();
                }
            }
            // zapis wyników do plików
            plik << "\n\n\nWyniki czasu sortowania tablic o rozmiarze " << Rozmiar_tab << " elementow\n\n";
            plik << "Dla tablicy nieposortowanej: \n";
            plik << "merge sort: " << Suma_winikow[0][0] << " sekund\n";
            plik << "quick sort: " << Suma_winikow[0][1] << " sekund\n";
            plik << "intro sort: " << Suma_winikow[0][2] << " sekund\n\n";
            for (int i = 0; i < IL_WAR; i++) {    
                plik << "Dla tablicy posortowanej w " << Tab_Warianty[i]*100 << "%: \n";
                plik << "merge sort: " << Suma_winikow[i + 1][0] << " sekund\n";
                plik << "quick sort: " << Suma_winikow[i + 1][1] << " sekund\n";
                plik << "intro sort: " << Suma_winikow[i + 1][2] << " sekund\n\n";   
            }
            plik << "Dla tablicy posortowanej w odwrotnej kolejnosci: \n";
            plik << "merge sort: " << Suma_winikow[7][0] << " sekund\n";
            plik << "quick sort: " << Suma_winikow[7][1] << " sekund\n";
            plik << "intro sort: " << Suma_winikow[7][2] << " sekund\n\n";

            plik2 << "\n\n\nWyniki czasu sortowania tablic o rozmiarze " << Rozmiar_tab << " elementow\n\n";
            plik2 << "Dla tablicy nieposortowanej: \n";
            plik2 << Suma_winikow[0][0] << "\n" << Suma_winikow[0][1] << "\n" << Suma_winikow[0][2] << "\n";
            for (int i = 0; i < IL_WAR; i++) {    
                plik2 << "Dla tablicy posortowanej w " << Tab_Warianty[i]*100 << "%: \n";
                plik2 << Suma_winikow[i+1][0] << "\n" << Suma_winikow[i+1][1] << "\n" << Suma_winikow[i+1][2] << "\n\n";
            }
            plik2 << "Dla tablicy posortowanej w odwrotnej kolejnosci: \n";
            plik2 << Suma_winikow[7][0] << "\n" << Suma_winikow[7][1] << "\n" << Suma_winikow[7][2] << "\n";
        }
    }



    //liczba& operator=(const liczba& r) {re = r.re; im = r.im; return *this;}
    Testy<Rozmiar_tab>& operator = (const Testy<Rozmiar_tab>& Test_prawy) {
        if(Rozmiar_tab < ROZMIAR_GRANICZNY) {
            for(int i = 0; i < ROZM_X; i++) {
                for(int j = 0; j < ROZM_Z; j++) {
                    for(int k = 0; k < Rozmiar_tab; k++) {
                        Tab_testowa[i][j][k] = Test_prawy.Tab_testowa[i][j][k];
                    }
                }
            }
        } else if(Rozmiar_tab >= ROZMIAR_GRANICZNY){
            for(int i = 0; i < ROZM_X; i++) {
                for(int j = 0; j < ROZM_Y; j++) {
                    for(int k = 0; k < Rozmiar_tab; k++) {
                        Tab_testowa[i][j][k] = Test_prawy.Tab_testowa[i][j][k];
                    }
                }
            }
        }
        return *this;
    }


    void Przeprowadz_testy (std::fstream &plik_ref, std::fstream &plik_ref2, Testy<Rozmiar_tab> *Test_11, Testy<Rozmiar_tab> *Test_12) {
        
        this->Inicjuj_tab_losowe();
        *Test_11 = *this;
        *Test_12 = *this;

        plik_ref << "\nWyniki czasu sortowania tablic o rozmiarze " << Rozmiar_tab << " elementow\n\n";
        std::cout << "\nWyniki czasu sortowania tablic o rozmiarze " << Rozmiar_tab << " elementow\n\n";
        
        this->Petla_testujaca(plik_ref, plik_ref2, 1);
        Test_11->Petla_testujaca(plik_ref, plik_ref2, 2);
        Test_12->Petla_testujaca(plik_ref, plik_ref2, 3);

        delete Test_11;
        delete Test_12;
        delete this;
    }

};