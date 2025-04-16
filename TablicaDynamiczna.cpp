#include "TablicaDynamiczna.h"
#include <iostream>

using namespace std;

// Konstruktor
TablicaDynamiczna::TablicaDynamiczna() {
    pojemnosc = 10;
    rozmiar = 0;
    tablica = new int[pojemnosc];
}

// Destruktor
TablicaDynamiczna::~TablicaDynamiczna() {
    delete[] tablica;
}

// Funkcja dodawania elementu na koniec
void TablicaDynamiczna::dodaj(int element) {
    // Podwajanie wielkości tablicy
    if (rozmiar == pojemnosc) {
        pojemnosc = pojemnosc * 2;
        int* nowaTablica = new int[pojemnosc];

        // Przenoszenie starych danych do nowej, większej tablicy
        for (int i = 0; i < rozmiar; i++) {
            nowaTablica[i] = tablica[i];
        }

        // Usuwanie starej tablicy, ustawianie większej jako używana
        delete[] tablica;
        tablica = nowaTablica;
    }

    // Dodawanie elementu
    tablica[rozmiar] = element;
    rozmiar++;
}

// Dodawanie elementu w danym miejscu w tablicy
void TablicaDynamiczna::dodajNaPozycji(int element, int indeks) {
    // Sprawdzanie czy indeks jest prawidłowy
    if (indeks < 0 || indeks > rozmiar) {
        //cout << "Nieprawidlowy indeks!" << endl;
        return;
    }

    // Podwajanie wielkości tablicy, jeśli potrzeba
    if (rozmiar == pojemnosc) {
        pojemnosc = pojemnosc * 2;
        int* nowaTablica = new int[pojemnosc];

        // Przenoszenie starych danych do nowej, większej tablicy
        for (int i = 0; i < rozmiar; i++) {
            nowaTablica[i] = tablica[i];
        }

        // Usuwanie starej tablicy, ustawianie większej jako używana
        delete[] tablica;
        tablica = nowaTablica;
    }

    // Przesuwanie elementów w prawo, aby zrobić miejsce na nowy element
    for (int i = rozmiar; i > indeks; i--) {
        tablica[i] = tablica[i - 1];
    }

    // Wstawianie nowego elementu
    tablica[indeks] = element;
    rozmiar++;
}

// Funkcja dodawania elementu na początku
void TablicaDynamiczna::dodajNaPoczatku(int element) {
    dodajNaPozycji(element, 0);
}

// Sprawdzanie wartości w tablicy z danym indeksem
int TablicaDynamiczna::get(int indeks) const {
    if (indeks >= 0 && indeks < rozmiar) {
        return tablica[indeks];
    }
    else {
        cout << "Indeks poza zakresem!" << endl;
        return -1;
    }
}

// Usuwanie elementu na poczatku
void TablicaDynamiczna::usunPoczatek() {
    if (rozmiar == 0) return;

    int* nowa = new int[rozmiar - 1];
    for (int i = 1; i < rozmiar; i++) {
        nowa[i - 1] = tablica[i];
    }

    delete[] tablica;
    tablica = nowa;
    rozmiar = rozmiar - 1;
}

// Usuwanie elementu pod wskazanym indeksem
void TablicaDynamiczna::usun(int indeks) {
    if (indeks >= 0 && indeks < rozmiar) {
        // Przesuwanie elementów w lewo
        for (int i = indeks; i < rozmiar - 1; i++) {
            tablica[i] = tablica[i + 1];
        }
        rozmiar--;
    }
    else {
        cout << "Indeks poza zakresem!" << endl;
    }
}

// Usuwanie elementu na koncu tablicy
void TablicaDynamiczna::usunKoniec() {
    if (rozmiar == 0) return;

    int* nowa = new int[rozmiar - 1];
    for (int i = 0; i < rozmiar - 1; i++) {
        nowa[i] = tablica[i];
    }

    delete[] tablica;
    tablica = nowa;
    rozmiar = rozmiar - 1;
}

// Sprawdzanie rozmiaru
int TablicaDynamiczna::getRozmiar() const {
    return rozmiar;
}

// Wyświetl wszystkie elementy
void TablicaDynamiczna::wyswietl() {
    cout << "TablicaDynamiczna: [";
    for (int i = 0; i < rozmiar; i++) {
        cout << tablica[i];
        if (i < rozmiar - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// Szukanie elementu
void TablicaDynamiczna::szukaj(int liczba) {
    bool znaleziona = false;
//    cout << "Liczba " << liczba << " znajduje sie na pozycjach: ";
    for (int i = 0; i < rozmiar; i++) {
        if (liczba == tablica[i]) {
//            cout << i << " ";
            znaleziona = true;
        }
    }
    if (znaleziona == false) {
        cout << "Tej liczby nie ma w tablicy.";
    }
//    cout << endl;
}
