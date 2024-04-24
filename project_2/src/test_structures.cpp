#include <iostream>
#include <utils/generator.h>
#include <chrono>

#include <structures/priority_queue_heap.h>
#include <structures/priority_queue_list.h>

// custom tests

int main(){
    Generator gen;

    //PriorityQueue_Heap<int> queue;
    PriorityQueue_LinkedList<int> queue;

    //for(int i = 0; i < 10; i++)
        //queue.insert(gen.random(0, 999), gen.random(0, 256));

    //for(auto obj : queue.get_vector())
    //    std::cout << "Priority: " << obj.priority << ", value:  " << obj.value << std::endl;
    
    //
    queue.insert(5, 1);
    queue.insert(10, 2);
    queue.insert(999, 100);
    queue.insert(998, 50);
    queue.insert(5, 1);
    queue.insert(5, 29);
    queue.insert(10, 45);
    queue.insert(10, 14);

    for(auto obj : queue.get_values())
        std::cout << "Priority: " << obj.priority << ", value:  " << obj.value << std::endl;
    //*/

    std::cout << "AFTER ACTION" << std::endl << std::endl;
    try{
        //queue.modify_key(5, 2);
    }catch(std::exception ignored){
        std::cout << ignored.what();
    }
    queue.modify_key(5, 911);
    queue.modify_key(999, 99999);
    queue.modify_key(998, 500);
    //queue.extract_max();
    //queue.extract_max();
    //queue.extract_max();
    for(auto obj : queue.get_values())
        std::cout << "Priority: " << obj.priority << ", value:  " << obj.value << std::endl;
    

    //std::cout << "PEEK" << std::endl << std::endl;
    //std::cout << queue.find_max() << std::endl;
    //std::cout << queue.extract_max() << std::endl;
    return 0;
}


