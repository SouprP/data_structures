#ifndef PRIORITY_QUEUE_LINKED_LIST_H
#define PRIORITY_QUEUE_LINKED_lIST_H

#include <iostream>
#include <utils/node.h>

template<typename T>
class PriorityQueue_LinkedList{
    private:
        Node<T>* head;
        size_t size;

        
        
    public:
        PriorityQueue_LinkedList(){
            head = nullptr;
            size = 0;
        }

        // loops through all nodes (unless empty) and deletes them
        ~PriorityQueue_LinkedList(){
            Node<T>* current = head;
            while(current != nullptr){
                Node<T>* temp = current;
                current = current->next;

                // personal cleaner, how nice!
                delete temp;
            }
        }

        // insert a new value into the priority queue
        void insert(T value, size_t priority){
            // 
            if(size == 0 || head == nullptr){
                head = new Node<T>(value, priority);
                size++;
                return;
            }

            // add front
            if(head->priority < priority){
                Node<T>* temp = head;
                head = new Node<T>(value, priority);
                head->next = temp;
                size++;
                return;
            }

            // go to the point where PR is <
            Node<T>* current = head;
            while(current->next != nullptr && current->next->priority > priority)
                current = current->next;
            
            // node just before where we want to place
            Node<T>* previous = current;

            // swapping, connecting, etc
            Node<T>* temp = previous->next;
            Node<T>* new_node = new Node<T>(value, priority);
            previous->next = new_node;
            new_node->next = temp;
            size++;
        }

        void modify_key(T value, size_t priority){
            /**
             *      previous => current => next
             * 
             *      // we either get rid of current node
             *      // or let it stay where it is
             *      // depending on it's priority
             * 
             *      previous => next
            */
            Node<T>* current = head;
            Node<T>* previous = nullptr;

            while(current->value != value){
                if(current->next == nullptr)
                    return; // break out of the loop and do nothing

                previous = current;
                current = current->next;
            }

            // our node was found!
            current->priority = priority;


            // check if we need to move the node
            if(previous == nullptr)
                return; // we are at the front

            if(previous->priority > priority && current->next->priority < priority)
                return; // we are in the right place

            // move the node
            // by deleteting it and inserting it as a new node
            Node<T>* temp = current->next;
            previous->next = temp;
            delete current;

            insert(value, priority);
        }

        // get and remove the root
        T extract_max(){
            // yes I do love making people suffer with errors 3>
            if(size == 0)
                throw std::out_of_range("Priority queue is empty");

            // root element => max value
            T max_value = head->value;

            // deleting the first element 
            // and swapping / connecting
            Node<T>* temp = head->next;
            delete head;
            head = temp;
            size--;


            return max_value;
        }

        // get root, but dont remove it
        T find_max(){
            if(size == 0)
                throw std::out_of_range("Priority queue is empty");

            return head->value;
        }

        // return size of queue
        size_t get_size(){
            return size;
        }

        // get the queue vector
        // only used for testing
        std::vector<Node<T>> get_values(){
            // get all values and push them into a vector
            Node<T>* current = head;
            std::vector<Node<T>> temp;
            while(current != nullptr){
                temp.push_back(*current);
                current = current->next;
            }
            return temp;
        }

};

#endif