#ifndef MENU_H
#define MENU_H

#include <utils/generator.h>

#include <structures/array_list.h>
#include <structures/linked_list.h>
#include <structures/linked_list_tail.h>
#include <structures/double_linked_list.h>

#include <iostream>
#include <vector>
#include <chrono>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::nanoseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()

#define OBJECT_ADD 200
#define OBJECT_FIND_FALSE 999
#define OBJECT_FIND_TRUE 20

class Menu{
    private:
        TimeVar start;
        TimeVar end;

        Generator gen;
        std::vector<int> data;
        size_t size_data;
    public:

        enum MAIN_MENU{
            GEN_DATA, // 0
            READ_DATA, // 1
            STRUCTS, // 2
            QUIT, // 3
        };

        enum SUB_STRUCTS{
            ADD_FRONT, // 0
            ADD_BACK, // 1
            ADD, // 2
            REMOVE_FRONT, // 3
            REMOVE_BACK, // 4
            REMOVE, // 5
            GET, // 6
            SEARCH, // 7
            RETURN // 8
        };

        size_t get_input(std::string input_info){
            //clear();
            size_t input;
            std::cout << std::endl << input_info;
            std::cin >> input;

            return input;
        }

        void clear(){
            printf("\x1b[H\x1b[J");
        }

        void go_back(bool go_main, bool prompt){
            if(prompt)
                uint8_t input = get_input("Return? [Press anything]");

            if(go_main){
                render();
                return;
            }
            render_structs_menu();
        }

        bool should_return(){
            uint8_t input = get_input("Test again or return? [0 / 1]");
            return input;
        }

        void read_data(){
            for(auto obj : data)
                std::cout << obj << std::endl;

            go_back(true, true);
        }

        void render_structs_menu(){
            clear();

            uint8_t input;
            std::cout << "SELECT ACTION TO TEST" << std::endl;
            std::cout << "1. ADD_FRONT" << std::endl;
            std::cout << "2. ADD_BACK" << std::endl;
            std::cout << "3. ADD" << std::endl;
            std::cout << "4. REMOVE_FRONT" << std::endl;
            std::cout << "5. REMOVE_BACK" << std::endl;
            std::cout << "6. REMOVE" << std::endl;
            std::cout << "7. GET" << std::endl;
            std::cout << "8. SEARCH" << std::endl;
            std::cout << "9. RETURN" << std::endl; 

            input = get_input("Action: ") - 1;
            switch(input){
                case SUB_STRUCTS::ADD_FRONT:
                    test_add_front();
                    render_structs_menu();
                    break;
                    // test front
                
                case SUB_STRUCTS::ADD_BACK:
                    test_add_back();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::ADD:
                    test_add();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::REMOVE_FRONT:
                    test_remove_front();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::REMOVE_BACK:
                    test_remove_back();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::REMOVE:
                    test_remove();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::GET:
                    test_get();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::SEARCH:
                    test_search();
                    render_structs_menu();
                    break;

                case SUB_STRUCTS::RETURN:
                    render();
                    break;
                    
            }
        };

        void render(){
            clear();
            uint8_t input;
            std::cout << "SELECT ACTION" << std::endl;
            std::cout << "1. Generate data," << std::endl;
            std::cout << "2. Read data," << std::endl;
            std::cout << "3. Test structures," << std::endl;
            std::cout << "4. Quit." << std::endl << std::endl;
            input = get_input("Action: ") - 1;

            switch(input){
                case MAIN_MENU::GEN_DATA:
                    size_data = get_input("Amount of data to generate: ");
                    data = gen.generate_int(size_data);
                    render();
                    break;

                case MAIN_MENU::READ_DATA:
                    read_data();
                    render();
                    break;

                case MAIN_MENU::STRUCTS:
                    render_structs_menu();
                    break;

                case MAIN_MENU::QUIT:
                    exit(0);
                    break;

                default:
                    exit(0);
                    break;
            }

        }

        void test_add_front(){
            clear();
            std::cout << "ADD FRONT" << std::endl << std::endl;
            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            start = timeNow();
            array.add_front(OBJECT_ADD);
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.add_front(OBJECT_ADD);
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.add_front(OBJECT_ADD);
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.add_front(OBJECT_ADD);
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_add_front();
            else
                render_structs_menu();
            

        }

        void test_add_back(){
            clear();
            std::cout << "ADD BACK" << std::endl << std::endl;
            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            
            start = timeNow();
            array.add_back(OBJECT_ADD);
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.add_back(OBJECT_ADD);
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.add_back(OBJECT_ADD);
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.add_back(OBJECT_ADD);
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_add_back();
            else
                render_structs_menu();
        }

        void test_add(){
            clear();
            std::cout << "ADD INDEX" << std::endl << std::endl;
            //size_t input = get_input("Index to add at [0 - DATA_SIZE]: ");
            //std::cout << std::endl;
            size_t input = size_data / 2;

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            start = timeNow();
            array.add(OBJECT_ADD, input);
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.add(OBJECT_ADD, input + 1);
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.add(OBJECT_ADD, input + 1);
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.add(OBJECT_ADD, input + 1);
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_add();
            else
                render_structs_menu();
        }

        void test_remove_front(){
            clear();
            std::cout << "REMOVE FRONT" << std::endl << std::endl;
            //size_t input = get_input("Index to add at [0 - DATA_SIZE]: ");
            std::cout << std::endl;

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            start = timeNow();
            array.remove_front();
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.remove_front();
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.remove_front();
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.remove_front();
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_remove_front();
            else
                render_structs_menu();
        }

        void test_remove_back(){
            clear();
            std::cout << "REMOVE BACK" << std::endl << std::endl;
            //size_t input = get_input("Index to add at [0 - DATA_SIZE]: ");
            std::cout << std::endl;

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            start = timeNow();
            array.remove_back();
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.remove_back();
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.remove_back();
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.remove_back();
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_add_back();
            else
                render_structs_menu();
        }

        void test_remove(){
            clear();
            std::cout << "REMOVE INDEX" << std::endl << std::endl;
            //size_t input = get_input("Index to add at [0 - DATA_SIZE-1]: ");
            //std::cout << std::endl;
            size_t input = size_data / 2;

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            start = timeNow();
            array.remove(input);
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.remove(input + 1);
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.remove(input + 1);
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.remove(input + 1);
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_remove();
            else
                render_structs_menu();
        }

        void test_get(){
            clear();
            std::cout << "GET INDEX" << std::endl << std::endl;
            //size_t input = get_input("Index to add at [0 - DATA_SIZE-1]: ");
            //std::cout << std::endl;
            size_t input = size_data / 2;

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            start = timeNow();
            array.get(input);
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.get(input + 1);
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.get(input + 1);
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.get(input + 1);
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_get();
            else
                render_structs_menu();
        }

        void test_search(){
            clear();
            std::cout << "SEARCH" << std::endl << std::endl;
            size_t input = get_input("Number to search for: ");
            std::cout << std::endl;

            ArrayList<int> array;
            LinkedList<int> list;
            LinkedListTail<int> list_tail;
            DoubleLinkedList<int> d_list;

            for(auto obj : data){
                array.add_front(obj);
                list.add_front(obj);
                list_tail.add_front(obj);
                d_list.add_front(obj);
            }

            bool is_found = array.search(input);
            std::cout << "Found? " << is_found << std::endl << std::endl;
            
            start = timeNow();
            array.search(input);
            end = timeNow();
            std::cout << "Array: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list.search(input + 1);
            end = timeNow();
            std::cout << "LinkedList: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            list_tail.search(input + 1);
            end = timeNow();
            std::cout << "LinkedListTail: " << duration(end - start) << "ns" << std::endl;

            start = timeNow();
            d_list.search(input + 1);
            end = timeNow();
            std::cout << "DoubleLinkedList: " << duration(end - start) << "ns" << std::endl << std::endl;

            if(!should_return())
                test_search();
            else
                render_structs_menu();
        }
};

#endif