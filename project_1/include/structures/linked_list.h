#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <utils/node.h>

template<typename T>
class LinkedList{
    private:
        Node<T>* head;
        size_t size;
    
    public:
        LinkedList(){
            head = nullptr;
            size = 0;
        };

        // loops through all nodes (unless empty) and deletes them
        ~LinkedList(){
            Node<T>* current = head;
            while(current != nullptr){
                Node<T>* temp = current;
                current = current->next;

                // personal cleaner, how nice!
                delete temp;
            }
        };

        void add_front(T element){
            if(head == nullptr){
                head = new Node<T>(element);
                return;
            }

            Node<T>* current = new Node<T>(element);
            current->next = head;
            head = current;
            size++;
        };

        void add_back(T element){
            size++;
            if(head == nullptr){
                head = new Node<T>(element);
                return;
            }

            Node<T>* current = head;
            while(current->next != nullptr)
                current = current->next;

            current->next = new Node<T>(element);
        };

        void add(T element, size_t index){
            if(index == 1){
                add_front(element);
                return;
            }

            if(index >= size + 1){
                add_back(element);
                return;
            }

            // gets the node that just before where we want to insert a new node
            size_t i = 1;
            Node<T>* previous = head->next;
            while(i < index - 2){
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
            size--;
        }

        void remove(size_t index){
            if(index == 1){
                remove_front();
                return;
            }

            if(index >= size + 1){
                remove_back();
                return;
            }

            // gets the node that just before where we want to insert a new node
            size_t i = 1;
            Node<T>* previous = head->next;
            while(i < index - 2){
                previous = previous->next;
                i++;
            }

            // swapping, connecting, etc
            Node<T>* node_to_del = previous->next;
            Node<T>* temp = node_to_del->next;
            delete node_to_del;
            previous->next = temp; 
            
            size--;
        }

        // returns pointer to value
        // returning NULL is better than returning
        T* get(size_t index){
            Node<T>* current = head;
            for(size_t i = 0; i < index - 1; i++){
                if(current == nullptr)
                    return NULL;

                current = current->next;
            }

            if(current == nullptr)
                return NULL;
            
            return &current->value;
        }

        std::vector<T> get_values(){
            Node<T>* current = head;
            std::vector<T> temp;
            while(current != nullptr){
                temp.push_back(current->value);
                current = current->next;
            }
            return temp;
        }
};

#endif