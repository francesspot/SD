#ifndef TWO_CHOICE_HPP
#define TWO_CHOICE_HPP

#include <iostream>

class Two_choice {
    private:
        struct Node {
            long long data; 
            Node* next;
            Node(long long val) : data(val), next(nullptr) {}
        };

        int capacity;
        Node** table;
        int* sizes; 

        int hashing_1(long long key) const { 
            return (key < 0 ? -key : key) % capacity;
        }
        
        int hashing_2(long long key) const { 
            return ((key < 0 ? -key : key) / capacity + 7) % capacity;
        }

        bool removeFromBucket(int idx, long long key) { 
            Node *curr = table[idx], *prev = nullptr;
            while (curr) {
                if (curr->data == key) {
                    if (!prev) table[idx] = curr->next;
                    else prev->next = curr->next;
                    
                    delete curr;
                    sizes[idx]--;
                    return true;
                }
                prev = curr;
                curr = curr->next;
            }
            return false;
        }

    public:
        Two_choice(int size) : capacity(size) {
            table = new Node*[capacity]();
            sizes = new int[capacity]();
        }

        ~Two_choice() {
            for (int i = 0; i < capacity; i++) {
                Node* curr = table[i];
                while (curr) {
                    Node* temp = curr;
                    curr = curr->next;
                    delete temp;
                }
            }
            delete[] table;
            delete[] sizes;
        }

        void insert(long long key) { 
            int idx1 = hashing_1(key);
            int idx2 = hashing_2(key);

            int targetIdx = (sizes[idx1] <= sizes[idx2]) ? idx1 : idx2;

            Node* newNode = new Node(key);
            newNode->next = table[targetIdx];
            table[targetIdx] = newNode;
            
            sizes[targetIdx]++;
        }

        bool remove(long long key) { 
            if (removeFromBucket(hashing_1(key), key)) return true;
            return removeFromBucket(hashing_2(key), key);
        }

        void display() const {
            for (int i = 0; i < capacity; i++) {
                std::cout << "[" << i << "](size:" << sizes[i] << "): ";
                Node* temp = table[i];
                while (temp) {
                    std::cout << temp->data << " -> ";
                    temp = temp->next;
                }
                std::cout << "null\n";
            }
        }
};

#endif // TWO_CHOICE_HPP