#ifndef CUCKOO_HASHTABLE_HPP_
#define CUCKOO_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <utils/node.hpp>

template<typename T>
class CuckooHashTable : public HashTable<T>{
    private:
        HashType other_hash;

        Pair<T>** arr1;
        Pair<T>** arr2;

        int cycle;

        void rehash(){
            std::cout << "rehash" << std::endl;
            this->size *= 2;
        }

    public:
        CuckooHashTable(size_t size, HashType hash_type, HashType other_hash){
            this->size = size;
            this->hash_type = hash_type;
            this->other_hash = other_hash;

            arr1 = new Pair<T>*[size];
            arr2 = new Pair<T>*[size];

            for(size_t i = 0; i < this->size; i++){
                arr1[i] = nullptr;
                arr2[i] = nullptr;
            }
        }

        void insert(std::string key, T value) override{
            size_t hash_1 = this->hash(key, HashType::MOD);
            size_t hash_2 = this->hash(key, HashType::MOD_X);

            float load_factor = (float) this->capacity / (float) this->size;
            if(load_factor > 0.5)
                rehash();
            
            Pair<T>* new_piar = new Pair<T>(key, value);

            if(arr1[hash_1] == nullptr){
                arr1[hash_1] = new_piar;
                this->capacity++;
                return;
            }
            
            if(arr2[hash_2] == nullptr){
                arr2[hash_2] = arr1[hash_1];
                arr1[hash_1] = new_piar;
                this->capacity++;
                return;
            }

            // infinite loop if exceeds
            for(uint8_t i = 0; i < 4; i++){
                // hash 1
                size_t new_hash = this->hash(arr2[hash_2]->key, HashType::MOD_X);
                if(arr1[hash_1] == nullptr){
                    arr1[new_hash] = arr2[hash_2];
                    arr2[hash_2] = arr1[hash_1];
                    arr1[hash_1] = new_piar;
                    this->capacity++;
                    return;
                }
            }

            rehash();
            insert(key, value);
            
        }

        void remove(std::string key) override{

        }

        T get(std::string key) override{

        }

        std::vector<T> get_values() override{
            for(size_t i = 0; i < this->size; i++){
                // std::cout << arr1[i] ? arr1[i]->key : '-'
                //     << ' ' << arr2[i] ? arr2[i]->key : ' '
                //     << std::endl;
                if(arr1[i] != nullptr){
                    std::cout << arr1[i]->key;
                }else
                    std::cout << "---";


                std::cout << "     ";
                if(arr2[i] != nullptr){
                    std::cout << arr2[i]->key;
                }else
                    std::cout << "---";

                std::cout << std::endl;
            }

            return {};
        }
};

#endif