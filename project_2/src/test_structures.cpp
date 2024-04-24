#include <iostream>
#include <utils/generator.h>
#include <chrono>

#include <structures/priority_queue_heap.h>

// custom tests

int main(){
    Generator gen;

    PriorityQueue_Heap<int> queue;

    //for(int i = 0; i < 10; i++)
        //queue.insert(gen.random(0, 999), gen.random(0, 256));

    for(auto obj : queue.get_vector()){
        std::cout << "Priority: " << obj.priority << ", value:  " << obj.value << std::endl;
    }
    //
    queue.insert(5, 1);
    queue.insert(10, 2);
    queue.insert(999, 100);
    queue.insert(999, 50);
    queue.insert(5, 1);
    queue.insert(5, 29);
    queue.insert(10, 45);
    queue.insert(10, 14);
    //*/

    std::cout << "AFTER ACTION" << std::endl << std::endl;
    queue.modify_key(5, 0);
    queue.modify_key(999, 99999);
    //queue.extract_max();
    //queue.extract_max();
    //queue.extract_max();
    for(auto obj : queue.get_vector()){
        std::cout << "Priority: " << obj.priority << ", value:  " << obj.value << std::endl;
    }

    std::cout << "PEEK" << std::endl << std::endl;
    std::cout << queue.find_max() << std::endl;
    return 0;
}


