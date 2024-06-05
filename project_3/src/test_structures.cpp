#include <iostream>
#include <utils/generator.hpp>
#include <chrono>

#include <structures/hash_tables/chain_table.hpp>
#include <structures/hash_tables/cuckoo_table.hpp>

// custom tests

int main(){
    Generator gen;

    HashTable<int>* table =  new ChainHashTable<int>(10, HashType::MOD_X);
    //HashTable<int>* table = new CuckooHashTable<int>(10, HashType::MOD);

    ///std::cout << table->get_size() << std::endl;
    table->insert("donald tusk", 5);
    table->insert("tusk donald", 2);
    table->insert("morawiecki", 100);
    table->insert("george bush", 1002);
    table->insert("5", 5);

    std::cout << "BEFORE REMOVE" << std::endl;
    table->get_values();
    // table->remove("morawiecki");
    //table->remove("tusk donald");
    table->remove("donald tusk");

    std::cout << std::endl << "AFTER REMOVE" << std::endl;
    table->get_values();
    return 0;
}


