//
// Created by Gaming PC on 14.05.2024.
//

#ifndef PROJECT_2_PRIORITY_QUEUE_FIBONACCIHEAP_H
#define PROJECT_2_PRIORITY_QUEUE_FIBONACCIHEAP_H

#include <cmath>
#include <iostream>

using namespace std;

// Node creation
struct node {
    int priority;
    int value;
    int degree;
    node *parent;
    node *child;
    node *left;
    node *right;
    bool mark;
    node(int val, int prio) : value(val), priority(prio), mark(false), parent(nullptr), child(nullptr), left(this), right(this), degree(0) {};
};

// Implementation of Fibonacci heap
class FibonacciHeap {
private:
    int nH;
    node *H;

    void consolidate();
    void cut(node* x, node* y);
    void cascadingCut(node* y);
    static void link(node* y, node* x);
    void deleteAll(node* n) {
        if (n != nullptr) {
            node* x = n;
            do {
                node* d = x->right;
                deleteAll(x->child);
                delete x;
                x = d;
            } while (x != n);
        }
    }

public:
    FibonacciHeap();
    ~FibonacciHeap();
    node* insert(int priority , int value);
    int extractMax();
    node* findMax();
    void increaseKey(node* x, int newpriority);
    void decreaseKey(node* x, int newpriority);
    void modifyKey(int value, int newpriority);
    //void deleteKey(node* x);
    int getSize(){return nH;};

    static void display(node* H);
    node* find(node* H, int value);
};

// Initialize heap
FibonacciHeap::FibonacciHeap() {
    H = nullptr;
    nH = 0;
}

// Destructor
FibonacciHeap::~FibonacciHeap() {
    deleteAll(H);
}

// Create and insert node
node* FibonacciHeap::insert(int priority, int value) {
    node* x = new node(value,priority);

    if (H != nullptr) {
        H->left->right = x;
        x->right = H;
        x->left = H->left;
        H->left = x;
        if (x->priority > H->priority)
            H = x;
    } else {
        H = x;
        x->left = x;
        x->right = x;
    }
    nH++;
    return x;
}

// Extract max
int FibonacciHeap::extractMax() {
    node* z = H;
    int value = z->value;
    if (z != nullptr) {
        node* x = z->child;
        if (x != nullptr) {
            do {
                node* next = x->right;
                H->left->right = x;
                x->right = H;
                x->left = H->left;
                H->left = x;
                x->parent = nullptr;
                x = next;
            } while (x != z->child);
        }

        z->left->right = z->right;
        z->right->left = z->left;

        if (z == z->right) {
            H = nullptr;
        } else {
            H = z->right;
            consolidate();
        }
        nH--;
    }
    delete z;
    return value;
}

// Delete a priority
//void FibonacciHeap::deleteKey(node* x) {
//    increaseKey(x, INT_MAX);
//    node* max = extractMax();
//    if (max != nullptr) {
//        delete max;
//    }
//}

// Find max
node* FibonacciHeap::findMax() {
    return H;
}

// Consolidate the heap
void FibonacciHeap::consolidate() {
    int D = static_cast<int>(log2(nH)) + 1;
    node* A[D];
    for (int i = 0; i < D; i++) {
        A[i] = nullptr;
    }

    node* w = H;
    int rootListSize = 0;
    if (w != nullptr) {
        rootListSize++;
        for (node* x = w->right; x != w; x = x->right) {
            rootListSize++;
        }
    }

    while (rootListSize > 0) {
        int d = w->degree;
        node* x = w;
        node* next = w->right;
        while (A[d] != nullptr) {
            node* y = A[d];
            if (x->priority < y->priority) {
                swap(x, y);
            }
            link(y, x);
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
        w = next;
        rootListSize--;
    }

    H = nullptr;
    for (int i = 0; i < D; i++) {
        if (A[i] != nullptr) {
            if (H == nullptr) {
                H = A[i];
                H->left = H;
                H->right = H;
            } else {
                H->left->right = A[i];
                A[i]->right = H;
                A[i]->left = H->left;
                H->left = A[i];
                if (A[i]->priority > H->priority) {
                    H = A[i];
                }
            }
        }
    }
}

// Link two nodes
void FibonacciHeap::link(node* y, node* x) {
    y->left->right = y->right;
    y->right->left = y->left;

    y->parent = x;
    if (x->child == nullptr) {
        x->child = y;
        y->right = y;
        y->left = y;
    } else {
        x->child->left->right = y;
        y->right = x->child;
        y->left = x->child->left;
        x->child->left = y;
    }
    x->degree++;
    y->mark = false;
}

// Increase priority
void FibonacciHeap::increaseKey(node* x, int newpriority) {
    if (newpriority < x->priority) {
        cout << "New priority is smaller than current priority" << endl;
        return;
    }
    x->priority = newpriority;
    node* y = x->parent;
    if (y != nullptr && x->priority > y->priority) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->priority > H->priority) {
        H = x;
    }
}
// Decrease priority
void FibonacciHeap::decreaseKey(node* x, int newpriority) {
    if (newpriority > x->priority) {
        cout << "New priority is larger than current priority" << endl;
        return;
    }
    x->priority = newpriority;
    node* y = x->parent;
    if (y != nullptr && x->priority < y->priority) {
        cut(x, y);
        cascadingCut(y);
    }
}

void FibonacciHeap::modifyKey(int value, int newpriority) {
    node* x = find(H, value);
    if( x !=nullptr) {
        if (newpriority > x->priority) {
            increaseKey(x, newpriority);
        } else if (newpriority < x->priority) {
            decreaseKey(x, newpriority);
        } else {
            cout << "New priority is the same as current priority" << endl;
        }
    } else cout << "Error: Value not found in the heap." << endl;
}

// Cut a node
void FibonacciHeap::cut(node* x, node* y) {
    if (x->right == x) {
        y->child = nullptr;
    } else {
        x->right->left = x->left;
        x->left->right = x->right;
        if (y->child == x) {
            y->child = x->right;
        }
    }
    y->degree--;
    x->parent = nullptr;
    x->left = H->left;
    x->right = H;
    H->left->right = x;
    H->left = x;
    x->mark = false;
}

// Cascading cut
void FibonacciHeap::cascadingCut(node* y) {
    node* z = y->parent;
    if (z != nullptr) {
        if (!y->mark) {
            y->mark = true;
        } else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

// Get size
//int FibonacciHeap::getSize() {
//    return nH;
//}

// Display the heap
void FibonacciHeap::display(node* H) {
    node* p = H;
    if (p == nullptr) {
        cout << "Empty Heap" << endl;
        return;
    }
    cout << "Root Nodes: ";
    do {
        cout << p->priority;
        p = p->right;
        if (p != H) {
            cout << " -> ";
        }
    } while (p != H && p->right != nullptr);
    cout << endl;
}

// Find a node by value
node* FibonacciHeap::find(node* H, int value) {
    node* x = H;
    if (x == nullptr) return nullptr;
    do {
        if (x->value == value) {
            return x;
        }
        node* found = find(x->child, value);
        if (found) return found;
        x = x->right;
    } while (x != H);
    return nullptr;
}

//int main() {
//    FibonacciHeap fh;
//
//    fh.insert(7,7);
//    fh.insert(3, 3);
//    fh.insert(17, 17);
//    fh.insert(24, 24);
//
//    fh.display(fh.findMax());
//
//    int maxNode = fh.extractMax();
//    if (maxNode != -1) {
//        cout << "The node with maximum priority: " << maxNode << endl;
//    } else {
//        cout << "Heap is empty" << endl;
//    }
//    fh.insert(6,6);
//
//    fh.modifyKey(7, 2);
//    maxNode = fh.extractMax();
//    cout<<fh.getSize()<<endl;
//    if (maxNode != -1) {
//        cout << "The node with maximum priority: " << maxNode << endl;
//    } else cout << "Heap is empty" << endl;
//    maxNode = fh.extractMax();
//    if (maxNode != -1) {
//        cout << "The node with maximum priority: " << maxNode << endl;
//    } else cout << "Heap is empty" << endl;
//    maxNode = fh.extractMax();
//    if (maxNode != -1) {
//        cout << "The node with maximum priority: " << maxNode << endl;
//    } else cout << "Heap is empty" << endl;
//    cout<< fh.extractMax() << endl;
//
//    fh.display(fh.findMax());
//
//    return 0;
//}


#endif //PROJECT_2_PRIORITY_QUEUE_FIBONACCIHEAP_H
