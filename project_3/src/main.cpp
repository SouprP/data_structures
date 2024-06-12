#include <iostream>
#include <utils/generator.hpp>
#include <chrono>

#include <structures/hash_tables/chain_table.hpp>
#include <structures/hash_tables/cuckoo_table.hpp>
#include <structures/hash_tables/open_addr_table.hpp>

typedef std::chrono::high_resolution_clock::time_point TimeVar;

#define duration(a) std::chrono::duration_cast<std::chrono::microseconds>(a).count()
#define timeNow() std::chrono::high_resolution_clock::now()


#define DATA_SIZE_1 1000
#define DATA_SIZE_2 10000
#define DATA_SIZE_3 25000
#define DATA_SIZE_4 50000
#define DATA_SIZE_5 100000

#define LOOPS 100

// std::vector<size_t> SIZES = {DATA_SIZE_1, DATA_SIZE_2, 
//     DATA_SIZE_3, DATA_SIZE_4, DATA_SIZE_5};

//std::vector<size_t> SIZES = {1000};
std::vector<size_t> SIZES = {DATA_SIZE_2};
// efficiency tests

int main(int argc, char* argv[]){
    for(auto size : SIZES){
        std::cout << "======================" << std::endl << std::endl;
        std::cout << size << std::endl << std::endl;

        size_t chain_time = 0;
        size_t addr_time = 0;
        size_t cuckoo_time  = 0;

        size_t chain_cols = 0;
        size_t addr_cols = 0;
        size_t cuckoo_cols  = 0;

        TimeVar start;
        TimeVar end;

        for(uint8_t index = 0; index < LOOPS; index++){
            Generator gen = Generator();

            HashTable<int>* chain_table =  new ChainHashTable<int>(size, HashType::MOD_X);
            HashTable<int>* addr_table = new OpenAddrTable<int>(size, HashType::MOD_X);
            HashTable<int>* cuckoo_table = new CuckooHashTable<int>(size, HashType::MOD, HashType::MOD_X, HashType::FIB);


            std::vector<std::string> items = gen.generate_string(size);
            std::vector<std::string> remove_keys = {};

            //std::cout << "generated" << std::endl;
            
            for(size_t i = 0; i < LOOPS; i++)
                remove_keys.push_back(items[gen.random(0, items.size())]);

            for(std::string key : items){
                int value = gen.random(0, 10000);
                //chain_table->insert(key, value);
                addr_table->insert(key, value);
                //cuckoo_table->insert(key, value);
            }

            std::cout << "inserted!" << std::endl;

            chain_cols += chain_table->get_col_amount();
            addr_cols += addr_table->get_col_amount();
            cuckoo_cols += cuckoo_table->get_col_amount();

            start = timeNow();
            for(size_t i = 0; i < LOOPS; i++){
                chain_table->insert(gen.generate_string(1).at(0), gen.random(0, 10000));
                //chain_table->remove(remove_keys.at(i));
            }
                
            end = timeNow();
            chain_time += duration(end - start);



            start = timeNow();
            for(size_t i = 0; i < LOOPS; i++){
                addr_table->insert(gen.generate_string(1).at(0), gen.random(0, 10000));
                //addr_table->remove(remove_keys.at(i));
            }
            end = timeNow();
            addr_time += duration(end - start);



            start = timeNow();
            for(size_t i = 0; i < LOOPS; i++){
                cuckoo_table->insert(gen.generate_string(1).at(0), gen.random(0, 10000));
                //cuckoo_table->remove(remove_keys.at(i));   
            }
            end = timeNow();
            cuckoo_time += duration(end - start);
        }

        std::cout << "CHAIN:  " << chain_time / (LOOPS*LOOPS) << std::endl;
        std::cout << "ADDR :  " << addr_time / (LOOPS*LOOPS) << std::endl;
        std::cout << "CUCK :  " << cuckoo_time / (LOOPS*LOOPS) << std::endl;
        std::cout << "CHAIN COLS:  " << chain_cols / (LOOPS) << std::endl;
        std::cout << "ADDR  COLS:  " << addr_cols / (LOOPS) << std::endl;
        std::cout << "CUCK  COLS:  " << cuckoo_cols / (LOOPS) << std::endl;
        std::cout << std::endl;
    }

    return 0;
}