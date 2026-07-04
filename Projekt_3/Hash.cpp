#include <iostream>

struct Node{
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr){}
};

class Separate_chaining {
private:
    int capacity;
    Node** table;

    int hashing_0(int key){
        return ( (key < 0 ? -key : key) % capacity);
    }

public:
    Separate_chaining(int size) : capacity(size){
        table = new Node*[capacity]();
    }

    ~Separate_chaining() {
        for(int i = 0; i < capacity; i++){
            Node* curr = table[i];
            while(curr){
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
    }

    void insert(int key) {
        int idx = hashing_0(key);
        Node* newNode = new Node(key);
        newNode->next = table[idx];
        table[idx] = newNode;
    }

    bool remove(int key) {
        int idx = hashing_0(key);
        Node *curr = table[idx], *prev = nullptr;
        while(curr){
            if(curr->data == key){
                if(!prev) table[idx] = curr->next;
                else prev->next = curr->next;
                delete curr;
                return true;
            }
            prev = curr; curr = curr->next;
        }
        return false;
    }
  void display() {
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

class Two_choice {
private:
    int capacity;
    Node** table;
    int* sizes; //Tabela pomocnicza, aby O(1) sprawdzać, jaki kubełek ma mniej elementów

    int hashing_1(int key){
        return(key < 0 ? -key : key) % capacity;
    }
    int hashing_2(int key){
        return((key < 0 ? -key : key) / capacity + 7) % capacity;
    }

public:
    Two_choice(int size) : capacity(size){
        table = new Node*[capacity]();
        sizes = new int[capacity]();
    }

    ~Two_choice() {
        for(int i = 0; i < capacity; i++){
            Node* curr = table[i];
            while(curr){
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
        delete[] table;
        delete[] sizes;
    }

    void insert(int key) {
        int idx1 = hashing_1(key);
        int idx2 = hashing_2(key);

        int targetIdx =(sizes[idx1] <= sizes[idx2]) ? idx1 : idx2;

        Node* newNode = new Node(key);
        newNode->next = table[targetIdx];
        table[targetIdx] = newNode;
        
        sizes[targetIdx]++;
    }

    bool remove(int key) {
        if(removeFromBucket(hashing_1(key), key)) return true;
        return removeFromBucket(hashing_2(key), key);
    }

    bool removeFromBucket(int idx, int key){
        Node *curr = table[idx], *prev = nullptr;
        while(curr){
            if(curr->data == key){
                if(!prev) table[idx] = curr->next;
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
  void display() {
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
int main() {
    std::cout << "--- SEPARATE CHAINING ---\n";
    Separate_chaining sc(5);
    sc.insert(10); // idx 0
    sc.insert(15); // idx 0 - kolizja
    sc.insert(20); // idx 0 - kolejna kolizja
    sc.display();
    std::cout << "\n--- 2-CHOICE HASHING ---\n";
    Two_choice tc(5);
    tc.insert(10); // moze trafic do idx 0 lub innego z h2
    tc.insert(15); // jesli idx 0 jest zajety, moze wybrac alternatywe z h2
    tc.insert(20);
    tc.display();
    return 0;
}
