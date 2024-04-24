#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

#include <iostream>
#include <utils/node.h>

template<typename T>
class PriorityQueue_Heap{
    private:
        std::vector<Pair<int>> queue;
        size_t size;

        size_t parent(size_t index){
            return (index - 1) / 2;
        }

        size_t left_child(size_t index){
            return 2*index + 1;
        }

        size_t right_child(size_t index){
            return 2*index + 2;
        }

        void swap(size_t index_1, size_t index_2){
            Pair<T> temp = queue[index_1];
            queue[index_1] = queue[index_2];
            queue[index_2] = temp;
        }

        // heap - max priority as root (max heap)
        /**
         *         (largest priority)
         *                root
         *              /      \
         *   left_child          right_child
         * 
        **/
        void make_heap(size_t index){
            size_t left = left_child(index);
            size_t right = right_child(index);
            size_t largest = index; 


            // left child has bigger priority
            if(left < size && queue[left].priority > queue[largest].priority)
                largest = left;

            // right child has bigger priority
            if(right < size && queue[right].priority > queue[largest].priority)
                largest = right;
            

            if(largest != index){
                swap(index, largest);
                make_heap(largest);
            }
        }
        
    public:
        PriorityQueue_Heap(){
            size = 0;
        }

        // insert a new value into the priority queue
        void insert(T value, size_t priority){
            // place the new Pair<T> at the end of queue
            queue.push_back(Pair<T>(value, priority));
            size++;

            // remake the heap
            size_t current_index = size - 1;
            // check if parents priority is bigger
            // if yes then move up the element
            while(current_index > 0 
                && queue[current_index].priority > queue[parent(current_index)].priority){
                    swap(current_index, parent(current_index));
                    current_index = parent(current_index);
                }
        }

        void modify_key(T value, size_t priority){
            // loop through all elements
            for(size_t i = 0; i < size; i++){
                // value was found
                if(queue[i].value == value){
                    // change priority
                    queue[i].priority = priority;

                    // remake the heap
                    // if parent has lower priority swap it with our current node 
                    // (the node we changed)
                    // this continues until we reach root (index 0) 
                    // or priority of parent is bigger
                    size_t parent_index = parent(i);
                    if(parent_index >= 0 && queue[parent_index].priority < queue[i].priority){
                        while(i > 0 && queue[parent_index].priority < queue[i].priority){
                            swap(i, parent_index);
                            i = parent_index;
                            parent_index = parent(i);
                        }
                    }else{
                        make_heap(i);
                    }
                    
                    //make_heap(i);

                    // stop the for loop
                    // we only change priority of one node
                    return;    
                }
            }
        }

        // get and remove the root
        T extract_max(){
            // yes I do love making people suffer with errors 3>
            if(size == 0)
                throw std::out_of_range("Priority queue is empty");

            // root element => max value
            T max_value = queue[0].value;

            // deleting the first element
            queue.erase(queue.begin());
            size--;

            // build heap from root
            make_heap(0);

            return max_value;
        }

        // get root, but dont remove it
        T find_max(){
            if(size == 0)
                throw std::out_of_range("Priority queue is empty");

            return queue[0].value;
        }

        // return size of queue / heap
        size_t get_size(){
            return size;
        }

        // get the queue vector
        // only used for testing
        std::vector<Pair<T>> get_values(){
            return queue;
        }



};

#endif