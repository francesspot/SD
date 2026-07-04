#ifndef OPEN_ADDRESSING_HPP
#define OPEN_ADDRESSING_HPP

#include <iostream>

class Open_addresing {
    private:
        enum class SlotState {
            EMPTY,
            OCCUPIED,
            DELETED
        };

        struct Slot {
            long long key = 0; 
            SlotState status = SlotState::EMPTY;
        };

        int capacity;
        int count;
        Slot* table;

        int hashing_0(long long key) const { 
            return (key < 0 ? -key : key) % capacity;
        }

    public:
        Open_addresing(int size) : capacity(size), count(0) {
            table = new Slot[capacity];
        }

        ~Open_addresing() {
            delete[] table;
        }

        void insert(long long key) { 
            if (count >= capacity) {
                std::cerr << "Tablica pelna!\n";
                return;
            }
            
            int base = hashing_0(key);
            int first_deleted = -1;
            int idx = base; 

            for (int i = 0; i < capacity; i++) {
                if (table[idx].status == SlotState::OCCUPIED) {
                    if (table[idx].key == key) return; 
                }
                else if (table[idx].status == SlotState::DELETED) {
                    if (first_deleted == -1) {
                        first_deleted = idx;
                    }
                }
                else { 
                    int insertAt = (first_deleted != -1) ? first_deleted : idx;
                    table[insertAt].key = key;
                    table[insertAt].status = SlotState::OCCUPIED;
                    count++;
                    return;
                }
                
                idx++;
                if (idx >= capacity) {
                    idx = 0;
                }
            }

            if (first_deleted != -1) {
                table[first_deleted].key = key;
                table[first_deleted].status = SlotState::OCCUPIED;
                count++;
            }
        }

        bool remove(long long key) { 
            int base = hashing_0(key);
            int idx = base; 
            
            for (int i = 0; i < capacity; i++) {
                if (table[idx].status == SlotState::EMPTY) {
                    return false; 
                }
                if (table[idx].status == SlotState::OCCUPIED && table[idx].key == key) {
                    table[idx].status = SlotState::DELETED;
                    count--;
                    return true;
                }
                
                idx++;
                if (idx >= capacity) {
                    idx = 0;
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

#endif // OPEN_ADDRESSING_HPP