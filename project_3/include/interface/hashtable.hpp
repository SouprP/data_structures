#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef>
#include <string>
#include <vector>
#include <cmath>

enum HashType{
    MOD, // normal modulo
    MOD_X, // modulo with multiplying
    FIB, // fibonacci
    ALG, // algebra 
};

template<typename T>
class HashTable{
    private:
        const double alfa = 0.6180339887; // golden ratio - 1 
        const size_t a = 2654435769; // constant relatively prime to 2^w
        const size_t w = 64; // machine word size in bits

        const double phi = 1.6180339887; // golden ratio
        const size_t a_m = static_cast<size_t>(pow(2, 64) / phi); // 64-bit multiplier

    protected:
        HashType hash_type;

        size_t size;
        size_t capacity;
        size_t collision_amount;
        
        size_t hash(std::string& key, HashType type){
            size_t s_int = 0;
            //std::cout << "hash size: " << this->size << std::endl; 
            //std::cout << "hash capacity: " << this->capacity << std::endl; 

            unsigned long djb2 = 5381;
            //for(auto &k : key)
            //    s_int += int(k);

            // transform the string into a number using djb2
            // using djb2 instead of a simple int(k)
            // proved to be more a more effective way of doing this
            // (less collisions)
            for(auto &k : key)
                djb2 = ((djb2 << 5) + djb2) + int(k);

            s_int = djb2;
            const size_t m = log2(size); // log base 2 of table size

            switch(type){
                // hα(x) = x mod m
                case HashType::MOD:
                    return s_int % size;

                // hα(x) = ⌊(αx mod W )/(W /m)⌋
                case HashType::MOD_X:
                    return (a * s_int) >> (w - m);

                // not used + it's not even aglebraic hashing
                case HashType::ALG:
                    return int(size*(alfa*s_int*2 - int(alfa*s_int*2)));

                // fibonacci hashing
                case HashType::FIB:
                    return (a_m * s_int) >> (w - (size_t) log2(size));
            }

            // it should not get here
            return 0;

        }
    public:
        /**
         * 
         *      INHERITED
         * 
        */
        virtual void insert(std::string key, T value) = 0;
        virtual void remove(std::string key) = 0;
        virtual T get(std::string key) = 0;

        // debug
        // change it to something else
        // return a vector of vectors?
        virtual std::vector<T> get_values() = 0;

        size_t get_size(){
            return size;
        }

        size_t get_col_amount(){
            return collision_amount;
        }
};

#endif