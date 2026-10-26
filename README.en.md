🇵🇱 [Polski](README.md) | 🇬🇧 **English**

# 🧱 Data Structures — Implementations & Benchmarks

![C++](https://img.shields.io/badge/C++-00599C?logo=cplusplus&logoColor=white) ![Excel](https://img.shields.io/badge/Excel-217346?logo=microsoftexcel&logoColor=white)

> 🎓 Projects for the **Data Structures** course (Wrocław University of Science and Technology), done in a pair

Three projects in which data structures were implemented from scratch and then compared for performance. Every operation was timed on 50 copies of the structure and the results were charted.

## 📦 Projects

| Project | Topic | What's compared |
|---|---|---|
| [`Projekt_1`](Projekt_1) | Lists vs dynamic array | singly and doubly linked list, dynamic array (doubles when full) — insert, remove and search, up to **1M** elements |
| [`Projekt_2`](Projekt_2) | Priority queues | linked list, binary heap, treap — insert, extract, peek, change priority, in best, average and worst cases |
| [`Projekt_3`](Projekt_3) | Hash tables | separate chaining, two-choice hashing and **open addressing** (my part) — with no collisions, random keys, and keys that all collide |

## 🛠️ Tech

C++17 · `std::chrono` · Excel (charts)

## 🚀 Run it

Each project is a single `main.cpp`:

```bash
cd Projekt_3
g++ -std=c++17 -O2 main.cpp -o main
./main
```
