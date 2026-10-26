[Polski](README.md) | **English**

# Data Structures — Projects (SD)

Three C++ projects for the *Data Structures* (Struktury Danych) course. In each one the structures are implemented from scratch and then benchmarked: every operation is timed on 50 copies of the structure for a range of sizes, and the averaged results are saved to CSV and charted in Excel.

| Project | Topic | Structures compared |
|---------|-------|---------------------|
| [`Projekt_1`](Projekt_1) | Linked lists vs dynamic array | singly linked list, doubly linked list, dynamic array (capacity doubles when full) |
| [`Projekt_2`](Projekt_2) | Priority queues | linked list, binary heap, treap (tree + heap) |
| [`Projekt_3`](Projekt_3) | Hash tables | separate chaining, open addressing, two-choice hashing |

## Projekt_1 — lists and dynamic array

Operations measured: insertion and removal at the **front**, at the **back** and at a **chosen index** (middle), plus **searching** for a value.
Sizes: 1 000 – 1 000 000 elements. Results: `results.csv`, charts: `results_charts.xlsx`.

## Projekt_2 — priority queues

Operations measured: **insert**, **extract** (remove the highest-priority element), **size**, **peek** and **modify the priority** of a given element.
Sizes: 1 000 – 50 000 elements. Best, average and worst cases were measured separately — see the `results_priority_queue*.csv` files and the matching `*_charts.xlsx` workbooks.

## Projekt_3 — hash tables

Operations measured: **insert** and **remove** a key.
Sizes: 1 000 – 1 000 000 keys, in three scenarios:

- **optimistic** (`Optymistyczny`) — consecutive keys, no collisions,
- **average** (`Sredni`) — random keys,
- **pessimistic** (`Pesymistyczny`) — keys chosen so that they all hash to the same slot (sizes above 500 000 are skipped, as the cost becomes O(n²)).

Results: `wyniki_Hash_<scenario>.csv` and `*_wykresy.xlsx`.

## Build and run

Each project is a single `main.cpp` that includes its own headers:

```bash
cd Projekt_3
g++ -std=c++17 -O2 main.cpp -o main
./main
```

The CSV files use `;` as the separator. Times are given in nanoseconds.
