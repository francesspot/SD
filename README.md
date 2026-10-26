🇵🇱 **Polski** | 🇬🇧 [English](README.en.md)

# 🧱 Struktury danych — implementacje i testy wydajności

![C++](https://img.shields.io/badge/C++-00599C?logo=cplusplus&logoColor=white) ![Excel](https://img.shields.io/badge/Excel-217346?logo=microsoftexcel&logoColor=white)

> 🎓 Projekty na przedmiot **Struktury Danych** (Politechnika Wrocławska), realizowane w parze

Trzy projekty, w których implementowaliśmy struktury danych od zera, a potem sprawdzaliśmy w praktyce, jak szybkie są ich operacje. Każdą operację mierzyliśmy na 50 kopiach struktury i porównywaliśmy wyniki na wykresach. 📈

## 📦 Projekty

| | Temat | Co porównujemy |
|---|---|---|
| 1️⃣ [`Projekt_1`](Projekt_1) | Listy a tablica dynamiczna | lista jednokierunkowa, dwukierunkowa, tablica dynamiczna (×2 przy zapełnieniu) — dodawanie, usuwanie i szukanie, do **1 mln** elementów |
| 2️⃣ [`Projekt_2`](Projekt_2) | Kolejki priorytetowe | lista wiązana, kopiec binarny, treap — insert, extract, peek, zmiana priorytetu, w przypadku optymistycznym, średnim i pesymistycznym |
| 3️⃣ [`Projekt_3`](Projekt_3) | Tablice mieszające | metoda łańcuchowa, haszowanie z dwoma wyborami i **adresowanie otwarte** (moja część) — w scenariuszu bez kolizji, losowym i takim, w którym wszystko koliduje |

## 🛠️ Technologie

C++17 · `std::chrono` · Excel (wykresy)

## 🚀 Uruchomienie

Każdy projekt to jeden `main.cpp`:

```bash
cd Projekt_3
g++ -std=c++17 -O2 main.cpp -o main
./main
```
