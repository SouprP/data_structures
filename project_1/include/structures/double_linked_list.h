#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <iostream>
#include <utils/node.h>

template<typename T>
class DoubleLinkedList{
    private:
        DoubleNode<T>* head;
        DoubleNode<T>* tail;
        size_t size;

    public:
        DoubleLinkedList(){
            head = nullptr;
            tail == nullptr;
            size = 0;
        };

        ~DoubleLinkedList(){
            DoubleNode<T>* current = head;
            while(current != nullptr){
                DoubleNode<T>* temp = current;
                current = current->next;
                delete temp;
            }
        }

        void add_front(T element){
            size++;
            if(head == nullptr){
                DoubleNode<T>* new_node = new DoubleNode<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            DoubleNode<T>* new_node = new DoubleNode<T>(element);
            new_node->next = head;
            head = new_node;
        };

        void add_back(T element){
            size++;
            if(head == nullptr){
                DoubleNode<T>* new_node = new DoubleNode<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            DoubleNode<T>* new_node = new DoubleNode<T>(element);
            tail->next = new_node;
        };

        // fix some things
        void add(T element, size_t index){
            if(index == 1){
                add_front(element);
                return;
            }

            if(index > size){
                add_back(element);
                return;
            }

            size++;
            // check if going from the back is better
            size_t pivot = size / 2;
            if(index <= pivot){
                size_t i = 1;
                //DoubleNode<T>* previous = head->next;
                DoubleNode<T>* previous = head;
                while(i < index - 1){
                    previous = previous->next;
                    i++;
                }
                //std::cout << previous->value << std::endl;
                DoubleNode<T>* temp = previous->next;
                DoubleNode<T>* new_node = new DoubleNode<T>(element);
                previous->next = new_node;
                new_node->next = temp;
                return;
            }

            // go from back
            size_t i = size;
            DoubleNode<T>* previous = tail;
            while(i > index + 1){
                previous = previous->prev;
                i--;
            }

            std::cout << "the node just one: " << previous->value;
            

        }

        void remove_front(){
            if(head == nullptr)
                return;

            DoubleNode<T>* next_node = head->next;
            delete head;
            head = next_node;
            size--;
        };

        void remove_back(){
            if(tail == nullptr)
                return;

            DoubleNode<T>* prev_node = tail->prev;
            prev_node->next = nullptr;
            delete tail;
            tail = prev_node;
            size--;
        };

        // add things
        void remove(size_t index){
            if(index == 1){
                remove_front();
                return;
            }

            if(index >= size - 1){
                remove_back();
                return;
            }

            // get middle index
            size_t pivot = size / 2;
            if(index <= pivot){
                // go from front
            }

            if(index > pivot){
                // go from back
            }
        };

        T* get(size_t index); // functions for going from back to mid / from front to mid
        std::vector<T> get_values(){
            DoubleNode<T>* current = head;
            std::vector<T> temp;
            while(current != nullptr){
                temp.push_back(current->value);
                current = current->next;
            }
            return temp;
        }
};

#endif