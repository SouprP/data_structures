#include <iostream>
#include <utils/generator.h>
#include <chrono>

#include <structures/priority_queue_heap.h>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()


#define DATA_SIZE_1 1000
#define DATA_SIZE_2 10000
#define DATA_SIZE_3 50000
#define DATA_SIZE_4 100000
#define DATA_SIZE_5 250000
#define DATA_SIZE_6 500000
#define DATA_SIZE_7 1000000

#define OBJECT_ADD 999
#define LOOPS 100

std::vector<size_t> SIZES = {DATA_SIZE_1, DATA_SIZE_2, 
    DATA_SIZE_3, DATA_SIZE_4, DATA_SIZE_5, DATA_SIZE_6, DATA_SIZE_7};

// efficiency tests

int main(int argc, char* argv[]){
    return 0;
}