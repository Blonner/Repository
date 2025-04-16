#include "ListaDwukierunkowa.h"
#include <iostream>

using namespace std;

// Implementacja konstruktora węzła
ListaDwukierunkowa::Wezel::Wezel(int war, Wezel* nast, Wezel* poprz) {
    wartosc = war;
    nastepny = nast;
    poprzedni = poprz;
}

// Konstruktor
ListaDwukierunkowa::ListaDwukierunkowa() {
    head = nullptr;
    tail = nullptr;
    rozmiar = 0;
}

// Destruktor
ListaDwukierunkowa::~ListaDwukierunkowa() {
    // Usuwanie wszystkich węzłów
    Wezel* aktualny = head;
    while (aktualny != nullptr) {
        Wezel* temp = aktualny;
        aktualny = aktualny->nastepny;
        delete temp;
    }
}

// Metoda do klonowania listy - efektywne kopiowanie
ListaDwukierunkowa* ListaDwukierunkowa::clone() const {
    ListaDwukierunkowa* nowaLista = new ListaDwukierunkowa();

    if (head == nullptr) {
        return nowaLista; // Lista jest pusta, zwracamy pustą listę
    }

    // Tworzymy pierwszy węzeł
    nowaLista->head = new Wezel(head->wartosc);
    nowaLista->tail = nowaLista->head;
    nowaLista->rozmiar = 1;

    // Kopiujemy resztę węzłów
    Wezel* aktualny = head->nastepny;
    Wezel* poprzedni = nowaLista->head;

    while (aktualny != nullptr) {
        Wezel* nowyWezel = new Wezel(aktualny->wartosc, nullptr, poprzedni);
        poprzedni->nastepny = nowyWezel;
        poprzedni = nowyWezel;
        nowaLista->tail = nowyWezel;
        nowaLista->rozmiar++;
        aktualny = aktualny->nastepny;
    }

    return nowaLista;
}

// Dodawanie elementu na koniec listy
void ListaDwukierunkowa::dodaj(int element) {
    Wezel* nowyWezel = new Wezel(element);

    // Jeśli lista jest pusta
    if (head == nullptr) {
        head = nowyWezel;
        tail = nowyWezel;
    }
    else {
        // Dodawanie na koniec
        nowyWezel->poprzedni = tail;
        tail->nastepny = nowyWezel;
        tail = nowyWezel;
    }

    rozmiar++;
}

// Dodawanie elementu na określonej pozycji
void ListaDwukierunkowa::dodajNaPozycji(int element, int indeks) {
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

    // Określenie, z której strony listy zacząć przeszukiwanie
    Wezel* aktualny;
    if (indeks <= rozmiar / 2) {
        // Od początku
        aktualny = head;
        for (int i = 0; i < indeks; i++) {
            aktualny = aktualny->nastepny;
        }
    }
    else {
        // Od końca
        aktualny = tail;
        for (int i = rozmiar - 1; i > indeks; i--) {
            aktualny = aktualny->poprzedni;
        }
    }

    // Wstawianie przed aktualnym węzłem
    Wezel* nowyWezel = new Wezel(element, aktualny, aktualny->poprzedni);
    aktualny->poprzedni->nastepny = nowyWezel;
    aktualny->poprzedni = nowyWezel;

    rozmiar++;
}

// Dodawanie elementu na początku listy
void ListaDwukierunkowa::dodajNaPoczatku(int element) {
    Wezel* nowyWezel = new Wezel(element, head);

    if (head != nullptr) {
        head->poprzedni = nowyWezel;
    }

    head = nowyWezel;

    // Jeśli to pierwszy element, ustawiamy tail
    if (tail == nullptr) {
        tail = nowyWezel;
    }

    rozmiar++;
}

// Pobieranie wartości z określonej pozycji
int ListaDwukierunkowa::get(int indeks) const {
    if (indeks < 0 || indeks >= rozmiar) {
        cout << "Indeks poza zakresem!" << endl;
        return -1;
    }

    Wezel* aktualny;
    // Z ktorej strony patrzymy
    if (indeks <= rozmiar / 2) {
        // Od początku
        aktualny = head;
        for (int i = 0; i < indeks; i++) {
            aktualny = aktualny->nastepny;
        }
    }
    else {
        // Od końca
        aktualny = tail;
        for (int i = rozmiar - 1; i > indeks; i--) {
            aktualny = aktualny->poprzedni;
        }
    }

    return aktualny->wartosc;
}

// Usuwanie elementu na poczatku
void ListaDwukierunkowa::usunPoczatek() {
    if (head != nullptr) {
        Wezel* temp = head;
        head = head->nastepny;
        if (head != nullptr) {
            head->poprzedni = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        rozmiar--;
    }
}

// Usuwanie elementu z określonej pozycji
void ListaDwukierunkowa::usun(int indeks) {
    if (indeks < 0 || indeks >= rozmiar) {
        cout << "Indeks poza zakresem!" << endl;
        return;
    }

    // Usuwanie pierwszego elementu
    if (indeks == 0) {
        Wezel* temp = head;
        head = head->nastepny;

        if (head != nullptr) {
            head->poprzedni = nullptr;
        }
        else {
            // Lista będzie pusta
            tail = nullptr;
        }

        delete temp;
    }
    // Usuwanie ostatniego elementu
    else if (indeks == rozmiar - 1) {
        Wezel* temp = tail;
        tail = tail->poprzedni;

        if (tail != nullptr) {
            tail->nastepny = nullptr;
        }
        else {
            // Lista będzie pusta
            head = nullptr;
        }

        delete temp;
    }
    // Usuwanie elementu ze środka
    else {
        Wezel* aktualny;

        // Ktoredy patrzymy
        if (indeks <= rozmiar / 2) {
            // Od początku
            aktualny = head;
            for (int i = 0; i < indeks; i++) {
                aktualny = aktualny->nastepny;
            }
        }
        else {
            // Od końca
            aktualny = tail;
            for (int i = rozmiar - 1; i > indeks; i--) {
                aktualny = aktualny->poprzedni;
            }
        }

        aktualny->poprzedni->nastepny = aktualny->nastepny;
        aktualny->nastepny->poprzedni = aktualny->poprzedni;

        delete aktualny;
    }

    rozmiar--;
}

// Usuwanie elementu z konca
void ListaDwukierunkowa::usunKoniec() {
    if (tail != nullptr) {
        Wezel* temp = tail;
        tail = tail->poprzedni;
        if (tail != nullptr) {
            tail->nastepny = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        rozmiar--;
    }
}

// Pobieranie rozmiaru listy
int ListaDwukierunkowa::getRozmiar() const {
    return rozmiar;
}

// Wyświetlanie wszystkich elementów od początku do końca
void ListaDwukierunkowa::wyswietl() {
    cout << "ListaDwukierunkowa: [";
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
void ListaDwukierunkowa::szukaj(int liczba) {
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
