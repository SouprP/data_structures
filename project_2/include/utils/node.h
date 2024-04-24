#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename T>
class Node{
    public:
        T value;
        size_t priority;

        Node(T value, size_t priority){
            this->value = value;
            this->priority = priority;
        }
};


#endif