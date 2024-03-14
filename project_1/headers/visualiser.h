#ifndef VISUALISER_H
#define VISUALISER_H

#include <ncurses.h>
#include <string>
#include <chrono>
#include <thread>
#include <locale>
#include <menu.h>

// colors
#define BACKGROUND COLOR_BLACK

// window params
#define PROJECT_INFO_WIDTH 50
#define PROJECT_INFO_HEIGH 8
#define MENU_WIDTH 20
#define MENU_HEIGH 20
#define INFO_WIDTH 30
#define INFO_HEIGHT 20
#define PADDING_X 10
#define PADDING_Y 3
#define HZ 20

// menu params
#define DEFAULT_SELECTED_ITEM 0


class Visualiser{
    private:
        // components, etc...
        WINDOW* project_info_win;
        WINDOW* menu_win;
        WINDOW* info_win; 

        Menu* current_menu;
        uint8_t current_item;

        // threads handling
        std::thread visual_thread;
        bool should_run;

        // time handling
        std::chrono::high_resolution_clock::time_point program_start_time;
        
        // main loop fuctions
        void init();
        void update_screen();

        // helper functions for writing data to screen using mvwprintw()
        void write_project_info();
        void write_menu();
        void write_content();

        // menu functions
        void render_menu();
        void clear_box(WINDOW* win);

        // info functions
        size_t get_runtime();

        // write a function to switch beetwen pages

    public:
        Visualiser();
        ~Visualiser();
};

#include <visualiser.cpp>
#endif