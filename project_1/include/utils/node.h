#ifndef NODE_H
#define NODE_H

/*
class BaseNode{

};
*/
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

template<typename T>
class DoubleNode{
    public:
        T value;
        DoubleNode* prev;
        DoubleNode* next;

        DoubleNode(T value){
            this->value = value;
            prev = nullptr;
            next = nullptr;
        }
};

#endif