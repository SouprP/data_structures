#ifndef GENERATOR_HPP_
#define GENERATOR_HPP_

#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>

// alphabet for ASCII
#define RAND_GEN_MAX std::pow(2, 8)
#define ALPHABET_MIN -25
#define ALPHABET_MAX 90
#define CAPITAL_ADD 32
#define MAX_KEY_LENGTH std::pow(256, 2)
#define MIN_KEY_LENGTH 1

class Generator{
    public:
        int random(size_t low, size_t high){
            return rand() % (high - low) + low;
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

        std::vector<std::string> generate_string(size_t size){
            std::vector<std::string> buffer;

            for(size_t i = 0; i < size; i++){
                int length = random(MIN_KEY_LENGTH, MAX_KEY_LENGTH);
                //std::stringstream buffer1;
                std::string s_buffer;
                s_buffer.reserve(length);

                while(s_buffer.size() < length){
                    int capital = random(0, 2);
                    //std::cout << capital << std::endl;
                    int c = random(65, 90 + 1);
                    //std::cout << c << std::endl;

                    if(capital){
                        s_buffer += char(c);
                        continue;
                    }

                    s_buffer += char(c + CAPITAL_ADD);
                }

                buffer.push_back(s_buffer);
            }

            return buffer;
        }
 
        Generator(){
            srand(time(NULL));
        };
};


#endif