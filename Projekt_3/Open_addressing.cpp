#include <iostream>

enum class SlotState {
  EMPTY,
  OCCUPIED,
  DELETED
};

struct Slot {
  int key = 0;
  SlotState status = SlotState::EMPTY;
};

class Open_addresing {
  private:
    int capacity;
    int count;
    Slot* table;

    int hashing_0(int key) const {
      return (key < 0 ? -key : key) % capacity;
    }

  public:
    Open_addresing(int size) : capacity(size), count(0) {
      table = new Slot[capacity];
    }

    ~Open_addresing() {
      delete[] table;
    }

    void insert(int key) {
      if (count >= capacity) {
        std::cerr << "Tablica pelna!\n";
        return;
      }
      int base = hashing_0(key);
      int first_deleted = -1;

      for (int i = 0; i < capacity; i++) {
        int idx = (base + i) % capacity;

        if (table[idx].status == SlotState::OCCUPIED) {
          if (table[idx].key == key) return; 
          continue; 
        }
        if (table[idx].status == SlotState::DELETED) {
          if (first_deleted == -1) {
            first_deleted = idx;
            continue;
          }
        }

        int insertAt = (first_deleted != -1) ? first_deleted : idx;
        table[insertAt].key = key;
        table[insertAt].status = SlotState::OCCUPIED;
        count++;
        return;
      }

      if (first_deleted != -1) {
        table[first_deleted].key = key;
        table[first_deleted].status = SlotState::OCCUPIED;
        count++;
      }
    }

    bool remove(int key) {
      int base = hashing_0(key);
      for (int i = 0; i < capacity; i++) {
        int idx = (base + i) % capacity;
        if (table[idx].status == SlotState::EMPTY) {
          return false; // nie ma
        }
        if (table[idx].status == SlotState::OCCUPIED && table[idx].key == key) {
          table[idx].status = SlotState::DELETED;
          count--;
          return true;
        }
      }
      return false;
    }

    void display() const {
      for (int i = 0; i < capacity; i++) {
        std::cout << "[" << i << "]: ";
        switch (table[i].status) {
          case SlotState::EMPTY: {
            std::cout << "EMPTY\n";
            break;
          }
          case SlotState::DELETED: {
            std::cout << "DELETED\n";
            break;
          }
          case SlotState::OCCUPIED: {
            std::cout << table[i].key << "\n";
            break;
          }
        }
      }
    }
};

int main() {
  std::cout << "--- OPEN ADDRESSING (Linear Probing) ---\n";
  Open_addresing oa(5);
  oa.insert(10);
  oa.insert(15);
  oa.insert(20);
  oa.display();
  std::cout << "\nPo usunieciu 15:\n";
  oa.remove(15);
  oa.display();
  return 0;
}