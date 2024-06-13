#ifndef OPEN_ADDR_HASHTABLE_HPP_
#define OPEN_ADDR_HASHTABLE_HPP_

#include <interface/hashtable.hpp>
#include<interface/hashtable.hpp>
#include <utils/node.hpp>
#include <vector>
#include <string>

template<typename T>
class OpenAddrTable : public HashTable<T> {
    private:
        Pair<T>** arr;

        // find a new index
        size_t probe(size_t hash, size_t i) const {
            // inear probing
            return (hash + i*i) % this->size;
        }

        // resize so the load factor is lower
        void resize() {
            size_t new_size = this->size*2;
            std::cout << "resize" << std::endl;
            Pair<T>** new_arr = new Pair<T>*[new_size];
            for (size_t i = 0; i < new_size; ++i) {
                new_arr[i] = nullptr;
            }

            this->collision_amount = 0;

            // insert elements into the new arr
            for (size_t i = 0; i < this->size; ++i) {
                if (arr[i] != nullptr) {
                    size_t new_hash = this->hash(arr[i]->key, this->hash_type);
                    size_t j = 0;
                    while (new_arr[probe(new_hash, j)] != nullptr) {
                        j++;
                        this->collision_amount++;
                    }
                    new_arr[probe(new_hash, j)] = arr[i];
                }
            }

            delete[] arr;
            arr = new_arr;
            this->size = new_size;
        }

    public:
        OpenAddrTable(size_t size, HashType type) {
            this->size = size;
            this->capacity = 0;
            this->collision_amount = 0;
            this->hash_type = type;

            arr = new Pair<T>*[size];
            for (size_t i = 0; i < size; ++i) {
                arr[i] = nullptr;
            }
        }

        ~OpenAddrTable() {
            for (size_t i = 0; i < this->size; ++i) {
                if (arr[i] != nullptr) {
                    delete arr[i];
                }
            }
            delete[] arr;
        }

        // insert a new element
        void insert(std::string key, T value) override {
            if (this->capacity >= this->size * 0.7) {
                resize();
            }

            // key to index hash
            size_t hash = this->hash(key, this->hash_type);
            size_t i = 0;

            // find an empty space
            while (arr[probe(hash, i)] != nullptr && arr[probe(hash, i)]->key != key) {
                i++;
                this->collision_amount++;
            }
            
            // insert an element
            size_t idx = probe(hash, i);
            if (arr[idx] == nullptr) {
                arr[idx] = new Pair<T>(key, value);
                this->capacity++;
            } else {
                arr[idx]->value = value;
            }
        }

        // remove an element
        void remove(std::string key) override {
            size_t hash = this->hash(key, this->hash_type);
            size_t i = 0;

            // find the place of the item we want to remove
            while (arr[probe(hash, i)] != nullptr && arr[probe(hash, i)]->key != key) {
                i++;
            }

            // remove the item
            size_t idx = probe(hash, i);
            if (arr[idx] != nullptr && arr[idx]->key == key) {
                delete arr[idx];
                arr[idx] = nullptr;
                this->capacity--;

                // reinsert all items that are located at higher indexes
                size_t j = i + 1;
                while (arr[probe(hash, j)] != nullptr) {
                    Pair<T>* temp = arr[probe(hash, j)];
                    arr[probe(hash, j)] = nullptr;
                    this->capacity--;
                    insert(temp->key, temp->value);
                    delete temp;
                    j++;
                }
            }
        }

        // get the value associated with a key
        T get(std::string key) override {
            size_t hash = this->hash(key, this->hash_type);
            size_t i = 0;

            // look for the item we are looking for
            while (arr[probe(hash, i)] != nullptr && arr[probe(hash, i)]->key != key) {
                i++;
            }

            // return the item
            size_t idx = probe(hash, i);
            if (arr[idx] != nullptr && arr[idx]->key == key) {
                return arr[idx]->value;
            }

            // here so it doesnt show warnings when building with CMake
            throw std::runtime_error("Key not found");
        }

        // finally a working get_values() function, also a display function
        std::vector<T> get_values() override {
            std::vector<T> values;
            for (size_t i = 0; i < this->size; ++i) {
                if (arr[i] != nullptr) {
                    values.push_back(arr[i]->value);
                    std::cout << arr[i]->key << std::endl;
                }
            }
            return values;
        }
};

#endif