#ifndef VISUALISER_H
#define VISUALISER_H

#include <ncurses.h>
#include <string>
#include <chrono>
#include <thread>
#include <locale>

// colors
#define BACKGROUND COLOR_BLACK

// window params
#define PROJECT_INFO_WIDTH 50
#define PROJECT_INFO_HEIGH 8
#define MENU_WIDTH 20
#define MENU_HEIGH 20
//#define WIN_HEIGHT 30
//#define PADDING_X 10
//#define PADDING_Y 3
#define HZ 20

class Visualiser{
    private:
        // components, etc...
        WINDOW* project_info_win;
        WINDOW* menu_win;
        WINDOW* info_win; 

        // threads handling
        std::thread visual_thread;
        bool should_run;

        // time handling
        std::chrono::high_resolution_clock::time_point program_start_time;
        
        // functions
        void init();
        void update_screen();

        // helper functions for writing data to screen using mvwprintw()
        void write_project_info();
        void write_menu();
        void write_content();

        size_t get_runtime();

        // write a function to switch beetwen pages

    public:
        Visualiser();
        ~Visualiser();
};
#endif