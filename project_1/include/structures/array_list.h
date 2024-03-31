#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <iostream>

template<typename T>
class ArrayList{
    private:
        T* arr;
        size_t capacity;
        size_t size;

    public:
        ArrayList(){
            capacity = 10;
            arr = new T[capacity];
            size = 0;
        };

        ~ArrayList(){
            delete[] arr;
        };

        void add_front(T element){
            if(size == 0){
                arr[0] = element;
                size++;
                return;
            }

            if(size == capacity)
                capacity *= 2;

            // increase capacity
            T* temp_arr = new T[capacity];

            // copy elements, but move them one place forward
            for(size_t i = 0; i < size; i++)
                temp_arr[i + 1] = arr[i];
                
            delete[] arr;
            arr = temp_arr;

            arr[0] = element;
            size++;


        };

        // add at the end of the array
        void add_back(T element){
            // check if array is full
            if(size == capacity){
                // increase capacity
                capacity *= 2;
                T* temp_arr = new T[capacity];

                // copy elements
                for(size_t i = 0; i < size; i++)
                    temp_arr[i] = arr[i];

                // delete old contents of arr and copy new values from temp_arr
                delete[] arr;
                arr = temp_arr;
            }

            // add element at the end
            arr[size] = element;
            size++;
        };

        void add(T element, size_t index){
            if(index >= size)
                return;

            if(size == capacity)
                capacity *= 2;

            if(index == 0){
                add_front(element);
                return;
            }

            if(index >= size){
                add_back(element);
                return;
            }

             // if it doesnt need to be at the end
             // or at the front
             T* temp_arr = new T[capacity];

             for(int i = 0; i < index; i ++)
                temp_arr[i] = arr[i];

            temp_arr[index] = element;

            for(int i = index + 1; i < size; i++)
                temp_arr[i] = arr[i];

            delete[] arr;
            arr = temp_arr;
            size++;
        };

        void remove_front(){
            T* temp_arr = new T[capacity];

            // copy all elements, excepet the first one
            // moves them one place back
            for(size_t i = 1; i < size; i++)
                temp_arr[i - 1] = arr[i];

            delete[] arr;
            arr = temp_arr;

            size--;
        }

        void remove_back(){
            // just decreasse the size
            // the amount of bytes the array uses is still the same
            size--;
        }

        // remove at provided index
        void remove(size_t index){
            if(index >= size)
                return;

            // move all the elements after the element we removed one place back
            for(size_t i = index; i < size - 1; i++)
                arr[i] = arr[i + 1];

            
            // there is no need to remove the last element
            // we can just decrease the size
            // byte size of the array is still the same
            // whether we remove it or not
            size--;
        };

        // does it really need an explanation?
        T get(size_t index){
            if(index >= size)
                return -1;

            return arr[index];
        };

        
        // functions for utility calls
        size_t get_size(){
            return size;
        };

        T* get_arr(){
            return arr;
        };


};

#endif