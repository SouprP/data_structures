#include <thread>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <headers/visualiser.h>

// int main(int argc, char** argv){
//     // visualiser / menu boot
//     // then based on what we choose we create a thread 
//     // which enables us to test data structures
//     //std::cout << "test";
//     Visualiser *visuals = new Visualiser();

//     getch();
//     delete visuals;

//     return 0;
// }

using namespace std;

// Struktura danych: Tablica dynamiczna (ArrayList)

class ArrayList {
private:
    int* arr;
    int capacity;
    int size;

public:
    ArrayList() {
        capacity = 10; // Początkowy rozmiar tablicy
        arr = new int[capacity];
        size = 0;
    }

    ~ArrayList() {
        delete[] arr;
    }

    void add(int element) {
        if (size == capacity) {
            // Jeśli tablica jest pełna, zwiększ jej rozmiar dwukrotnie
            capacity *= 2;
            int* newArr = new int[capacity];
            for (int i = 0; i < size; ++i) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = element;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Nieprawidłowy indeks" << endl;
            return;
        }
        for (int i = index; i < size - 1; ++i) {
            arr[i] = arr[i + 1];
        }
        --size;
    }

    int get(int index) {
        if (index < 0 || index >= size) {
            cout << "Nieprawidłowy indeks" << endl;
            return -1;
        }
        return arr[index];
    }

    int getSize() {
        return size;
    }
};

// Struktura danych: Lista jednokierunkowa (Singly Linked List)

class Node {
public:
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() {
        head = nullptr;
    }

    ~SinglyLinkedList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void add(int element) {
        if (head == nullptr) {
            head = new Node(element);
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new Node(element);
        }
    }

    void remove(int index) {
        if (index < 0) {
            cout << "Nieprawidłowy indeks" << endl;
            return;
        }
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1; ++i) {
            if (current == nullptr) {
                cout << "Nieprawidłowy indeks" << endl;
                return;
            }
            current = current->next;
        }
        if (current == nullptr || current->next == nullptr) {
            cout << "Nieprawidłowy indeks" << endl;
            return;
        }
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }

    int get(int index) {
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            if (current == nullptr) {
                cout << "Nieprawidłowy indeks" << endl;
                return -1;
            }
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Nieprawidłowy indeks" << endl;
            return -1;
        }
        return current->data;
    }

    int getSize() {
        int count = 0;
        Node* current = head;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }
};

// Struktura danych: Lista dwukierunkowa (Doubly Linked List)

class DoublyNode {
public:
    int data;
    DoublyNode* prev;
    DoublyNode* next;

    DoublyNode(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
private:
    DoublyNode* head;
    DoublyNode* tail;

public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoublyLinkedList() {
        DoublyNode* current = head;
        while (current != nullptr) {
            DoublyNode* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void add(int element) {
        if (head == nullptr) {
            head = new DoublyNode(element);
            tail = head;
        } else {
            tail->next = new DoublyNode(element);
            tail->next->prev = tail;
            tail = tail->next;
        }
    }

    void remove(int index) {
        if (index < 0) {
            cout << "Nieprawidłowy indeks" << endl;
            return;
        }
        if (index == 0) {
            if (head == nullptr) {
                cout << "Nieprawidłowy indeks" << endl;
                return;
            }
            DoublyNode* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete temp;
            return;
        }
        DoublyNode* current = head;
        for (int i = 0; i < index; ++i) {
            if (current == nullptr) {
                cout << "Nieprawidłowy indeks" << endl;
                return;
            }
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Nieprawidłowy indeks" << endl;
            return;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }
        delete current;
    }

    int get(int index) {
        DoublyNode* current = head;
        for (int i = 0; i < index; ++i) {
            if (current == nullptr) {
                cout << "Nieprawidłowy indeks" << endl;
                return -1;
            }
            current = current->next;
        }
        if (current == nullptr) {
            cout << "Nieprawidłowy indeks" << endl;
            return -1;
        }
        return current->data;
    }

    int getSize() {
        int count = 0;
        DoublyNode* current = head;
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }
};

// Funkcja do pomiaru czasu

double measureTime(void (*function)(int), int arg) {
    clock_t start, end;
    start = clock();
    function(arg);
    end = clock();
    return ((double) (end - start)) / CLOCKS_PER_SEC;
}

// Funkcje do generowania losowych danych

void generateRandomData(int* data, int size) {
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        data[i] = rand();
    }
}

void generateRandomIndices(int* indices, int size, int maxIndex) {
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        indices[i] = rand() % maxIndex;
    }
}

// Funkcje testujące operacje na strukturach danych

void testArrayList(int size) {
    ArrayList list;
    int* data = new int[size];
    generateRandomData(data, size);

    for (int i = 0; i < size; ++i) {
        list.add(data[i]);
    }

    delete[] data;
}

void testSinglyLinkedList(int size) {
    SinglyLinkedList list;
    int* data = new int[size];
    generateRandomData(data, size);

    for (int i = 0; i < size; ++i) {
        list.add(data[i]);
    }

    delete[] data;
}

void testDoublyLinkedList(int size) {
    DoublyLinkedList list;
    int* data = new int[size];
    generateRandomData(data, size);

    for (int i = 0; i < size; ++i) {
        list.add(data[i]);
    }

    delete[] data;
}

int main() {
    int sizes[] = {5000, 8000, 10000, 16000, 20000, 40000, 60000, };
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    cout << "Pomiar czasu dodawania elementów do ArrayList:" << endl;
    for (int i = 0; i < numSizes; ++i) {
        double time = measureTime(testArrayList, sizes[i]);
        cout << "Rozmiar: " << sizes[i] << ", Czas: " << time << "s" << endl;
    }

    cout << endl << "Pomiar czasu dodawania elementów do SinglyLinkedList:" << endl;
    for (int i = 0; i < numSizes; ++i) {
        double time = measureTime(testSinglyLinkedList, sizes[i]);
        cout << "Rozmiar: " << sizes[i] << ", Czas: " << time << "s" << endl;
    }

    cout << endl << "Pomiar czasu dodawania elementów do DoublyLinkedList:" << endl;
    for (int i = 0; i < numSizes; ++i) {
        double time = measureTime(testDoublyLinkedList, sizes[i]);
        cout << "Rozmiar: " << sizes[i] << ", Czas: " << time << "s" << endl;
    }

    return 0;
}
