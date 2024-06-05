#ifndef OPEN_ADDR_HASHTABLE_HPP_
#define OPEN_ADDR_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <utils/node.hpp>

template<typename T>
class OpenAddrTable : HashTable<T>{
    private:
        // add some array here?
    public:
        OpenAddrTable(size_t size, HashType hash_type){
            this->size = size;
            this->hash_type = hash_type;

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
