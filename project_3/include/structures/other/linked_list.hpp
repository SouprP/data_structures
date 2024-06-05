#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

#include <utils/node.hpp>

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
            size++;
            // the list is empty, just add at head and do nothing
            if(head == nullptr){
                head = new Node<T>(element);
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
                head = new Node<T>(element);
                return;
            }

            // go to the current last element
            // and insert the new element there
            Node<T>* current = head;
            while(current->next != nullptr)
                current = current->next;

            current->next = new Node<T>(element);
        };

        void add(T element, size_t index){
            // add at front
            if(index == 1){
                add_front(element);
                return;
            }

            // add at the back
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
            // get the first node and remove
            // and also make the next node head
            Node<T>* current = head->next;
            delete head;
            head = current;
            size--;
        };

        void remove_back(){
            // get the node just before our
            Node<T>* current = head;
            while(current->next->next != nullptr)
                current = current->next;

            // deleting
            delete current->next;
            current->next = nullptr;
            size--;
        }

        void remove(size_t index){
            // remove at front
            if(index == 1){
                remove_front();
                return;
            }

            // remove at the back
            if(index >= size){
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

        T* get(size_t index){
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
        }

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
        }
};

#endif