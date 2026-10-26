**Polski** | [English](README.en.md)

# Struktury Danych — projekty (SD)

Trzy projekty w C++ z kursu *Struktury Danych*. W każdym struktury są zaimplementowane od podstaw, a następnie przetestowane wydajnościowo: każda operacja jest mierzona na 50 kopiach struktury dla różnych rozmiarów, a uśrednione wyniki trafiają do plików CSV i wykresów w Excelu.

| Projekt | Temat | Porównywane struktury |
|---------|-------|-----------------------|
| [`Projekt_1`](Projekt_1) | Listy wiązane a tablica dynamiczna | lista jednokierunkowa, lista dwukierunkowa, tablica dynamiczna (pojemność rośnie x2) |
| [`Projekt_2`](Projekt_2) | Kolejki priorytetowe | lista wiązana, kopiec binarny, treap (drzewo + kopiec) |
| [`Projekt_3`](Projekt_3) | Tablice mieszające | metoda łańcuchowa, adresowanie otwarte, haszowanie z dwoma wyborami |

## Projekt_1 — listy i tablica dynamiczna

Mierzone operacje: dodawanie i usuwanie na **początku**, na **końcu** i pod **wybranym indeksem** (środek), a także **wyszukiwanie** wartości.
Rozmiary: 1 000 – 1 000 000 elementów. Wyniki: `results.csv`, wykresy: `results_charts.xlsx`.

## Projekt_2 — kolejki priorytetowe

Mierzone operacje: **dodanie**, **usunięcie** elementu o najwyższym priorytecie, **rozmiar**, **peek** oraz **zmiana priorytetu** wybranego elementu.
Rozmiary: 1 000 – 50 000 elementów. Osobno zmierzono przypadek optymistyczny, średni i pesymistyczny — zob. pliki `results_priority_queue*.csv` i odpowiadające im `*_charts.xlsx`.

## Projekt_3 — tablice mieszające

Mierzone operacje: **wstawienie** i **usunięcie** klucza.
Rozmiary: 1 000 – 1 000 000 kluczy, w trzech scenariuszach:

- **optymistyczny** — kolejne klucze, brak kolizji,
- **średni** — klucze losowe,
- **pesymistyczny** — klucze dobrane tak, by wszystkie trafiały do tego samego miejsca (rozmiary powyżej 500 000 są pomijane, bo koszt rośnie do O(n²)).

Wyniki: `wyniki_Hash_<scenariusz>.csv` oraz `*_wykresy.xlsx`.

## Kompilacja i uruchomienie

Każdy projekt to jeden `main.cpp`, który dołącza własne nagłówki:

```bash
cd Projekt_3
g++ -std=c++17 -O2 main.cpp -o main
./main
```

Pliki CSV używają separatora `;`. Czasy podane są w nanosekundach.
