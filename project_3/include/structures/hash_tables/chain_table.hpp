#ifndef CHAIN_HASHTABLE_HPP_
#define CHAIN_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <structures/other/linked_list.hpp>

template<typename T>
class ChainHashTable : public HashTable<T>{
    private:
        HashType hash_type;

        // array of all the the lists
        LinkedList<Pair<T>*>** chain_List;

    public:
        ChainHashTable(size_t size, HashType hash_type){
            this->size = size;
            this->collision_amount = 0;
            this->hash_type = hash_type;

            // setup the list of linked lists
            chain_List = new LinkedList<Pair<T>*>*[size];
            for(size_t index = 0; index < this->size; index++)
                chain_List[index] = new LinkedList<Pair<T>*>();
        }

        void insert(std::string key, T value) override{
            // hash the key to an index
            size_t index = this->hash(key, hash_type);

            // insert a new element
            Pair<T>* new_pair = new Pair<T>(key, value);
            if(chain_List[index]->get_size() >= 1){
                //std::cout << "col add: " << chain_List[index]->get_size()
                //    << std::endl;
                this->collision_amount++;
            }

            chain_List[index]->add_front(new_pair);
        }

        void remove(std::string key) override{
            // hash the key to an index
            size_t index = this->hash(key, hash_type);

            // get the list where the Pair<T>* is held
            LinkedList<Pair<T>*>* list = chain_List[index];

            // search for it
            // and remove it at it's list index using list.remove()
            size_t i = 1;
            for(Pair<T>* pair : list->get_values()){
                if(pair->key == key){
                    if(list->get_size() > 1)
                        this->collision_amount--;

                    list->remove(i);
                    break;
                }

                i++;
            }

        }

        T get(std::string key) override{
            // hash the key to an index
            size_t index = this->hash(key, hash_type);

            // get the list where the Pair<T>* is held
            LinkedList<Pair<T>*>* list = chain_List[index];

            // look at all the values in the list
            // and compare them to our key
            for(Pair<T>* pair : list->get_values())
                if(pair->key == key)
                    return pair->value;

            return T();
        }

        // yea, it does not return a vector of values
        // it functions as a display function pretty much
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