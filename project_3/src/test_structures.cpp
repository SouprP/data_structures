#include <iostream>
#include <utils/generator.hpp>
#include <chrono>

#include <structures/hash_tables/chain_table.hpp>
#include <structures/hash_tables/cuckoo_table.hpp>
#include <structures/hash_tables/open_addr_table.hpp>


#define SIZE 100000
#define KEY_SET SIZE

int main(){
    Generator gen = Generator();

    HashTable<int>* table =  new ChainHashTable<int>(SIZE, HashType::FIB);
    //HashTable<int>* table = new OpenAddrTable<int>(10, HashType::MOD_X);
    //HashTable<int>* table = new CuckooHashTable<int>(SIZE, HashType::MOD, HashType::MOD_X, HashType::FIB);


    for(auto obj : gen.generate_string(KEY_SET))
        table->insert(obj, gen.random(0, 10000));
    
    // table->insert("donald tusk", 10);
    // table->insert("morawiecki", 5);
    // table->insert("jaruzelski", 20);

    std::cout << std::endl << "BEFORE REMOVE" << std::endl;
    //table->get_values();


    //table->remove("donald tusk");
    //table->remove("jaruzelski");


    std::cout << std::endl << "AFTER REMOVE" << std::endl;
    //table->get_values();
    std::cout << "Collisions amount: " << table->get_col_amount() << std::endl;

    // for(auto obj : gen.generate_string(1))
    //    std::cout << obj << std::endl;
    return 0;
}


