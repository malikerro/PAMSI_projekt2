#include "testy.hh"
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <conio.h>


using namespace std;


int main ()
{
    
    srand(time(NULL));

    remove("Wyniki.txt");
    remove("Excel.txt");

    fstream plik, plik2;
    plik.open("Wyniki.txt", ios::out); // plik do zapisu czytelnych wyników testów
    plik2.open("Excel.txt", ios::out); // plik do zapisu wyników testów w formacie przygotowanym do Excela
    fstream &plik_ref = plik;
    fstream &plik_ref2 = plik2;
    
    if(plik.good() == false || plik2.good() == false) {
    cout << "Nie uzyskano dostepu do plikow!" << std::endl;
    return 1;
    }

    cout << "Nacisnij dowolny przycisk, aby kontynuowac\n";
    char Znak;
    cin >> Znak;


    {   // testy dla tablic w rozmiarze 10 000
    Testy<ROZMIAR_1> *Test_1 = new Testy<ROZMIAR_1>;
    Testy<ROZMIAR_1> *Test_11 = new Testy<ROZMIAR_1>;
    Testy<ROZMIAR_1> *Test_12 = new Testy<ROZMIAR_1>;
    Test_1->Przeprowadz_testy (plik_ref, plik_ref2, Test_11, Test_12);
    }

    {   // testy dla tablic w rozmiarze 50 000
    Testy<ROZMIAR_2> *Test_2 = new Testy<ROZMIAR_2>;
    Testy<ROZMIAR_2> *Test_21 = new Testy<ROZMIAR_2>;
    Testy<ROZMIAR_2> *Test_22 = new Testy<ROZMIAR_2>;
    Test_2->Przeprowadz_testy (plik_ref, plik_ref2, Test_21, Test_22);
    }

    {   // testy dla tablic w rozmiarze 100 000
    Testy<ROZMIAR_3> *Test_3 = new Testy<ROZMIAR_3>;
    Testy<ROZMIAR_3> *Test_31 = new Testy<ROZMIAR_3>;
    Testy<ROZMIAR_3> *Test_32 = new Testy<ROZMIAR_3>;
    Test_3->Przeprowadz_testy (plik_ref, plik_ref2, Test_31, Test_32);
    }
    
    {   // testy dla tablic w rozmiarze 500 000
    Testy<ROZMIAR_4> *Test_4 = new Testy<ROZMIAR_4>;
    Testy<ROZMIAR_4> *Test_41 = new Testy<ROZMIAR_4>;
    Testy<ROZMIAR_4> *Test_42 = new Testy<ROZMIAR_4>;
    Test_4->Przeprowadz_testy (plik_ref, plik_ref2, Test_41, Test_42);
    }
    
    {   // testy dla tablic w rozmiarze 1 000 000
    Testy<ROZMIAR_5> *Test_5 = new Testy<ROZMIAR_5>;
    Testy<ROZMIAR_5> *Test_51 = new Testy<ROZMIAR_5>;
    Testy<ROZMIAR_5> *Test_52 = new Testy<ROZMIAR_5>;
    Test_5->Przeprowadz_testy (plik_ref, plik_ref2, Test_51, Test_52);
    }


    plik.close();
    plik2.close();


    return 0;
}

