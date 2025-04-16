#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <vector>
#include <memory>
#include <fstream>
#include <string>
#include <iomanip>
#include "TablicaDynamiczna.h"
#include "ListaJednokierunkowa.h"
#include "ListaDwukierunkowa.h"

using namespace std;
using namespace chrono;

// Losowy index
int getRandomIndex(int size) {
    if (size <= 1) return 0;
    return rand() % (size - 1);
}

// Zapisywanie wyników do txt
void saveResultsToFile(const string& structureName, int elementsCount, const vector<double>& results) {
    string fileName = structureName + "_wyniki.txt";
    ofstream file;

    bool fileExists = false;
    ifstream checkFile(fileName);
    if (checkFile.good()) {
        fileExists = true;
    }
    checkFile.close();

    // Otwarcie w trybie edycji
    file.open(fileName, ios::app);

    if (!file.is_open()) {
        cout << "Blad otwierania pliku: " << fileName << endl;
        return;
    }

    // Jesli plik jest nowy, to napisanie nazw kolumn
    if (!fileExists) {
        file << "Elements\tAdd_Begin\tAdd_Random\tAdd_End\tRemove_Begin\tRemove_Random\tRemove_End\tSearch" << endl;
    }

    // Zapisywanie wynikow
    file << elementsCount;
    for (const auto& result : results) {
        file << "\t" << fixed << setprecision(2) << result;
    }
    file << endl;

    file.close();
    cout << "Wyniki zapisane do: " << fileName << endl;
}

// Testy wydajnosciowe
void runPerformanceTests() {
    srand(time(0)); // Ustawienie losowości
    auto startfull = high_resolution_clock::now();

    // Predefiniowany test
    vector<int> testSizes = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000, 150000, 200000};
    int x = 500;    // Liczba powtórzen

    for (int n : testSizes) {
        cout << "\n===== Testowanie " << n << " elementow =====" << endl;

        cout << "Przygotowywanie danych..." << endl;

        // Przechowywanie danych w wektorach
        vector<int> originalData(n);
        for (int i = 0; i < n; i++) {
            originalData[i] = rand() % 1000;
        }

        // Wektor dla każdej struktury
        vector<double> dynamicArrayResults;
        vector<double> singlyLinkedListResults;
        vector<double> doublyLinkedListResults;

        // ===== DYNAMIC ARRAY TESTS =====
        cout << "\n===== DYNAMIC ARRAY TESTY =====\n";

        // Tworzenie tablicy
        auto setupDynamicArray = [&](const vector<int>& data) {
            TablicaDynamiczna* arr = new TablicaDynamiczna();
            for (int val : data) {
                arr->dodaj(val);
            }
            return arr;
            };

        
        double result = 0.0;

        // Dodanie poczatek
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            auto start = high_resolution_clock::now();
            arr->dodajNaPoczatku(1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Dodanie na poczatku: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Dodanie random
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            int randomIndex = getRandomIndex(arr->getRozmiar());
            auto start = high_resolution_clock::now();
            arr->dodajNaPozycji(1, randomIndex);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Dodanie na losowej pozycji: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Dodanie koniec
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            auto start = high_resolution_clock::now();
            arr->dodaj(1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Dodanie na koncu: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Usuniecie poczatek
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            auto start = high_resolution_clock::now();
            arr->usunPoczatek();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Usuniecie z poczatku: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Usuniecie random
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            int randomIndex = getRandomIndex(arr->getRozmiar());
            auto start = high_resolution_clock::now();
            arr->usun(randomIndex);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Usuniecie z losowej pozycji: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Usuniecie koniec
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            auto start = high_resolution_clock::now();
            arr->usunKoniec();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Usuniecie z konca: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Szukanie
        result = 0.0;
        for (int i = 0; i < x; i++) {
            TablicaDynamiczna* arr = setupDynamicArray(originalData);
            int randomValue = originalData[getRandomIndex(originalData.size())];
            auto start = high_resolution_clock::now();
            arr->szukaj(randomValue);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete arr;
        }
        result /= x;
        cout << "Szukanie: " << result << " ns" << endl;
        dynamicArrayResults.push_back(result);

        // Zapisanie wynikow
        saveResultsToFile("DynamicArray", n, dynamicArrayResults);

        // ===== SINGLY LINKED LIST TESTS =====
        cout << "\n===== SINGLY LINKED LIST TESTY =====\n";

        // Tworzenie listy
        auto setupSinglyLinkedList = [&](const vector<int>& data) {
            ListaJednokierunkowa* list = new ListaJednokierunkowa();
            for (int val : data) {
                list->dodaj(val);
            }
            return list;
            };

        // Dodanie poczatek
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->dodajNaPoczatku(1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Dodanie na poczatku: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Dodanie random
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            int randomIndex = getRandomIndex(list->getRozmiar());
            auto start = high_resolution_clock::now();
            list->dodajNaPozycji(1, randomIndex);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Dodanie na losowej pozycji: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Dodanie koniec
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->dodaj(1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Dodanie na koncu: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Usuniecie poczatek
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->usunPoczatek();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Usuniecie z poczatku: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Usuniecie random
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            int randomIndex = getRandomIndex(list->getRozmiar());
            auto start = high_resolution_clock::now();
            list->usun(randomIndex);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Usuniecie z losowej pozycji: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Usuniecie koniec
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->usunKoniec();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Usuniecie z konca: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Szukanie
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaJednokierunkowa* list = setupSinglyLinkedList(originalData);
            int randomValue = originalData[getRandomIndex(originalData.size())];
            auto start = high_resolution_clock::now();
            list->szukaj(randomValue);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Szukanie: " << result << " ns" << endl;
        singlyLinkedListResults.push_back(result);

        // Zapisanie wyników
        saveResultsToFile("SinglyLinkedList", n, singlyLinkedListResults);

        // ===== DOUBLY LINKED LIST TESTS =====
        cout << "\n===== DOUBLY LINKED LIST TESTY =====\n";

        // Tworzenie listy
        auto setupDoublyLinkedList = [&](const vector<int>& data) {
            ListaDwukierunkowa* list = new ListaDwukierunkowa();
            for (int val : data) {
                list->dodaj(val);
            }
            return list;
            };

        // Dodanie poczatek
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->dodajNaPoczatku(1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Dodanie na poczatku: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Dodanie random
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            int randomIndex = getRandomIndex(list->getRozmiar());
            auto start = high_resolution_clock::now();
            list->dodajNaPozycji(1, randomIndex);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Dodanie na losowej pozycji: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Dodanie koniec
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->dodaj(1);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Dodanie na koncu: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Usuniecie poczatek
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->usunPoczatek();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Usuniecie z poczatku: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Usuniecie random
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            int randomIndex = getRandomIndex(list->getRozmiar());
            auto start = high_resolution_clock::now();
            list->usun(randomIndex);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Usuniecie z losowej pozycji: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Usuniecie koniec
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            auto start = high_resolution_clock::now();
            list->usunKoniec();
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Usuniecie z konca: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Szukanie
        result = 0.0;
        for (int i = 0; i < x; i++) {
            ListaDwukierunkowa* list = setupDoublyLinkedList(originalData);
            int randomValue = originalData[getRandomIndex(originalData.size())];
            auto start = high_resolution_clock::now();
            list->szukaj(randomValue);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<nanoseconds>(stop - start).count();
            result += duration;
            delete list;
        }
        result /= x;
        cout << "Szukanie: " << result << " ns" << endl;
        doublyLinkedListResults.push_back(result);

        // Zapisanie wyników
        saveResultsToFile("DoublyLinkedList", n, doublyLinkedListResults);
    }

    auto stopfull = high_resolution_clock::now();
    auto fullDuration = duration_cast<seconds>(stopfull - startfull).count();
    cout << "\nCaly czas trwania testu: " << fullDuration << " s" << endl;
}

// Określony test
void runSpecificTest() {
    int n = 0;
    int x = 0;
    int operation = 0;
    int structureType = 0;

    cout << "Podaj liczbe elementow (n): ";
    cin >> n;

    cout << "Podaj liczbe powtorzen (x): ";
    cin >> x;

    cout << "\nPodaj ktora strukture testowac:\n";
    cout << "1. Dynamic Array\n";
    cout << "2. Singly Linked List\n";
    cout << "3. Doubly Linked List\n";
    cout << "Wybor: ";
    cin >> structureType;

    if (structureType < 1 || structureType > 3) {
        cout << "Niepoprawny wybor!" << endl;
        return;
    }

    cout << "\nPodaj ktora funkcje chcesz testowac:\n";
    cout << "1. Dodanie na poczatku\n";
    cout << "2. Dodanie na losowej pozycji\n";
    cout << "3. Dodanie na koncu\n";
    cout << "4. Usuniecie z poczatku\n";
    cout << "5. Usuniecie z losowej pozycji\n";
    cout << "6. Usuniecie z konca\n";
    cout << "7. Szukanie\n";
    cout << "Wybor: ";
    cin >> operation;

    if (operation < 1 || operation > 7) {
        cout << "Niepoprawny wybor!" << endl;
        return;
    }

    // Generowanie danych
    vector<int> originalData(n);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        originalData[i] = rand() % 1000;
    }

    long long totalTime = 0;

    cout << "Test trwa..." << endl;

    for (int i = 0; i < x; i++) {
        // Zapelnienie struktury
        void* dataStructure = nullptr;

        if (structureType == 1) {
            TablicaDynamiczna* arr = new TablicaDynamiczna();
            for (int val : originalData) {
                arr->dodaj(val);
            }
            dataStructure = arr;
        }
        else if (structureType == 2) {
            ListaJednokierunkowa* list = new ListaJednokierunkowa();
            for (int val : originalData) {
                list->dodaj(val);
            }
            dataStructure = list;
        }
        else {
            ListaDwukierunkowa* list = new ListaDwukierunkowa();
            for (int val : originalData) {
                list->dodaj(val);
            }
            dataStructure = list;
        }

        // Random wartosci
        int randomIndex = 0;
        int randomValue = 0;

        if (structureType == 1) {
            TablicaDynamiczna* arr = static_cast<TablicaDynamiczna*>(dataStructure);
            randomIndex = getRandomIndex(arr->getRozmiar());
            if (!originalData.empty()) {
                randomValue = originalData[getRandomIndex(originalData.size())];
            }
        }
        else if (structureType == 2) {
            ListaJednokierunkowa* list = static_cast<ListaJednokierunkowa*>(dataStructure);
            randomIndex = getRandomIndex(list->getRozmiar());
            if (!originalData.empty()) {
                randomValue = originalData[getRandomIndex(originalData.size())];
            }
        }
        else {
            ListaDwukierunkowa* list = static_cast<ListaDwukierunkowa*>(dataStructure);
            randomIndex = getRandomIndex(list->getRozmiar());
            if (!originalData.empty()) {
                randomValue = originalData[getRandomIndex(originalData.size())];
            }
        }

        // Zegar start
        auto start = high_resolution_clock::now();

        // Wybrana funkcja
        if (structureType == 1) {
            TablicaDynamiczna* arr = static_cast<TablicaDynamiczna*>(dataStructure);
            switch (operation) {
            case 1: arr->dodajNaPoczatku(1); break;
            case 2: arr->dodajNaPozycji(1, randomIndex); break;
            case 3: arr->dodaj(1); break;
            case 4: arr->usunPoczatek(); break;
            case 5: arr->usun(randomIndex); break;
            case 6: arr->usunKoniec(); break;
            case 7: arr->szukaj(randomValue); break;
            }
            delete arr;
        }
        else if (structureType == 2) {
            ListaJednokierunkowa* list = static_cast<ListaJednokierunkowa*>(dataStructure);
            switch (operation) {
            case 1: list->dodajNaPoczatku(1); break;
            case 2: list->dodajNaPozycji(1, randomIndex); break;
            case 3: list->dodaj(1); break;
            case 4: list->usunPoczatek(); break;
            case 5: list->usun(randomIndex); break;
            case 6: list->usunKoniec(); break;
            case 7: list->szukaj(randomValue); break;
            }
            delete list;
        }
        else {
            ListaDwukierunkowa* list = static_cast<ListaDwukierunkowa*>(dataStructure);
            switch (operation) {
            case 1: list->dodajNaPoczatku(1); break;
            case 2: list->dodajNaPozycji(1, randomIndex); break;
            case 3: list->dodaj(1); break;
            case 4: list->usunPoczatek(); break;
            case 5: list->usun(randomIndex); break;
            case 6: list->usunKoniec(); break;
            case 7: list->szukaj(randomValue); break;
            }
            delete list;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start).count();
        totalTime += duration;
    }

    double averageTime = (double)totalTime / x;
    cout << "Sredni czas trwania: " << averageTime << " ns" << endl;

    // Wynik
    string structureName;
    if (structureType == 1) structureName = "DynamicArray";
    else if (structureType == 2) structureName = "SinglyLinkedList";
    else structureName = "DoublyLinkedList";

    string operationName;
    switch (operation) {
    case 1: operationName = "Dodaj_poczatek"; break;
    case 2: operationName = "Dodaj_random"; break;
    case 3: operationName = "Dodaj_koniec"; break;
    case 4: operationName = "Usun_poczatek"; break;
    case 5: operationName = "Usun_random"; break;
    case 6: operationName = "Usun_koniec"; break;
    case 7: operationName = "Szukanie"; break;
    }

    string fileName = structureName + "_" + operationName + "_okreslony_test.txt";
    ofstream file(fileName);
    if (file.is_open()) {
        file << "Elementy\t" << operationName << endl;
        file << n << "\t" << fixed << setprecision(2) << averageTime << endl;
        file.close();
        cout << "Wynik zapisany do " << fileName << endl;
    }
    else {
        cout << "Nie otwarto pliku: " << fileName << endl;
    }
}

// Testy dla jednej wartości
void runComprehensiveTest() {
    int n = 0;
    int x = 0;

    cout << "Liczba elementow (n): ";
    cin >> n;

    cout << "Liczba powtorzen testow (x): ";
    cin >> x;

    // Wygenerowanie danych
    vector<int> originalData(n);
    srand(time(0));
    for (int i = 0; i < n; i++) {
        originalData[i] = rand() % 1000;
    }

    // Funkcje
    vector<string> operationNames = {
        "Dodanie na poczatku", "Dodanie na losowej pozycji", "Dodanie na koncu",
        "Usuniecie z poczatku", "Usuniecie z losowej pozycji", "Usuniecie z konca",
        "Znalezienie losowej wartosci"
    };

    // Wektory wynikow
    vector<double> dynamicArrayResults;
    vector<double> singlyLinkedListResults;
    vector<double> doublyLinkedListResults;

    // Wszystkie funkcje na wszytskich strukturach
    for (int structureType = 1; structureType <= 3; structureType++) {
        string structureName;
        if (structureType == 1) structureName = "Dynamic Array";
        else if (structureType == 2) structureName = "Singly Linked List";
        else structureName = "Doubly Linked List";

        cout << "\n===== " << structureName << " TESTS =====\n";

        vector<double>* currentResults = nullptr;
        if (structureType == 1) currentResults = &dynamicArrayResults;
        else if (structureType == 2) currentResults = &singlyLinkedListResults;
        else currentResults = &doublyLinkedListResults;

        for (int operation = 1; operation <= 7; operation++) {
            long long totalTime = 0;

            for (int i = 0; i < x; i++) {
                // Dodawanie danych
                void* dataStructure = nullptr;

                if (structureType == 1) {
                    TablicaDynamiczna* arr = new TablicaDynamiczna();
                    for (int val : originalData) {
                        arr->dodaj(val);
                    }
                    dataStructure = arr;
                }
                else if (structureType == 2) {
                    ListaJednokierunkowa* list = new ListaJednokierunkowa();
                    for (int val : originalData) {
                        list->dodaj(val);
                    }
                    dataStructure = list;
                }
                else {
                    ListaDwukierunkowa* list = new ListaDwukierunkowa();
                    for (int val : originalData) {
                        list->dodaj(val);
                    }
                    dataStructure = list;
                }

                // Losowe wartości
                int randomIndex = 0;
                int randomValue = 0;

                if (structureType == 1) {
                    TablicaDynamiczna* arr = static_cast<TablicaDynamiczna*>(dataStructure);
                    randomIndex = getRandomIndex(arr->getRozmiar());
                    if (!originalData.empty()) {
                        randomValue = originalData[getRandomIndex(originalData.size())];
                    }
                }
                else if (structureType == 2) {
                    ListaJednokierunkowa* list = static_cast<ListaJednokierunkowa*>(dataStructure);
                    randomIndex = getRandomIndex(list->getRozmiar());
                    if (!originalData.empty()) {
                        randomValue = originalData[getRandomIndex(originalData.size())];
                    }
                }
                else {
                    ListaDwukierunkowa* list = static_cast<ListaDwukierunkowa*>(dataStructure);
                    randomIndex = getRandomIndex(list->getRozmiar());
                    if (!originalData.empty()) {
                        randomValue = originalData[getRandomIndex(originalData.size())];
                    }
                }

                // Zegar
                auto start = high_resolution_clock::now();

                // Wykonanie operacji
                if (structureType == 1) {
                    TablicaDynamiczna* arr = static_cast<TablicaDynamiczna*>(dataStructure);
                    switch (operation) {
                    case 1: arr->dodajNaPoczatku(1); break;
                    case 2: arr->dodajNaPozycji(1, randomIndex); break;
                    case 3: arr->dodaj(1); break;
                    case 4: arr->usunPoczatek(); break;
                    case 5: arr->usun(randomIndex); break;
                    case 6: arr->usunKoniec(); break;
                    case 7: arr->szukaj(randomValue); break;
                    }
                    delete arr;
                }
                else if (structureType == 2) {
                    ListaJednokierunkowa* list = static_cast<ListaJednokierunkowa*>(dataStructure);
                    switch (operation) {
                    case 1: list->dodajNaPoczatku(1); break;
                    case 2: list->dodajNaPozycji(1, randomIndex); break;
                    case 3: list->dodaj(1); break;
                    case 4: list->usunPoczatek(); break;
                    case 5: list->usun(randomIndex); break;
                    case 6: list->usunKoniec(); break;
                    case 7: list->szukaj(randomValue); break;
                    }
                    delete list;
                }
                else {
                    ListaDwukierunkowa* list = static_cast<ListaDwukierunkowa*>(dataStructure);
                    switch (operation) {
                    case 1: list->dodajNaPoczatku(1); break;
                    case 2: list->dodajNaPozycji(1, randomIndex); break;
                    case 3: list->dodaj(1); break;
                    case 4: list->usunPoczatek(); break;
                    case 5: list->usun(randomIndex); break;
                    case 6: list->usunKoniec(); break;
                    case 7: list->szukaj(randomValue); break;
                    }
                    delete list;
                }

                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<nanoseconds>(stop - start).count();
                totalTime += duration;
            }

            double averageTime = (double)totalTime / x;
            cout << operationNames[operation - 1] << ": " << averageTime << " ns" << endl;
            currentResults->push_back(averageTime);
        }

        // Zapisanie wynikow
        string fileStructureName;
        if (structureType == 1) fileStructureName = "DynamicArray";
        else if (structureType == 2) fileStructureName = "SinglyLinkedList";
        else fileStructureName = "DoublyLinkedList";

        saveResultsToFile(fileStructureName, n, *currentResults);
    }
}

void menu() {
    TablicaDynamiczna tablica;
    ListaJednokierunkowa lista1;
    ListaDwukierunkowa lista2;

    int wyborStruktury = 0;
    while (true) {
        cout << "\n~~~~ WYBIERZ STRUKTURE DANYCH ~~~~\n";
        cout << "1. Tablica Dynamiczna\n";
        cout << "2. Lista Jednokierunkowa\n";
        cout << "3. Lista Dwukierunkowa\n";
        cout << "4. Testy wydajnosci\n";
        cout << "0. Wyjdz\n";
        cout << "Wybor: ";
        cin >> wyborStruktury;

        if (wyborStruktury == 0) break;
        else if (wyborStruktury == 4) {
            int testChoice = 0;
            cout << "\n~~~~ MENU TESTOW WYDAJNOSCI ~~~~\n";
            cout << "1. Uruchom wszystkie testy (predefiniowane)\n";
            cout << "2. Uruchom konkretny test\n";
            cout << "3. Uruchom kompleksowy test\n";
            cout << "0. Wroc\n";
            cout << "Wybor: ";
            cin >> testChoice;

            switch (testChoice) {
            case 1:
                runPerformanceTests();
                break;
            case 2:
                runSpecificTest();
                break;
            case 3:
                runComprehensiveTest();
                break;
            case 0:
                break;
            default:
                cout << "Nieprawidlowy wybor!" << endl;
            }
            continue;
        }
        else if (wyborStruktury >= 5) {
            cout << "Zla struktura!" << endl;
            continue;
        }

        int operacja = -1;
        while (operacja != 0) {
            cout << "\n~~~~ MENU OPERACJI ~~~~\n";
            cout << "1. Dodaj element na poczatku\n";
            cout << "2. Dodaj element na pozycji\n";
            cout << "3. Dodaj element na koniec\n";
            cout << "4. Usun element z poczatku\n";
            cout << "5. Usun element z pozycji\n";
            cout << "6. Usun element z konca\n";
            cout << "7. Wyswietl cala strukture\n";
            cout << "8. Szukaj elementu\n";
            cout << "9. Dodawanie losowych elementow\n";
            cout << "0. Wroc\n";
            cout << "Wybor: ";
            cin >> operacja;

            int wartosc, indeks, ilosc;
            switch (operacja) {
            case 1:
                cout << "Podaj liczbe do dodania na poczatek: ";
                cin >> wartosc;
                if (wyborStruktury == 1) tablica.dodajNaPoczatku(wartosc);
                else if (wyborStruktury == 2) lista1.dodajNaPoczatku(wartosc);
                else lista2.dodajNaPoczatku(wartosc);
                break;
            case 2:
                cout << "Podaj liczbe i indeks (lub -1 dla losowego indeksu): ";
                cin >> wartosc >> indeks;
                if (indeks == -1) {
                    if (wyborStruktury == 1) indeks = getRandomIndex(tablica.getRozmiar());
                    else if (wyborStruktury == 2) indeks = getRandomIndex(lista1.getRozmiar());
                    else indeks = getRandomIndex(lista2.getRozmiar());
                    cout << "Wylosowany indeks: " << indeks << endl;
                }
                if (wyborStruktury == 1) tablica.dodajNaPozycji(wartosc, indeks);
                else if (wyborStruktury == 2) lista1.dodajNaPozycji(wartosc, indeks);
                else lista2.dodajNaPozycji(wartosc, indeks);
                break;
            case 3:
                cout << "Podaj liczbe do dodania: ";
                cin >> wartosc;
                if (wyborStruktury == 1) tablica.dodaj(wartosc);
                else if (wyborStruktury == 2) lista1.dodaj(wartosc);
                else lista2.dodaj(wartosc);
                break;
            case 4:
                if (wyborStruktury == 1) tablica.usunPoczatek();
                else if (wyborStruktury == 2) lista1.usunPoczatek();
                else lista2.usunPoczatek();
                break;
            case 5:
                cout << "Podaj indeks do usuniecia (lub -1 dla losowego indeksu): ";
                cin >> indeks;
                if (indeks == -1) {
                    if (wyborStruktury == 1) indeks = getRandomIndex(tablica.getRozmiar());
                    else if (wyborStruktury == 2) indeks = getRandomIndex(lista1.getRozmiar());
                    else indeks = getRandomIndex(lista2.getRozmiar());
                    cout << "Wylosowany indeks: " << indeks << endl;
                }
                if (wyborStruktury == 1) tablica.usun(indeks);
                else if (wyborStruktury == 2) lista1.usun(indeks);
                else lista2.usun(indeks);
                break;
            case 6:
                if (wyborStruktury == 1) tablica.usunKoniec();
                else if (wyborStruktury == 2) lista1.usunKoniec();
                else lista2.usunKoniec();
                break;
            case 7:
                if (wyborStruktury == 1) {
                    tablica.wyswietl();
                    cout << "Rozmiar: " << tablica.getRozmiar() << endl;
                }
                else if (wyborStruktury == 2) {
                    lista1.wyswietl();
                    cout << "Rozmiar: " << lista1.getRozmiar() << endl;
                }
                else {
                    lista2.wyswietl();
                    cout << "Rozmiar: " << lista2.getRozmiar() << endl;
                }
                break;
            case 8:
                cout << "Podaj liczbe do wyszukania (lub -1 dla losowej liczby): ";
                cin >> wartosc;
                if (wartosc == -1) {
                    if (wyborStruktury == 1 && tablica.getRozmiar() > 0) {
                        indeks = getRandomIndex(tablica.getRozmiar());
                        wartosc = tablica.get(indeks);
                    }
                    else if (wyborStruktury == 2 && lista1.getRozmiar() > 0) {
                        indeks = getRandomIndex(lista1.getRozmiar());
                        wartosc = lista1.get(indeks);
                    }
                    else if (lista2.getRozmiar() > 0) {
                        indeks = getRandomIndex(lista2.getRozmiar());
                        wartosc = lista2.get(indeks);
                    }
                    else {
                        wartosc = rand() % 1000;
                    }
                    cout << "Wylosowana liczba: " << wartosc << endl;
                }
                if (wyborStruktury == 1) tablica.szukaj(wartosc);
                else if (wyborStruktury == 2) lista1.szukaj(wartosc);
                else lista2.szukaj(wartosc);
                break;
            case 9:
                cout << "Podaj ilosc liczb do losowego dodania: ";
                cin >> ilosc;
                for (int i = 1; i < ilosc + 1; i++) {
                    if (wyborStruktury == 1) tablica.dodaj((rand()) % 1000);
                    else if (wyborStruktury == 2) lista1.dodaj(rand() % 1000);
                    else lista2.dodaj(rand() % 1000);
                }
                break;
            case 0:
                break;
            default:
                cout << "Nieprawidlowy wybor!" << endl;
            }
        }
    }

    cout << "Koniec programu!" << endl;
}

int main() {
    menu();
    return 0;
}
