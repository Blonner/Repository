#include "ListaJednokierunkowa.h"
#include <iostream>

using namespace std;

// Implementacja konstruktora węzła
ListaJednokierunkowa::Wezel::Wezel(int war, Wezel* nast) {
    wartosc = war;
    nastepny = nast;
}

// Konstruktor
ListaJednokierunkowa::ListaJednokierunkowa() {
    head = nullptr;
    tail = nullptr;
    rozmiar = 0;
}

// Destruktor
ListaJednokierunkowa::~ListaJednokierunkowa() {
    // Usuwanie wszystkich węzłów
    Wezel* aktualny = head;
    while (aktualny != nullptr) {
        Wezel* temp = aktualny;
        aktualny = aktualny->nastepny;
        delete temp;
    }
}

// Klonowanie listy
ListaJednokierunkowa* ListaJednokierunkowa::clone() const {
    ListaJednokierunkowa* nowaLista = new ListaJednokierunkowa();

    if (head == nullptr) {
        return nowaLista; // Lista jest pusta, zwracamy pustą listę
    }

    // Tworzymy pierwszy węzeł
    nowaLista->head = new Wezel(head->wartosc);
    nowaLista->tail = nowaLista->head;
    nowaLista->rozmiar = 1;

    // Kopiujemy resztę węzłów
    Wezel* aktualny = head->nastepny;
    while (aktualny != nullptr) {
        nowaLista->tail->nastepny = new Wezel(aktualny->wartosc);
        nowaLista->tail = nowaLista->tail->nastepny;
        nowaLista->rozmiar++;
        aktualny = aktualny->nastepny;
    }

    return nowaLista;
}

// Dodawanie elementu na koniec listy
void ListaJednokierunkowa::dodaj(int element) {
    Wezel* nowyWezel = new Wezel(element);

    // Jeśli lista jest pusta
    if (head == nullptr) {
        head = nowyWezel;
        tail = nowyWezel;
    }
    else {
        // Dodawanie na koniec
        tail->nastepny = nowyWezel;
        tail = nowyWezel;
    }

    rozmiar++;
}

// Dodawanie elementu na określonej pozycji
void ListaJednokierunkowa::dodajNaPozycji(int element, int indeks) {
    // Sprawdzanie czy indeks jest prawidłowy
    if (indeks < 0 || indeks > rozmiar) {
        cout << "Nieprawidlowy indeks!" << endl;
        return;
    }

    // Dodawanie na początek
    if (indeks == 0) {
        dodajNaPoczatku(element);
        return;
    }

    // Dodawanie na koniec
    if (indeks == rozmiar) {
        dodaj(element);
        return;
    }

    // Dodawanie w środku
    Wezel* aktualny = head;
    for (int i = 0; i < indeks - 1; i++) {
        aktualny = aktualny->nastepny;
    }

    Wezel* nowyWezel = new Wezel(element, aktualny->nastepny);
    aktualny->nastepny = nowyWezel;
    rozmiar++;
}

// Dodawanie elementu na początku listy
void ListaJednokierunkowa::dodajNaPoczatku(int element) {
    Wezel* nowyWezel = new Wezel(element, head);
    head = nowyWezel;

    // Jeśli to pierwszy element, ustawiamy tail
    if (tail == nullptr) {
        tail = nowyWezel;
    }

    rozmiar++;
}

// Pobieranie wartości z określonej pozycji
int ListaJednokierunkowa::get(int indeks) const {
    if (indeks < 0 || indeks >= rozmiar) {
        cout << "Indeks poza zakresem!" << endl;
        return -1;
    }

    Wezel* aktualny = head;
    for (int i = 0; i < indeks; i++) {
        aktualny = aktualny->nastepny;
    }

    return aktualny->wartosc;
}

// Usuwanie elementu na poczatku
void ListaJednokierunkowa::usunPoczatek() {
    if (head != nullptr) {
        Wezel* temp = head;
        head = head->nastepny;
        delete temp;

        // Jeśli usunieto ostatni element
        if (head == nullptr) {
            tail = nullptr;
        }

        rozmiar--;
    }
}

// Usuwanie elementu z określonej pozycji
void ListaJednokierunkowa::usun(int indeks) {
    if (indeks < 0 || indeks >= rozmiar) {
        cout << "Indeks poza zakresem!" << endl;
        return;
    }

    // Usuwanie pierwszego elementu
    if (indeks == 0) {
        Wezel* temp = head;
        head = head->nastepny;
        delete temp;

        // Jeśli to był ostatni element, ustawiamy tail na nullptr
        if (head == nullptr) {
            tail = nullptr;
        }
    }
    else {
        // Znajdowanie węzła przed usuwanym
        Wezel* aktualny = head;
        for (int i = 0; i < indeks - 1; i++) {
            aktualny = aktualny->nastepny;
        }

        Wezel* temp = aktualny->nastepny;
        aktualny->nastepny = temp->nastepny;

        // Jeśli usuwamy ostatni element, odnawiamy tail
        if (temp == tail) {
            tail = aktualny;
        }

        delete temp;
    }

    rozmiar--;
}

// Usuwanie elementu z końca
void ListaJednokierunkowa::usunKoniec() {
    if (head == nullptr) return;

    if (head->nastepny == nullptr) {
        delete head;
        head = nullptr;
        tail = nullptr;
        rozmiar--;
    }
    else {
        Wezel* temp = head;
        while (temp->nastepny->nastepny != nullptr) {
            temp = temp->nastepny;
        }
        delete temp->nastepny;
        temp->nastepny = nullptr;
        tail = temp;
        rozmiar--;
    }
}

// Sprawdzanie rozmiaru listy
int ListaJednokierunkowa::getRozmiar() const {
    return rozmiar;
}

// Wyświetlanie wszystkich elementów
void ListaJednokierunkowa::wyswietl() {
    cout << "ListaJednokierunkowa: [";
    Wezel* aktualny = head;
    while (aktualny != nullptr) {
        cout << aktualny->wartosc;

        if (aktualny->nastepny != nullptr) {
            cout << ", ";
        }

        aktualny = aktualny->nastepny;
    }
    cout << "]" << endl;
}

// Szukanie elementu
void ListaJednokierunkowa::szukaj(int liczba) {
    bool znaleziona = false;
    int pozycja = 0;
    Wezel* aktualny = head;

//    cout << "Liczba " << liczba << " znajduje sie na pozycjach: ";

    while (aktualny != nullptr) {
        if (aktualny->wartosc == liczba) {
//            cout << pozycja << " ";
            znaleziona = true;
        }

        aktualny = aktualny->nastepny;
        pozycja++;
    }

    if (!znaleziona) {
        cout << "Tej liczby nie ma w liscie.";
    }

//    cout << endl;
}
