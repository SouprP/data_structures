//
// Created by Gaming PC on 14.05.2024.
//

#ifndef PROJECT_2_PRIORITY_QUEUE_FIBONACCIHEAP_H
#define PROJECT_2_PRIORITY_QUEUE_FIBONACCIHEAP_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Struktura węzła kopca Fibonacciego
struct FibNode {
    int value; // Wartość elementu
    int priority; // Priorytet
    bool mark; // Czy węzeł był usunięty z dziecka
    FibNode* parent; // Wskaźnik na rodzica
    FibNode* child; // Wskaźnik na pierwsze dziecko
    FibNode* left; // Wskaźnik na lewe dziecko (w lewo od obecnego)
    FibNode* right; // Wskaźnik na prawe dziecko (w prawo od obecnego)
    int degree; // Liczba dzieci

    FibNode(int val, int prio) : value(val), priority(prio), mark(false), parent(nullptr), child(nullptr), left(this), right(this), degree(0) {}
};

// Klasa kopca Fibonacciego
class FibonacciHeap {
private:
    FibNode* maxNode; // Wskaźnik na węzeł o maksymalnym priorytecie
    unordered_map<int, FibNode*> nodeMap; // Mapa dla szybkiego dostępu do węzłów

    // Wstawianie nowego węzła do listy korzeni
    void insertNode(FibNode* node) {
        if (!maxNode) {
            maxNode = node;
        } else {
            node->left = maxNode;
            node->right = maxNode->right;
            maxNode->right->left = node;
            maxNode->right = node;
            if (node->priority > maxNode->priority) {
                maxNode = node;
            }
        }
    }

    // Łączenie dwóch kopców Fibonacciego
    void mergeHeaps(FibonacciHeap& otherHeap) {
        if (!otherHeap.maxNode) return;
        if (!maxNode) {
            maxNode = otherHeap.maxNode;
        } else {
            FibNode* temp = maxNode->right;
            maxNode->right = otherHeap.maxNode->right;
            otherHeap.maxNode->right->left = maxNode;
            otherHeap.maxNode->right = temp;
            temp->left = otherHeap.maxNode;
            if (otherHeap.maxNode->priority > maxNode->priority) {
                maxNode = otherHeap.maxNode;
            }
        }
    }

    // Łączenie dwóch węzłów
    FibNode* mergeNodes(FibNode* node1, FibNode* node2) {
        if (!node1) return node2;
        if (!node2) return node1;
        if (node1->priority < node2->priority) {
            FibNode* temp = node1;
            node1 = node2;
            node2 = temp;
        }
        FibNode* node1Right = node1->right;
        node1->right = node2->right;
        node2->right->left = node1;
        node2->right = node1Right;
        node1Right->left = node2;
        if (node2->priority > node1->priority) {
            return node2;
        }
        return node1;
    }

    // Przywrócenie własności kopca Fibonacciego po usunięciu węzła
    void consolidate() {
        if (!maxNode) return;

        vector<FibNode*> degreeTable(100, nullptr); // Tabela stopni węzłów
        vector<FibNode*> roots; // Lista korzeni po przejściu po wszystkich węzłach

        FibNode* current = maxNode;
        do {
            roots.push_back(current);
            current = current->right;
        } while (current != maxNode);

        for (FibNode* root : roots) {
            FibNode* x = root;
            int d = x->degree;
            while (degreeTable[d] != nullptr) {
                FibNode* y = degreeTable[d];
                if (x->priority < y->priority) {
                    FibNode* temp = x;
                    x = y;
                    y = temp;
                }
                link(y, x);
                degreeTable[d] = nullptr;
                d++;
            }
            degreeTable[d] = x;
        }

        maxNode = nullptr;
        for (FibNode* root : roots) {
            if (!maxNode || root->priority > maxNode->priority) {
                maxNode = root;
            }
        }
    }

    // Połączenie dwóch węzłów, jeden staje się dzieckiem drugiego
    void link(FibNode* child, FibNode* parent) {
        child->left->right = child->right;
        child->right->left = child->left;

        child->parent = parent;
        if (!parent->child) {
            parent->child = child;
            child->left = child;
            child->right = child;
        } else {
            child->left = parent->child;
            child->right = parent->child->right;
            parent->child->right->left = child;
            parent->child->right = child;
        }
        parent->degree++;
        child->mark = false;
    }

public:
    FibonacciHeap() : maxNode(nullptr) {}

    // Wstawianie elementu z określonym priorytetem do kopca Fibonacciego
    void insert(int value, int priority) {
        FibNode* node = new FibNode(value, priority);
        insertNode(node);
        nodeMap[value] = node;
    }

    // Usunięcie i zwrócenie elementu o największym priorytecie
    int extractMax() {
        if (!maxNode) return -1;

        FibNode* max = maxNode;
        int value = max->value;

        // Usuń maxa z listy korzeni
        if (max->left == max) {
            maxNode = nullptr;
        } else {
            max->left->right = max->right;
            max->right->left = max->left;
            maxNode = max->right;
        }

        // Przywróć własności kopca
        if (max->child) {
            FibNode* child = max->child;
            do {
                FibNode* temp = child->right;
                insertNode(child);
                child->parent = nullptr;
                child = temp;
            } while (child != max->child);
        }

        delete max;
        nodeMap.erase(value);
        consolidate();

        return value;
    }

    // Zwrócenie (podejrzenie) elementu o największym priorytecie
    int peek() {
        if (!maxNode) return -1;
        return maxNode->value;
    }

// Zmiana priorytetu elementu
    void modifyKey(int value, int newPriority) {
        if(nodeMap.find(value) == nodeMap.end()) {
            cout << "Error: Value not found in the heap." << endl;
            return;
        }

        FibNode* node = nodeMap[value];
        if (newPriority < node->priority) {
            decreaseKey(node, newPriority);
        } else if (newPriority > node->priority) {
            increaseKey(node, newPriority);
        }
    }

// Zmniejszenie priorytetu elementu
    void decreaseKey(FibNode* node, int newPriority) {
        node->priority = newPriority;
        FibNode* parent = node->parent;
        if (parent && node->priority < parent->priority) {
            cut(node, parent);
            cascadingCut(parent);
        }
        if (node->priority > maxNode->priority) {
            maxNode = node;
        }
    }

// Przywrócenie własności kopca po usunięciu węzła
    void cut(FibNode* node, FibNode* parent) {
        if (node == node->right) {
            parent->child = nullptr;
        } else {
            node->left->right = node->right;
            node->right->left = node->left;
            if (parent->child == node) {
                parent->child = node->right;
            }
        }
        parent->degree--;

        node->left = node;
        node->right = node;
        node->parent = nullptr;
        node->mark = false;

        insertNode(node);
    }

    // Wywołanie cut dla rodzica, jeśli węzeł stracił więcej niż jedno dziecko
    void cascadingCut(FibNode* node) {
        FibNode* parent = node->parent;
        if (parent) {
            if (!node->mark) {
                node->mark = true;
            } else {
                cut(node, parent);
                cascadingCut(parent);
            }
        }
    }

    // Zwiększenie priorytetu elementu
    void increaseKey(FibNode* node, int newPriority) {
        if (node->priority < newPriority) {
            node->priority = newPriority;
            FibNode* parent = node->parent;
            if (parent && node->priority > parent->priority) {
                cut(node, parent);
                cascadingCut(parent);
            }
            if (node->priority > maxNode->priority) {
                maxNode = node;
            }
        }
    }

    // Zwrócenie rozmiaru kopca Fibonacciego
    int returnSize() {
        if (!maxNode) return 0;
        int size = 0;
        vector<FibNode*> nodes; // Lista węzłów do zbadania

        FibNode* current = maxNode;
        do {
            nodes.push_back(current);
            current = current->right;
            size++;
        } while (current != maxNode);

        for (FibNode* node : nodes) {
            size += node->degree;
        }

        return size;
    }
};

//int main() {
//    // Przykładowe użycie kolejki priorytetowej typu MAX opartej na kopcu Fibonacciego
//    FibonacciHeap maxHeap;
//
//    // Dodawanie elementów
//    maxHeap.insert(1, 20);
//    maxHeap.insert(2, 20);
//    maxHeap.insert(5, 60);
//    maxHeap.insert(4, 30);
//    cout<< maxHeap.peek() << endl;
//    cout<< maxHeap.returnSize() << endl;
//    cout<<maxHeap.extractMax() << endl;
//    cout<< maxHeap.returnSize() << endl;
//    maxHeap.modifyKey(4, 25);
//    cout<< maxHeap.returnSize() << endl;
//    maxHeap.insert(3, 6);
//    cout<< maxHeap.returnSize() << endl;
//    cout<<maxHeap.extractMax() << endl;
//    cout<<maxHeap.extractMax() << endl;
//    cout<<maxHeap.extractMax() << endl;
//    cout<<maxHeap.extractMax() << endl;
//
//    // Zwracanie rozmiaru kopca
//    cout << "Rozmiar kopca: " << maxHeap.returnSize() << endl;
//
//    return 0;
//}


#endif //PROJECT_2_PRIORITY_QUEUE_FIBONACCIHEAP_H
