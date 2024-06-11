#include <iostream>
#include <utils/generator.hpp>
#include <chrono>

#include <structures/hash_tables/chain_table.hpp>
#include <structures/hash_tables/cuckoo_table.hpp>

// custom tests
//#define SIZE std::pow(2, 20)
//#define KEY_SET std::pow(2, 16)
#define SIZE 500000
#define KEY_SET 500000

int main(){
    Generator gen = Generator();

    //HashTable<int>* table =  new ChainHashTable<int>(10, HashType::MOD_X);
    HashTable<int>* table = new CuckooHashTable<int>(SIZE, HashType::MOD, HashType::MOD);

    //std::cout << table->get_size() << std::endl;
    // table->insert("donald tusk", 5);
    // table->insert("tusk donald", 2);
    // table->insert("morawiecki", 100);
    // table->insert("george bush", 1002);
    // table->insert("5", 5);
    for(auto obj : gen.generate_string(KEY_SET))
        table->insert(obj, gen.random(0, 10000));

    //std::cout << "BEFORE REMOVE" << std::endl;
    //table->get_values();
    // table->remove("morawiecki");
    //table->remove("tusk donald");
    //table->remove("donald tusk");

    std::cout << std::endl << "AFTER REMOVE" << std::endl;
    //table->get_values();

    //for(auto obj : gen.generate_string(1000))
    //    std::cout << obj << std::endl;
    return 0;
}


