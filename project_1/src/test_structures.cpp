#include <catch2/catch.hpp>
#include <utils/file.h>

#include <structures/array_list.h>
#include <structures/linked_list.h>
#include <structures/linked_list_tail.h>
#include <structures/double_linked_list.h>

#include <chrono>

#define DATA_SET_1 "data_10k.txt"
#define DATA_SET_2 "data_100k.txt"
#define DATA_SET_3 "ddata_500k.txt"
#define DATA_SET_4 "data_1m.txt"

#define INDEX_TO_REMOVE 5000
#define INDEX_TO_ADD 5000

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

TimeVar start_time;
TimeVar end_time;
std::vector<int> data;

void test_array(){
    ArrayList<int> array;
    for(auto obj : data)
        array.add_front(obj);

    start_time = timeNow();
    
    // ADD
    // array.add_back(999);
    // array.add_front(999);
    // array.add(999, 9999);

    //REMOVE
    //array.remove_back();
    //array.remove_front();
    //array.remove(999);

    //GET
    //array.get(500);
    //array.search();


    end_time = timeNow();
    std::cout << "ArrayList took: " << duration(end_time - start_time) << "ns" << std::endl;
}


int main(){
    FileIO<int> file;
    data = file.read(DATA_SET_1);    
    
    test_array();
    return 0;
}


