#include <iostream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>

#include "Open_addressing.hpp"
#include "Separate_chaining.hpp"
#include "Two_choice.hpp"

using namespace std;
using namespace std::chrono;

void createCopiesOA(Open_addresing** arr, int numCopies, int size, long long* keys) {
    int capacity = size * 2;  // Zwiększenie rozmiaru tablicy dla Open Addressing, aby uniknąć zbyt dużej liczby kolizji
    for (int i = 0; i < numCopies; i++) {
        arr[i] = new Open_addresing(capacity);
        for (int k = 0; k < size; k++) arr[i]->insert(keys[k]);
    }
}

void createCopiesSC(Separate_chaining** arr, int numCopies, int size, long long* keys) {
    for (int i = 0; i < numCopies; i++) {
        arr[i] = new Separate_chaining(size);
        for (int k = 0; k < size; k++) arr[i]->insert(keys[k]);
    }
}

void createCopiesTC(Two_choice** arr, int numCopies, int size, long long* keys) {
    for (int i = 0; i < numCopies; i++) {
        arr[i] = new Two_choice(size);
        for (int k = 0; k < size; k++) arr[i]->insert(keys[k]);
    }
}

template <typename T>
void deleteCopies(T** copiesArr, int numCopies) {
    for (int i = 0; i < numCopies; i++) {
        delete copiesArr[i];
    }
}

int main() {
    srand(time(NULL)); 
    int numCopies = 50; 
    
    vector<int> tableSizes = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};
    
    Open_addresing** oa_copies = new Open_addresing*[numCopies];
    Separate_chaining** sc_copies = new Separate_chaining*[numCopies];
    Two_choice** tc_copies = new Two_choice*[numCopies];

    string scenarios[] = {"Optymistyczny", "Sredni", "Pesymistyczny"};

    for (int scen = 0; scen < 3; scen++) {
        string filename = "wyniki_Hash_" + scenarios[scen] + ".csv";
        ofstream file(filename);
        file << "Size;SC_Add;TC_Add;OA_Add;SC_Remove;TC_Remove;OA_Remove\n";

        cout << "\n======================================================\n";
        cout << "ROZPOCZECIE TESTOW - PRZYPADEK: " << scenarios[scen] << "\n";
        cout << "======================================================\n";

        for (int size : tableSizes) {

            if (scen == 2 && size > 500000) { 
                cout << "Pominieto N=" << size << " (Zbyt dlugi czas oczekiwania dla O(N^2))\n";
                continue; 
            }
            
            long long oa_add = 0, sc_add = 0, tc_add = 0;
            long long oa_rem = 0, sc_rem = 0, tc_rem = 0;
            
            int capacityOA = size * 2;
            long long* keysToInsert = new long long[size]; 

            for (int i = 0; i < size; i++) {
                if (scen == 0) {
                    keysToInsert[i] = i; 
                } 
                else if (scen == 1) {
                    keysToInsert[i] = rand() % 20000000; 
                } 
                else if (scen == 2) {
                    // Rzutowanie na long long, aby uniknąć przekroczenia zakresu int dla większych rozmiarów
                    keysToInsert[i] = (long long)(i + 1) * capacityOA; 
                }
            }

            long long keyToAdd, keyToRemove; 
            if (scen == 0) {
                keyToAdd = size;                 
                keyToRemove = keysToInsert[size - 1]; 
            } else if (scen == 1) {
                keyToAdd = rand() % 20000000;
                keyToRemove = keysToInsert[size / 2]; 
            } else {
                keyToAdd = (long long)(size + 2) * capacityOA;   
                keyToRemove = keysToInsert[size - 1]; 
            }

            auto start = high_resolution_clock::now();
            auto end = high_resolution_clock::now();
            
            // --- INSERT ---
            // 1. Separate Chaining
            createCopiesSC(sc_copies, numCopies, size, keysToInsert);
            start = high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) sc_copies[i]->insert(keyToAdd);
            end = high_resolution_clock::now();
            sc_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
            deleteCopies(sc_copies, numCopies);

            // 2. Two Choice
            createCopiesTC(tc_copies, numCopies, size, keysToInsert);
            start = high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) tc_copies[i]->insert(keyToAdd);
            end = high_resolution_clock::now();
            tc_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
            deleteCopies(tc_copies, numCopies);

            // 3. Open Addressing
            createCopiesOA(oa_copies, numCopies, size, keysToInsert);
            start = high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) oa_copies[i]->insert(keyToAdd);
            end = high_resolution_clock::now();
            oa_add = duration_cast<nanoseconds>(end - start).count() / numCopies;
            deleteCopies(oa_copies, numCopies);

            // --- REMOVE ---
            // 1. Separate Chaining
            createCopiesSC(sc_copies, numCopies, size, keysToInsert);
            start = high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) sc_copies[i]->remove(keyToRemove);
            end = high_resolution_clock::now();
            sc_rem = duration_cast<nanoseconds>(end - start).count() / numCopies;
            deleteCopies(sc_copies, numCopies);

            // 2. Two Choice
            createCopiesTC(tc_copies, numCopies, size, keysToInsert);
            start = high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) tc_copies[i]->remove(keyToRemove);
            end = high_resolution_clock::now();
            tc_rem = duration_cast<nanoseconds>(end - start).count() / numCopies;
            deleteCopies(tc_copies, numCopies);

            // 3. Open Addressing
            createCopiesOA(oa_copies, numCopies, size, keysToInsert);
            start = high_resolution_clock::now();
            for (int i = 0; i < numCopies; ++i) oa_copies[i]->remove(keyToRemove);
            end = high_resolution_clock::now();
            oa_rem = duration_cast<nanoseconds>(end - start).count() / numCopies;
            deleteCopies(oa_copies, numCopies);

            delete[] keysToInsert;

            // Zapis do pliku CSV
            file << size << ";" 
                 << sc_add << ";" << tc_add << ";" << oa_add << ";"
                 << sc_rem << ";" << tc_rem << ";" << oa_rem << "\n";

            cout << "\nOperacje dla N = " << size << "\n";
            cout << string(75, '-') << "\n";
            cout << left << setw(15) << "Operacja" << setw(20) << "Sep Chain [ns]" << setw(20) << "Two Choice [ns]" << setw(20) << "Open Addr [ns]" << "\n";
            cout << string(75, '-') << "\n";
            cout << left << setw(15) << "1. add"      << setw(20) << sc_add << setw(20) << tc_add << setw(20) << oa_add << "\n";
            cout << left << setw(15) << "2. remove"   << setw(20) << sc_rem << setw(20) << tc_rem << setw(20) << oa_rem << "\n";
        }
        file.close(); 
    }

    delete[] oa_copies;
    delete[] sc_copies;
    delete[] tc_copies;

    return 0;
}