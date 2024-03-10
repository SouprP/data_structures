#include <headers/visualiser.h>

#include <iostream>
Visualiser::Visualiser(){
    init();

    //std::cout << "test";
    // start the loop
    should_run = true;
    visual_thread = std::thread(&Visualiser::update_screen, this);
}

Visualiser::~Visualiser(){
    should_run = false;
    visual_thread.join();

    delwin(project_info_win);
    endwin();
}

void Visualiser::init(){
    setlocale(LC_ALL, "");

    // screen initialization
    initscr();
    curs_set(0);

    // setup of windows
    // args - newwin(height of window, width of win, 
    // Y cord where to place, X cord where to place)
    // newwin(HEIGH, WIDTH, X, Y)
    project_info_win = newwin(PROJECT_INFO_HEIGH, PROJECT_INFO_WIDTH, 0, 0);
    menu_win = newwin(MENU_HEIGH, MENU_WIDTH, PROJECT_INFO_HEIGH, 0);
    refresh();

    box(project_info_win, 0, 0);
    box(menu_win, 0, 0);
    wrefresh(project_info_win);
    wrefresh(menu_win);

    noecho(); // dont print getch() output
    attron(A_BOLD); // make the text BOLD

    // init of color pairs for later use
    // BACKGROUND is defined ./headers/visualiser.h
    // init_pair(pair number, foreground color, background color)
    start_color();
    init_pair(1, COLOR_WHITE, BACKGROUND); // default colors

    program_start_time = std::chrono::high_resolution_clock::now();
}

/**
 * This function writes everything to the screen and handles refresh rate as well as the self recurversing loop.
*/
void Visualiser::update_screen(){
    write_project_info();

    // if we dont use sleep_for the this thread, it will throw Segmented Fault exception
    // you could say it makes it so that there is a refresh rate
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / HZ));

    // check if Visualiser object was deleted and told to stop running
    if(!should_run)
        return;

    update_screen();
}

/**
 * Gets program runtime in seconds.
 * 
 * @return seconds as size_t as they are going to be >= 0.
*/
size_t Visualiser::get_runtime(){
    // gets the diff beetwen 2 times
    auto time = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() 
    - program_start_time);

    // converts time to miliseconds and returns it devided by 1000
    auto time_conv = std::chrono::duration_cast<std::chrono::milliseconds>(time);
    return time_conv.count() / 1000;
}

/**
 * Writes info about the programm and other stuff to the screen.
*/
void Visualiser::write_project_info(){
    int x = getmaxx(project_info_win);
    int y getmaxy(project_info_win);

    std::string prog_name = "Sorting Algorithms";
    std::string name_1 = "Igor Potyrala - 272518";
    std::string name_2 = "Adam Sidorowicz - xxxxxx";
    std::string freq = "Frequency:: %dHz";
    std::string time = "Time elapsed: %ds";

    mvwprintw(project_info_win, 1, (int) (x / 2) - prog_name.length() / 2, prog_name.c_str());
    mvwprintw(project_info_win, 2, (int) (x / 2) - name_1.length() / 2, name_1.c_str());
    mvwprintw(project_info_win, 3, (int) (x / 2) - name_2.length() / 2, name_2.c_str());

    mvwprintw(project_info_win, 5, (int) (x / 2) - freq.length() / 2, freq.c_str(), HZ);
    mvwprintw(project_info_win, 6, (int) (x / 2) - time.length() / 2, time.c_str(), get_runtime());
    wrefresh(project_info_win);
}

void Visualiser::write_menu(){
    int x = getmaxx(menu_win);
    int y getmaxy(menu_win);
}

