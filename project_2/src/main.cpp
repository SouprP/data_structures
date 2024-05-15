#include <iostream>
#include <utils/generator.h>
#include <chrono>

#include <structures/priority_queue_heap.h>
#include <structures/priority_queue_list.h>
#include <structures/priority_queue_fibonacciheap.h>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()


#define DATA_SIZE_1 1000
#define DATA_SIZE_2 10000
#define DATA_SIZE_3 50000
#define DATA_SIZE_4 100000
#define DATA_SIZE_5 250000
#define DATA_SIZE_6 500000
//#define DATA_SIZE_7 1000000

#define MIN_PRIO 0
#define MAX_PRIO std::pow(2, 12)
#define PRIORITY_MOD 999

#define LOOPS 100

std::vector<size_t> SIZES = {DATA_SIZE_1, DATA_SIZE_2, 
    DATA_SIZE_3, DATA_SIZE_4, DATA_SIZE_5, DATA_SIZE_6};

// efficiency tests

// insert
// extract_max
// find_max / peek
// modify_key
// return_size

int main(int argc, char* argv[]){
    //std::cout << "CURRENT OP:  INSERT" << std::endl;
    //std::cout << "CURRENT OP:  EXTRACT_MAX" << std::endl;
    //std::cout << "CURRENT OP:  PEEK" << std::endl;
    //std::cout << "CURRENT OP:  MODIFY_KEY" << std::endl;
    std::cout << "CURRENT OP:  RETURN SIZE" << std::endl;

    for(auto size : SIZES){
        std::cout << "======================" << std::endl << std::endl;
        std::cout << size << std::endl << std::endl;

        size_t heap_time = 0;
        size_t list_time = 0;
        size_t fib_time  = 0;

        TimeVar start;
        TimeVar end;

        for(uint8_t index = 0; index < LOOPS; index++){
            Generator gen = Generator();

            PriorityQueue_Heap<int> queue_heap;
            PriorityQueue_LinkedList<int> queue_list;
            FibonacciHeap queue_fib;

            std::vector<int> items = gen.generate_int(size);
            int ITEM_CHANGE = items[gen.random(0, items.size())];

            for(int item : items){
                queue_heap.insert(item, gen.random(MIN_PRIO, MAX_PRIO));
                queue_list.insert(item, gen.random(MIN_PRIO, MAX_PRIO));
                queue_fib.insert(item, gen.random(MIN_PRIO, MAX_PRIO));
            }

            start = timeNow();
            //queue_heap.insert(100, gen.random(MIN_PRIO, MAX_PRIO)); //DONE
            //queue_heap.extract_max();
            //queue_heap.find_max();
            //queue_heap.modify_key(ITEM_CHANGE, PRIORITY_MOD);
            queue_heap.get_size();
            end = timeNow();
            heap_time += duration(end - start);



            start = timeNow();
            //queue_list.insert(100, gen.random(MIN_PRIO, MAX_PRIO));
            //queue_list.extract_max();
            //queue_list.find_max();
            //queue_list.modify_key(ITEM_CHANGE, PRIORITY_MOD);
            queue_list.get_size();
            end = timeNow();
            list_time += duration(end - start);



            start = timeNow();
            //queue_fib.insert(gen.random(MIN_PRIO, MAX_PRIO), 100);
            //queue_fib.extractMax();
            //queue_fib.findMax();
            //queue_fib.modifyKey(ITEM_CHANGE, PRIORITY_MOD);
            queue_fib.getSize();
            end = timeNow();
            fib_time += duration(end - start);
        }

        std::cout << "HEAP:  " << heap_time / LOOPS << std::endl;
        std::cout << "LIST:  " << list_time / LOOPS << std::endl;
        std::cout << "FIBB:  " << fib_time / LOOPS << std::endl;
        std::cout << std::endl;
    }

    return 0;
}