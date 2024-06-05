#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <cstddef>
#include <string>
#include <vector>
#include <uuid/uuid.h>

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
        const int W = 1.0;

    protected:
        size_t size;

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

        size_t hash(std::string& key, HashType type){
            size_t s_int = 0;

            for(auto &k : key)
                s_int += int(k);
                //std::cout << k << std::endl;

            //std::cout << s_int << std::endl;

            switch(type){
                // hα(x) = x mod m
                case HashType::MOD:
                    return s_int % size;

                // hα(x) = ⌊(αx mod W )/(W /m)⌋
                case HashType::MOD_X:
                    // fix, doesnt work correctly
                    return int( ((int(alfa * s_int)) % W) 
                        / (W / size));
                    //return 2;

                case HashType::ALG:
                    return 3;

                case HashType::FIB:
                    return 4;
            }

            // it should not go here
            return 0;

        }

        size_t get_size(){
            return size;
        }
};

#endif