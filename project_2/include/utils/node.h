#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename T>
class Pair{
    public:
        T value;
        size_t priority;

        Pair(T value, size_t priority){
            this->value = value;
            this->priority = priority;
        }
};

template<typename T>
class Node{
    public:
        T value;
        size_t priority;
        Node* next;

        Node(T value, size_t priority){
            this->value = value;
            this->priority = priority;
            next = nullptr;
        }
};


#endif