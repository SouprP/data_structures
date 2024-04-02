#include <iostream>
#include <utils/generator.h>
#include <utils/file.h>
//#include <utils/menu.h>
//#include <utils/visualiser.h>
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

#include <structures/array_list.h>
#include <structures/linked_list.h>
#include <structures/linked_list_tail.h>
#include <structures/double_linked_list.h>

#define DATA_SIZE_1 1000
#define DATA_SIZE_2 10000
#define DATA_SIZE_3 50000
#define DATA_SIZE_4 100000
#define DATA_SIZE_5 250000
#define DATA_SIZE_6 500000
#define DATA_SIZE_7 1000000

#define OBJECT_ADD 999

std::vector<size_t> SIZES = {DATA_SIZE_1, DATA_SIZE_2, 
    DATA_SIZE_3, DATA_SIZE_4, DATA_SIZE_5, DATA_SIZE_6, DATA_SIZE_7};

int main(int argc, char* argv[]){
    TimeVar start;
    TimeVar end;

    Generator* gen;
    std::vector<int> data;
    size_t overall_time_array = 0;
    size_t overall_time_list = 0;
    size_t overall_time_tail = 0;
    size_t overall_time_double = 0;

    //size_t data_size = DATA_SIZE_3;

    // 10 times
    for(auto data_size : SIZES){
        std::cout << data_size << std::endl << std::endl;

        //size_t pivot = 0;
        size_t pivot = 3 * data_size / 4;

        for(int i = 0; i < 10; i++){
            gen = new Generator();
            data = gen->generate_int(data_size);

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_back(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }
            //std::cout << "d_" << i << std::endl;
                
            //uint8_t obj_to_find = data[pivot];
            uint16_t obj_to_find = 999;
            //array.remove_back();
            //list.remove_back();
            //list_tail.remove_back();
            //d_list.remove_back();

            //array.add(999, pivot);
            //list.add(999, pivot);
            //list_tail.add(999, pivot);
            //d_list.add(999, pivot);
            //std::cout << "Found?  " << array.search(obj_to_find) << std::endl;

            start = timeNow();
            //array.add_front(OBJECT_ADD);
            //array.remove_front();
            array.add_back(OBJECT_ADD);
            //array.remove_back();
            //array.add(OBJECT_ADD, pivot);
            //array.remove(pivot);
            //array.get(pivot);
            //array.search(obj_to_find);
            end = timeNow();
            overall_time_array += duration(end - start);

            start = timeNow();
            //list.add_front(OBJECT_ADD);
            //list.remove_front();
            list.add_back(OBJECT_ADD);
            //list.remove_back();
            //list.add(OBJECT_ADD, pivot);
            //list.remove(pivot);
            //list.get(pivot);
            //list.search(obj_to_find);
            end = timeNow();
            overall_time_list += duration(end - start);

            start = timeNow();
            //list_tail.add_front(OBJECT_ADD);
            //list_tail.remove_front();
            list_tail.add_back(OBJECT_ADD);
            //list_tail.remove_back();
            //list_tail.add(OBJECT_ADD, pivot);
            //list_tail.remove(pivot);
            //list_tail.get(pivot);
            //list_tail.search(obj_to_find);
            end = timeNow();
            overall_time_tail += duration(end - start);

            start = timeNow();
            //d_list.add_front(OBJECT_ADD);
            //d_list.remove_front();
            d_list.add_back(OBJECT_ADD);
            //d_list.remove_back();
            //d_list.add(OBJECT_ADD, pivot);
            //d_list.remove(pivot);
            //d_list.get(pivot);
            //d_list.search(obj_to_find);
            end = timeNow();
            overall_time_double += duration(end - start);

        }
        std::cout << "Arrray    :  " << overall_time_array / 10 << "ns" << std::endl;
        std::cout << "LinkedList:  " << overall_time_list / 10 << "ns" << std::endl;
        std::cout << "LInkedTail:  " << overall_time_tail / 10 << "ns" << std::endl;
        std::cout << "DoubleList:  " << overall_time_double / 10 << "ns" << std::endl;
        std::cout << std::endl;
    }

        
    

}