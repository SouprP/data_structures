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
            head->prev = new_node;
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
            //new_node->prev = tail;
            //tail->next = new_node;
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;

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
            //size++;
            // check if going from the back is better
            size_t pivot = size / 2;
            if(index <= pivot){
                size_t i = 1;
                //DoubleNode<T>* previous = head->next;
                DoubleNode<T>* previous = head;
                while(i < index - 3){
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
            // get the node just before
            // if the index is 7 we get node with index 6
            while(i > index - 1){
                previous = previous->prev;
                i--;
            }

            DoubleNode<T>* new_node = new DoubleNode<T>(element);
            DoubleNode<T>* temp = previous->next;
            previous->next = new_node;
            temp->prev = new_node;
            new_node->prev = previous;
            new_node->next = temp;

            //std::cout << "the node just one: " << previous->value;
            //std::cout << std::endl;

            //std::cout << "size: " << i << std::endl;
            

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
                size_t i = 0;
                DoubleNode<T>* previous = head;
                while(i < index - 2){
                    previous = previous->next;
                    i++;
                }

                DoubleNode<T>* node_to_del = previous->next;
                DoubleNode<T>* temp = node_to_del->next;
                delete node_to_del;
                previous->next = temp;
            }

            if(index > pivot){
                size_t i = size;
                DoubleNode<T>* previous = tail;
                
                while(i > index - 1){
                    previous = previous->prev;
                    i--;
                }

                DoubleNode<T>* node_to_del = previous->next;
                DoubleNode<T>* temp = node_to_del->next;

                previous->next = temp;
                temp->prev = previous;
                delete node_to_del;
            }
        };

        T* get(size_t index){
            if(index == 1)
                return &head->value;
            

            if(index >= size - 1)
                return &tail->value;

            // get middle index
            size_t pivot = size / 2;
            if(index <= pivot){
                // go from front
                size_t i = 0;
                DoubleNode<T>* previous = head;
                while(i < index - 2){
                    previous = previous->next;
                    i++;
                }

                return &previous->next->value;
            }

            if(index > pivot){
                size_t i = size;
                DoubleNode<T>* previous = tail;
                
                while(i > index - 1){
                    previous = previous->prev;
                    i--;
                }

                return &previous->next->value;
            }
            
            return NULL;
        }; // functions for going from back to mid / from front to mid

        bool search(T element){
            DoubleNode<T>* current = head;
            while(current != nullptr){
                if(current->value == element)
                    return true;

                current = current->next;
            }
            return false;
        };
        
        std::vector<T> get_values(){
            DoubleNode<T>* current = head;
            std::vector<T> temp;
            while(current != nullptr){
                temp.push_back(current->value);
                current = current->next;
            }
            return temp;
        }

        T* get_tail(){
            return &tail->value;
        }
};

#endif