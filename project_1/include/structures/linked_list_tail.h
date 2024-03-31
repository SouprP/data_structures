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
            if(head == nullptr){
                Node<T>* new_node = new Node<T>(element);
                head = new_node;
                tail = new_node;
                //std::cout << "Tail: " 
                //<< tail->value << std::endl;
                return;
            }

            Node<T>* current = new Node<T>(element);
            current->next = head;
            head = current;
        };

        void add_back(T element){
            size++;
            if(head == nullptr){
                Node<T>* new_node = new Node<T>(element);
                head = new_node;
                tail = new_node;
                return;
            }

            Node<T>* current = head;
            while(current->next != nullptr)
                current = current->next;

            Node<T>* new_node = new Node<T>(element);
            current->next = new_node;
            tail = new_node;
            //std::cout << "Tail: " 
                //<< tail->value << std::endl;
        };

        void add(T element, size_t index){
            if(index == 1){
                add_front(element);
                std::cout << "front add" << std::endl;
                return;
            }

            if(index > size){
                add_back(element);
                std::cout << "back add" << std::endl;
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
            Node<T>* current = head->next;
            delete head;
            head = current;
            size--;
        };

        void remove_back(){
            Node<T>* current = head;
            while(current->next->next != nullptr)
                current = current->next;

            delete current->next;
            current->next = nullptr;
            tail = current;
            size--;
        };

        void remove(size_t index){
            if(index == 1){
                remove_front();
                return;
            }

            if(index >= size - 1){
                remove_back();
                return;
            }

            // gets the node that just before where we want to insert a new node
            size_t i = 0;
            Node<T>* previous = head->next;
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
        // a random fucking -1 which might throw an exception
        T* get(size_t index){
            Node<T>* current = head;
            for(size_t i = 0; i <= index; i++){
                if(current == nullptr)
                    return NULL;

                current = current->next;
            }

            if(current == nullptr)
                return NULL;
            
            return &current->value;
        };

        std::vector<T> get_values(){
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