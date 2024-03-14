#ifndef MENU_H
#define MENU_H

#include <headers/menu_item.h>
#include <iostream>
#include <vector>

class Menu{
    private:
        Menu* parent_menu;
        size_t items_size;
        std::vector<MenuItem> items;

    public:
        //void on_select();
        size_t get_size() { return items.size(); };
        std::vector<MenuItem> get_items() { return items; };

        Menu(Menu* parent, std::vector<MenuItem> items);
        //Menu(Menu* parent, size_t item_size);
        ~Menu();
};
#endif