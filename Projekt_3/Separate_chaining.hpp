#ifndef SEPARATE_CHAINING_HPP
#define SEPARATE_CHAINING_HPP

#include <iostream>

class Separate_chaining {
    private:
        struct Node {
            long long data; 
            Node* next;
            Node(long long val) : data(val), next(nullptr) {}
        };

        int capacity;
        Node** table;

        int hashing_0(long long key) const {
            return ((key < 0 ? -key : key) % capacity);
        }

    public:
        Separate_chaining(int size) : capacity(size) {
            table = new Node*[capacity]();
        }

        ~Separate_chaining() {
            for (int i = 0; i < capacity; i++) {
                Node* curr = table[i];
                while (curr) {
                    Node* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
            }
            delete[] table;
        }

        void insert(long long key) { 
            int idx = hashing_0(key);
            Node* newNode = new Node(key);
            newNode->next = table[idx];
            table[idx] = newNode;
        }

        bool remove(long long key) { 
            int idx = hashing_0(key);
            Node *curr = table[idx], *prev = nullptr;
            while (curr) {
                if (curr->data == key) {
                    if (!prev) table[idx] = curr->next;
                    else prev->next = curr->next;
                    delete curr;
                    return true;
                }
                prev = curr; 
                curr = curr->next;
            }
            return false;
        }

        void display() const {
            for (int i = 0; i < capacity; i++) {
                std::cout << "[" << i << "]: ";
                Node* temp = table[i];
                while (temp) {
                    std::cout << temp->data << " -> ";
                    temp = temp->next;
                }
                std::cout << "nullptr\n";
            }
        }
};

#endif // SEPARATE_CHAINING_HPP