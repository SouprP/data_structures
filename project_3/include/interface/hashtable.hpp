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
        const double alfa = 0.6180339887;
        // const int W = 1.0;
        const size_t a = 2654435769; // example constant, chosen to be relatively prime to 2^w
        const size_t w = 64; // fixed machine word size in bits
        //const size_t m = log2(size); // log base 2 of table size

        const double phi = 1.6180339887; // golden ratio
        const size_t a_m = static_cast<size_t>(pow(2, 64) / phi); // 64-bit multiplier
       // const size_t w = 64; // fixed machine word size in bits

    protected:
        HashType hash_type;

        size_t size;
        size_t capacity;
        
        size_t hash(std::string& key, HashType type){
            size_t s_int = 0;
            //std::cout << "hash size: " << this->size << std::endl; 
            std::cout << "hash capacity: " << this->capacity << std::endl; 

            for(auto &k : key)
                s_int += int(k);
                //std::cout << k << std::endl;

            //std::cout << s_int << std::endl;
            const size_t m = log2(size); // log base 2 of table size

            switch(type){
                // hα(x) = x mod m
                case HashType::MOD:
                    return s_int % size;

                // hα(x) = ⌊(αx mod W )/(W /m)⌋
                case HashType::MOD_X:
                    //return int(size*(alfa*s_int - int(alfa*s_int)));
                    // const size_t a = 2654435769; // example constant, chosen to be relatively prime to 2^w
                    // const size_t w = 64; // fixed machine word size in bits
                    return (a * s_int) >> (w - m);
                    //return 2;

                case HashType::ALG:
                    return int(size*(alfa*s_int*2 - int(alfa*s_int*2)));

                case HashType::FIB:
                    // const double phi = 1.6180339887; // golden ratio
                    // const size_t a = static_cast<size_t>(pow(2, 64) / phi); // 64-bit multiplier
                    // const size_t w = 64; // fixed machine word size in bits
                    return (a_m * s_int) >> (w - (size_t) log2(size));
            }

            // it should not go here
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


        /**
         * 
         *      IMPLEMENTED
         * 
        */

        // temporarily use another type of hash
        // size_t hash(std::string& key, HashType other_type){
        //     HashType temp = this->hash_type;
        //     this->hash_type = other_type;

        //     size_t index = hash(key);
        //     this->hash_type = temp;
        //     return index;
        // }

        size_t get_size(){
            return size;
        }
};

#endif