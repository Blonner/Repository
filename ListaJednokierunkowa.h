#ifndef LISTA_JEDNOKIERUNKOWA_H
#define LISTA_JEDNOKIERUNKOWA_H

class ListaJednokierunkowa {
private:
    // Struktura węzła listy
    struct Wezel {
        int wartosc;
        Wezel* nastepny;

        // Konstruktor węzła
        Wezel(int war, Wezel* nast = nullptr);
    };

    Wezel* head;    // Wskaźnik na początek listy
    Wezel* tail;    // Wskaźnik na koniec listy
    int rozmiar;    // Aktualny rozmiar listy

public:
    ListaJednokierunkowa();
    ~ListaJednokierunkowa();

    // Metoda do klonowania listy - efektywne kopiowanie
    ListaJednokierunkowa* clone() const;

    void dodaj(int element);
    void dodajNaPozycji(int element, int indeks);
    void dodajNaPoczatku(int element);
    int get(int indeks) const;
    void usunPoczatek();
    void usun(int indeks);
    void usunKoniec();
    int getRozmiar() const;
    void wyswietl();
    void szukaj(int liczba);
};

#endif // LISTA_JEDNOKIERUNKOWA_H
