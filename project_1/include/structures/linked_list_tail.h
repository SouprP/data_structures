#ifndef LINKED_LIST_TAIL_H
#define LINKED_LIST_TAIL_H

#include <iostream>
#include <utils/node.h>

template<typename T>
class LinkedListTail{
    private:
        Node<T>* head;
        Node<T>* tail;
        size_t size;

    public:
        LinkedListTail(){
            head= nullptr;
            tail = nullptr;
            size = 0;
        };

        ~LinkedListTail(){
            Node<T>* current = head;
            while(current != nullptr){
                Node<T>* temp = current;
                current = current->next;

                // personal cleaner, how nice!
                delete temp;
            }
        }

        void add_front(T element){
            size++;

            // the list is empty, just add at head and do nothing
            if(head == nullptr){
                Node<T>* new_node = new Node<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            // get the current head element
            // move it one place forward
            Node<T>* current = new Node<T>(element);
            current->next = head;
            head = current;
        };

        void add_back(T element){
            size++;

            // add at front
            if(head == nullptr){
                Node<T>* new_node = new Node<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            // get the tail and add the new element there
            Node<T>* new_node = new Node<T>(element);
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

            // gets the node that just before where we want to insert a new node
            size_t i = 1;
            Node<T>* previous = head;
            while(i < index - 1){
                previous = previous->next;
                i++;
            }

            // swapping, connecting, etc
            Node<T>* temp = previous->next;
            Node<T>* new_node = new Node<T>(element);
            previous->next = new_node;
            new_node->next = temp;
            size++;
        };

        void remove_front(){
            // get the first node and remove
            // and also make the next node head
            Node<T>* current = head->next;
            delete head;
            head = current;
            size--;
        };

        void remove_back(){
            // get the node just before tail
            Node<T>* current = head;
            while(current->next->next != nullptr)
                current = current->next;

            // swapping and deletion
            delete current->next;
            current->next = nullptr;
            tail = current;
            size--;
        };

        void remove(size_t index){
            // remove at the front
            if(index == 1){
                remove_front();
                return;
            }

            // remove at the back
            if(index >= size - 1){
                remove_back();
                return;
            }

            // gets the node that just before where we want to insert a new node
            size_t i = 0;
            Node<T>* previous = head;;
            while(i < index - 3){
                previous = previous->next;
                i++;
            }

            // swapping, connecting, etc
            Node<T>* node_to_del = previous->next;
            Node<T>* temp = node_to_del->next;
            delete node_to_del;
            previous->next = temp; 
            
            size--;
        };

        // returns pointer to value
        // returning NULL is better than returning
        // -1 which might throw an exception
        T* get(size_t index){
            if(index == size)
                return get_tail();

            // go to the provided index
            // and get the value
            Node<T>* current = head;
            for(size_t i = 0; i < index - 1; i++){
                if(current == nullptr)
                    return NULL;

                current = current->next;
            }

            if(current == nullptr)
                return NULL;
            
            return &current->value;
        };

        bool search(T element){
            // go through all elements
            Node<T>* current = head;
            while(current != nullptr){
                if(current->value == element)
                    return true;

                current = current->next;
            }
            return false;
        }

        std::vector<T> get_values(){
            // get all values and push them into a vector
            Node<T>* current = head;
            std::vector<T> temp;
            while(current != nullptr){
                temp.push_back(current->value);
                current = current->next;
            }
            return temp;
        };

        T* get_tail(){
            return &tail->value;
        }
};


#endif