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
    //file.write("data_10k.txt", gen.generate_int(10000));
    //file.write("data_100k.txt", gen.generate_int(100000));
    //file.write("data_500k.txt", gen.generate_int(500000));
    //file.write("data_1m.txt", gen.generate_int(1000000));
    //file.write("data_test.txt", data);
    //auto read = file.read("data_test.txt");

    /*
    ArrayList<int> array;
    for(auto obj : read)
        array.add_back(obj);
        //array.add_back(obj);
    

    array.remove(10);
    std::cout << array.get(10) << std::endl;
        

    for(size_t i = 0; i < array.get_size(); i++)
        std::cout << array.get(i) << ", ";
    */
    
   
   /*
    LinkedList<int> list;
    for(auto obj : read)
        list.add_back(obj);
    
    //list.add(9999, 5);
    //list.remove(6);
    for(auto obj : list.get_values())
        std::cout << obj << ", " << std::endl;

    list.remove(10);
    std::cout << *list.get(10);
    */

    /*
    LinkedListTail<int> list_tail;
    for(auto obj : read)
        list_tail.add_back(obj);

    for(auto obj : list_tail.get_values())
        std::cout << obj << ", " << std::endl;

    list_tail.remove(10);
    std::cout << "get_10: " << *list_tail.get(10) << std::endl;
    std::cout << "get_tail: " << *list_tail.get_tail() << std::endl;
    //std::cout << *list_tail.get_tail() << std::endl;
    */

    /*
    DoubleLinkedList<int> d_list;
    for(auto obj : read)
        d_list.add_back(obj);

    d_list.add(999, 9);
    

    for(auto obj : d_list.get_values())
        std::cout << obj << ", " << std::endl;

    d_list.remove_back();
    std::cout << "tail: " << *d_list.get_tail();
    */

    // DOUBLE - works
    // LIST_TAIL - check
    // LIST - check
    // RRAY - check

}