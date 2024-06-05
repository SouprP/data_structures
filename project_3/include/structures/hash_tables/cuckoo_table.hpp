#ifndef CUCKOO_HASHTABLE_HPP_
#define CUCKOO_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <utils/node.hpp>

template<typename T>
class CuckooHashTable : public HashTable<T>{
    private:
        Pair<T>** arr1;
        Pair<T>** arr2;

    public:
        CuckooHashTable(size_t size, HashType hash_type){
            this->size = size;
            this->hash_type = hash_type;

            arr1 = new Pair<T>*[size];
            arr2 = new Pair<T>*[size];

            for(size_t i = 0; i < this->size; i++){
                arr1[i] = nullptr;
                arr2[i] = nullptr;
            }
        }

        void insert(std::string key, T value) override{
            
        }

        void remove(std::string key) override{

        }

        T get(std::string key) override{

        }

        std::vector<T> get_values() override{

        }
};

#endif