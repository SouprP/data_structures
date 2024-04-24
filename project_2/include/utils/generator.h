#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>
#include <random>
#include <chrono>

// alphabet for ASCII
#define RAND_GEN_MAX std::pow(2, 8)
#define ALPHABET_MIN -25
#define ALPHABET_MAX 90
#define CAPITAL_ADD 32

class Generator{
    public:
        int random(size_t low, size_t high){
            return rand() % high + low;
        };

        std::vector<int> generate_int(size_t size){
            std::vector<int> buffer;

            int done = 0;
            while(done < size){
                buffer.push_back(random(0, RAND_GEN_MAX));
                done++;
            }

            return buffer;
        };

        Generator(){
            srand(time(NULL));
        };
};


#endif