#include <iostream>
#include <utils/generator.h>
#include <utils/file.h>
#include <structures/array_list.h>
#include <structures/linked_list.h>
#include <structures/linked_list_tail.h>
#include <structures/double_linked_list.h>

int main(int argc, char* argv[]){
    Generator gen = Generator();
    auto data = gen.generate_int(12);

    FileIO<int> file;
    //file.write("data_test.txt", data);
    auto read = file.read("data_test.txt");

    /*
    ArrayList<int> array;

    for(auto obj : read){
        array.add_front(obj);
        //array.add_back(obj);
    }

    //array.remove_back();
    //array.remove_front();
    array.remove(1);
    std::cout << array.get(10) << std::endl;
        

    for(size_t i = 0; i < array.get_size(); i++)
        std::cout << array.get(i) << ", ";

    std::cout << std::endl;
    std::cout << array.get_size() << std::endl;
    */
   
    //LinkedList<int> list;
    //for(auto obj : read)
        //list.add_back(obj);
    
    //list.add(9999, 5);
    //list.remove(6);
    //for(auto obj : list.get_values())
        //std::cout << obj <+< ", " << std::endl;

    
    //LinkedListTail<int> list_tail;
    //for(auto obj : read)
        //list_tail.add(obj, 1);

    //list_tail.add_front(5);
    //list_tail.remove_back();
    //std::cout << "get: " << *list_tail.get(5) << std::endl;
    //list_tail.remove(5);
    //for(auto obj : list_tail.get_values())
        //std::cout << obj << ", " << std::endl;

    //std::cout << *list_tail.get(10) << std::endl;
    //std::cout << "get_tail: " << *list_tail.get_tail() << std::endl;
    //std::cout << *list_tail.get_tail() << std::endl;
    
   DoubleLinkedList<int> d_list;
   for(auto obj : read)
    d_list.add_front(obj);

    //d_list.add(999, 10);

    for(auto obj : d_list.get_values())
        std::cout << obj << ", " << std::endl;

}