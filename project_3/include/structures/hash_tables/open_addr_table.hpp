#ifndef OPEN_ADDR_HASHTABLE_HPP_
#define OPEN_ADDR_HASHTABLE_HPP_

#include<interface/hashtable.hpp>
#include <utils/node.hpp>
#include <vector>
#include <string>

template<typename T>
class OpenAddrTable : public HashTable<T> {
    private:
        Pair<T>** arr;

        size_t probe(size_t hash, size_t i) const {
            // Quadratic probing
            return (hash + i * i) % this->size;
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

        void insert(std::string key, T value) override {
            size_t hash = this->hash(key, this->hash_type);
            size_t i = 0;

            while (arr[probe(hash, i)] != nullptr && arr[probe(hash, i)]->key != key) {
                i++;
                this->collision_amount++;
            }

            size_t idx = probe(hash, i);
            if (arr[idx] == nullptr) {
                arr[idx] = new Pair<T>(key, value);
                this->capacity++;
            } else {
                arr[idx]->value = value;
            }
        }

        void remove(std::string key) override {
            size_t hash = this->hash(key, this->hash_type);
            size_t i = 0;

            while (arr[probe(hash, i)] != nullptr && arr[probe(hash, i)]->key != key) {
                i++;
            }

            size_t idx = probe(hash, i);
            if (arr[idx] != nullptr && arr[idx]->key == key) {
                delete arr[idx];
                arr[idx] = nullptr;
                this->capacity--;
            }
        }

        T get(std::string key) override {
            size_t hash = this->hash(key, this->hash_type);
            size_t i = 0;

            while (arr[probe(hash, i)] != nullptr && arr[probe(hash, i)]->key != key) {
                i++;
            }

            size_t idx = probe(hash, i);
            if (arr[idx] != nullptr && arr[idx]->key == key) {
                return arr[idx]->value;
            }

            throw std::runtime_error("Key not found");
        }

        std::vector<T> get_values() override {
            std::vector<T> values;
            for (size_t i = 0; i < this->size; ++i) {
                if(arr[i] != nullptr){
                    std::cout << arr[i]->key;
                }else {
                    std::cout << "---";
                }

                std::cout << std::endl;
            }
            return values;
        }
};

#endif
