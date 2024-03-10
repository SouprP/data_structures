#include <thread>
#include <iostream>
#include <headers/visualiser.h>

int main(int argc, char** argv){
    // visualiser / menu boot
    // then based on what we choose we create a thread 
    // which enables us to test data structures
    //std::cout << "test";
    Visualiser *visuals = new Visualiser();

    getch();
    delete visuals;

    return 0;
}