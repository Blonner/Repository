#pragma once
#ifndef LISTA_DWUKIERUNKOWA_H
#define LISTA_DWUKIERUNKOWA_H

class ListaDwukierunkowa {
private:
    // Węzeł listy dwukierunkowej
    struct Wezel {
        int wartosc;
        Wezel* nastepny;
        Wezel* poprzedni;

        // Konstruktor węzła
        Wezel(int war, Wezel* nast = nullptr, Wezel* poprz = nullptr);
    };

    Wezel* head;     // Wskaźnik na początek listy
    Wezel* tail;     // Wskaźnik na koniec listy
    int rozmiar;     // Aktualny rozmiar listy

public:
    // Konstruktor
    ListaDwukierunkowa();

    // Destruktor
    ~ListaDwukierunkowa();

    // Metoda do klonowania listy - efektywne kopiowanie
    ListaDwukierunkowa* clone() const;

    // Dodawanie elementu na koniec listy
    void dodaj(int element);

    // Dodawanie elementu na określonej pozycji
    void dodajNaPozycji(int element, int indeks);

    // Dodawanie elementu na początku listy
    void dodajNaPoczatku(int element);

    // Pobieranie wartości z określonej pozycji
    int get(int indeks) const;

    // Usuwanie elementu na poczatku
    void usunPoczatek();

    // Usuwanie elementu z określonej pozycji
    void usun(int indeks);

    // Usuwanie elementu z konca
    void usunKoniec();

    // Pobieranie rozmiaru listy
    int getRozmiar() const;

    // Wyświetlanie wszystkich elementów od początku do końca
    void wyswietl();

    // Szukanie elementu
    void szukaj(int liczba);
};

#endif // LISTA_DWUKIERUNKOWA_H
