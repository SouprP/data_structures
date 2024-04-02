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

            // delete all elements
            while(current != nullptr){
                DoubleNode<T>* temp = current;
                current = current->next;
                delete temp;
            }
        }

        void add_front(T element){
            size++;

            // the list is empty, just add at head and do nothing
            if(head == nullptr){
                DoubleNode<T>* new_node = new DoubleNode<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            // get the current head element
            // move it one place forward
            DoubleNode<T>* new_node = new DoubleNode<T>(element);
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        };

        void add_back(T element){
            size++;

            // add at front
            if(head == nullptr){
                DoubleNode<T>* new_node = new DoubleNode<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            // get the tail and add the new element there
            DoubleNode<T>* new_node = new DoubleNode<T>(element);
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;

        };

        void add(T element, size_t index){
            // add at front
            if(index == 1){
                add_front(element);
                return;
            }

            // add at the back
            if(index > size){
                add_back(element);
                return;
            }
            //size++;
            // check if going from the back is better
            size_t pivot = size / 2;
            if(index <= pivot){
                size_t i = 1;

                // get the node just before
                DoubleNode<T>* previous = head;
                while(i < index - 3){
                    previous = previous->next;
                    i++;
                }

                // insert a new node
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

            // insert a new node
            DoubleNode<T>* new_node = new DoubleNode<T>(element);
            DoubleNode<T>* temp = previous->next;
            previous->next = new_node;
            temp->prev = new_node;
            new_node->prev = previous;
            new_node->next = temp;
        }

        void remove_front(){
            // no need to delete anything
            if(head == nullptr)
                return;

            // delete the first node
            // and make the next node head
            DoubleNode<T>* next_node = head->next;
            delete head;
            head = next_node;
            size--;
        };

        void remove_back(){
            // no need to delete anything
            if(tail == nullptr)
                return;

            // delete the flaast node
            // and make the previous node head
            DoubleNode<T>* prev_node = tail->prev;
            prev_node->next = nullptr;
            delete tail;
            tail = prev_node;
            size--;
        };

        void remove(size_t index){
            // remove at front
            if(index == 1){
                remove_front();
                return;
            }

            // remove at the back
            if(index >= size - 1){
                remove_back();
                return;
            }

            // get middle index
            // and check if its better go from the back
            // or the front
            size_t pivot = size / 2;
            if(index <= pivot){
                // go from front
                size_t i = 0;

                // get the node just before our
                DoubleNode<T>* previous = head;
                while(i < index - 2){
                    previous = previous->next;
                    i++;
                }

                // deletion and swapping
                DoubleNode<T>* node_to_del = previous->next;
                DoubleNode<T>* temp = node_to_del->next;
                delete node_to_del;
                previous->next = temp;
            }

            if(index > pivot){
                size_t i = size;
                DoubleNode<T>* previous = tail;
                
                // get the node just before
                while(i > index - 1){
                    previous = previous->prev;
                    i--;
                }

                // deletion and swapping
                DoubleNode<T>* node_to_del = previous->next;
                DoubleNode<T>* temp = node_to_del->next;

                previous->next = temp;
                temp->prev = previous;
                delete node_to_del;
            }
        };

        T* get(size_t index){
            // head node
            if(index == 1)
                return &head->value;
            
            // tail node
            if(index >= size - 1)
                return &tail->value;

            // get middle index
            // and check if its better go from the back
            // or the front
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
        }; 

        bool search(T element){
            // go through all elements
            DoubleNode<T>* current = head;
            while(current != nullptr){
                if(current->value == element)
                    return true;

                current = current->next;
            }
            return false;
        };
        
        std::vector<T> get_values(){
            // get all values and push them into a vector
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