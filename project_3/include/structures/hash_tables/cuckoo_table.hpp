#ifndef CUCKOO_HASHTABLE_HPP_
#define CUCKOO_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include <utils/node.hpp>
#include <iostream>
#include <vector>

template<typename T>
class CuckooHashTable : public HashTable<T>{
    private:
        std::vector<HashType> hash_types; //= {HashType::MOD, HashType::MOD_X, HashType::FIB};
        size_t current_hash_index = 0;
        HashType other_hash;

        Pair<T>** arr1;
        Pair<T>** arr2;

        int cycle =  0;

        void rehash(){
            this->cycle++;
            size_t old_size = this->size;
            this->size *= 2;
            this->capacity = 0;
            this->collision_amount = 0;
            // std::cout << "Rehash " << cycle << ", new size: " << this->size << std::endl;

            Pair<T>** old_arr1 = arr1;
            Pair<T>** old_arr2 = arr2;

            arr1 = new Pair<T>*[this->size];
            arr2 = new Pair<T>*[this->size];

            for (size_t i = 0; i < this->size; i++) {
                arr1[i] = nullptr;
                arr2[i] = nullptr;
            }

            // cycle to the next hashing algorithm
            current_hash_index = (current_hash_index + 1) % hash_types.size();
            this->hash_type = hash_types[current_hash_index];
            this->other_hash = hash_types[(current_hash_index + 1) % hash_types.size()];

            // copy contents from old arrays
            std::vector<Pair<T>*> elements;
            for (size_t i = 0; i < old_size; i++) {
                if (old_arr1[i] != nullptr) {
                    elements.push_back(old_arr1[i]);
                }
                if (old_arr2[i] != nullptr) {
                    elements.push_back(old_arr2[i]);
                }
            }

            // insert all the elements from old_arrs to new containers
            for (auto elem : elements) {
                insert(elem->key, elem->value);
                delete elem;
            }

            delete[] old_arr1;
            delete[] old_arr2;
        }

    public:
        CuckooHashTable(size_t size, HashType hash_type, HashType second_hash, HashType third_hash){
            this->size = size;
            this->collision_amount = 0;
            this->hash_type = hash_type;
            this->other_hash = second_hash;

            // the list of hashes to cycle through when rehaashing
            this->hash_types = {hash_type, second_hash, third_hash};

            // init of arrays
            arr1 = new Pair<T>*[size];
            arr2 = new Pair<T>*[size];

            for(size_t i = 0; i < this->size; i++){
                arr1[i] = nullptr;
                arr2[i] = nullptr;
            }
        }

        void insert(std::string key, T value) override{
            
            // decrease the chance of collision by rehashing when our 
            //hash table is full in more than 50%
            float load_factor = (float)this->capacity / (float)this->size;
            if (load_factor > 0.5) {
                // std::cout << "load rehash" << std::endl;
                rehash();
            }

            // create a new pair from the provided key and value
            Pair<T>* new_pair = new Pair<T>(key, value);
            size_t hash1 = this->hash(key, this->hash_type);
            size_t hash2 = this->hash(key, this->other_hash);

            // insert and handle collisions if nessecary
            // max 4 attempts
            for (size_t i = 0; i < 4; ++i) {
                if (arr1[hash1] == nullptr) {
                    arr1[hash1] = new_pair;
                    this->capacity++;
                    return;
                }

                if (arr2[hash2] == nullptr) {
                    arr2[hash2] = new_pair;
                    this->capacity++;
                    return;
                }

                // collision handling
                // evict the previous value to a new place
                std::swap(arr1[hash1], new_pair);
                hash1 = this->hash(new_pair->key, this->hash_type);
                std::swap(arr2[hash2], new_pair);
                hash2 = this->hash(new_pair->key, this->other_hash);

                this->collision_amount++;
            }

            rehash();
            insert(key, value);
        }

        void remove(std::string key) override{
            // hash the key to index
            size_t hash1 = this->hash(key, this->hash_type);
            size_t hash2 = this->hash(key, this->other_hash);

            // check if our pair is in the first array and remove it
            if (arr1[hash1] != nullptr && arr1[hash1]->key == key) {
                delete arr1[hash1];
                arr1[hash1] = nullptr;
                this->capacity--;
                return;
            }

            // check if it's in the second array and remove it
            if (arr2[hash2] != nullptr && arr2[hash2]->key == key) {
                delete arr2[hash2];
                arr2[hash2] = nullptr;
                this->capacity--;
                return;
            }
        }

        T get(std::string key) override{
            // hash the key to index
            size_t hash1 = this->hash(key, this->hash_type);
            size_t hash2 = this->hash(key, this->other_hash);

            // check if our pair is in the first array and get it
            if (arr1[hash1] != nullptr && arr1[hash1]->key == key) {
                return arr1[hash1]->value;
            }

            // check if it's in the second array and get it
            if (arr2[hash2] != nullptr && arr2[hash2]->key == key) {
                return arr2[hash2]->value;
            }
        }

        // yea, it does not return a vector of values
        // it functions as a display function pretty much
        std::vector<T> get_values() override{
            for(size_t i = 0; i < this->size; i++){
                if(arr1[i] != nullptr){
                    std::cout << arr1[i]->key;
                }else {
                    std::cout << "---";
                }

                std::cout << "     ";
                if(arr2[i] != nullptr){
                    std::cout << arr2[i]->key;
                }else {
                    std::cout << "---";
                }

                std::cout << std::endl;
            }

            return {};
        }
};

#endif