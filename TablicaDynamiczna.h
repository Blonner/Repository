#ifndef TABLICA_DYNAMICZNA_H
#define TABLICA_DYNAMICZNA_H

class TablicaDynamiczna {
private:
    int* tablica;
    int rozmiar;
    int pojemnosc;

    // Metoda pomocnicza do zmiany rozmiaru tablicy
    void zmienRozmiarTablicy(int nowaPojemnosc);

public:
    // Konstruktor i destruktor
    TablicaDynamiczna();
    ~TablicaDynamiczna();

    // Metody dostępowe
    int getRozmiar() const;
    int get(int indeks) const;

    // Podstawowe operacje
    void dodaj(int wartosc);
    void dodajNaPoczatku(int wartosc);
    void dodajNaPozycji(int wartosc, int indeks);
    void usun(int indeks);
    void usunPoczatek();
    void usunKoniec();
    void szukaj(int liczba);
    void wyswietl();
};

#endif // TABLICA_DYNAMICZNA_H