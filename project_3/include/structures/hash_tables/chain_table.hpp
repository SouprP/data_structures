#ifndef CHAIN_HASHTABLE_HPP_
#define CHAIN_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <structures/other/linked_list.hpp>

template<typename T>
class ChainHashTable : public HashTable<T>{
    private:
        HashType hash_type;

        LinkedList<Pair<T>*>** chain_List;

    public:
        ChainHashTable(size_t size, HashType hash_type){
            this->size = size;
            this->hash_type = hash_type;

            // setup the list of linked lists
            chain_List = new LinkedList<Pair<T>*>*[size];
            for(size_t index = 0; index < this->size; index++)
                chain_List[index] = new LinkedList<Pair<T>*>();
        }

        void insert(std::string key, T value) override{
            // hash the key to an index
            size_t index = this->hash(key);
            std::cout << "hash output: " << index << std::endl;

            // insert a new element
            Pair<T>* new_pair = new Pair<T>(key, value);
            chain_List[index]->add_front(new_pair);

            // for(auto obj : chain_List[index]->get_values())
            //     std::cout << obj->key << std::endl;
        }

        void remove(std::string key) override{
            size_t index = this->hash(key);

            LinkedList<Pair<T>*>* list = chain_List[index];

            size_t i = 1;
            //std::cout << "size" << list->get_values().size() << std::endl;
            for(Pair<T>* pair : list->get_values()){
                //std::cout << "Current pair: " << pair->key << std::endl;
                if(pair->key == key){
                    //std::cout << "Removed" << std::endl;
                    //std::cout << "i: " << i << std::endl;
                    //std::cout << "get: " << list->get(i)->key << std::endl;
                    list->remove(i);
                    break;
                }

                i++;
            }

        }

        T get(std::string key) override{
            size_t index = this->hash(key, hash_type);

            LinkedList<Pair<T>*>* list = chain_List[index];

            for(Pair<T>* pair : list->get_values())
                if(pair->key == key)
                    return pair->value;

        }

        std::vector<T> get_values() override{
            for(size_t index = 0; index < this->size; index++){
                std::cout << "========" << index << std::endl;
                LinkedList<Pair<T>*>* list = chain_List[index];
                if(list->get_values().size() != 0)
                    for(Pair<T>* obj : list->get_values())
                        std::cout << obj->key << std::endl;
            }

            return {};
        }

};

#endif