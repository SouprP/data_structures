#ifndef NODE_H
#define NODE_H

#include <iostream>

template<typename T>
class Pair{
    public:
        std::string key;
        T value;

        Pair(std::string key, T value){
            this->key = key;
            this->value = value;
        }
};

template<typename T>
class Node{
    public:
        T value;
        Node* next;

        Node(T value){
            this->value = value;
            next = nullptr;
        };
};


#endif