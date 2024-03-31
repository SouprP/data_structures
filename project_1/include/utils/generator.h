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
    private:
        std::chrono::high_resolution_clock::time_point program_seed;

        int random(size_t low, size_t high){
            //auto time_dur = std::chrono::duration<double>(
            //std::chrono::high_resolution_clock::now() - program_seed);
    
            //auto time_conv = std::chrono::duration_cast<std::chrono::nanoseconds>(time_dur);
            //size_t dur = time_conv.count();
            //srand(dur);

            //size_t dur = std::chrono::nanoseconds::count(current_time);
            return rand() % high + low;
        };

    public:
        std::vector<int> generate_int(size_t size){
            std::vector<int> buffer;

            int done = 0;
            while(done < size){
                //std::cout << "generated " << done << std::endl;
                buffer.push_back(random(0, RAND_GEN_MAX));
                done++;
            }

            return buffer;
        };
        //std::vector<std::string> generate_string(size_t size);
        //std::vector<char> generate_char(size_t size);

        Generator(std::chrono::high_resolution_clock::time_point program_seed){
            this->program_seed = program_seed;
        };

        Generator(){
            srand(time(NULL));
        };
};


#endif