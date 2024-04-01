#include <utils/file.h>
#include <utils/menu.h>

#include <structures/array_list.h>
#include <structures/linked_list.h>
#include <structures/linked_list_tail.h>
#include <structures/double_linked_list.h>

#include <chrono>

#define DATA_SET_1 "data_10k.txt"
#define DATA_SET_2 "data_100k.txt"
#define DATA_SET_3 "ddata_500k.txt"
#define DATA_SET_4 "data_1m.txt"


int main(){
    //FileIO<int> file;
    //data = file.read(DATA_SET_1);    
    Menu menu;
    menu.render();
    //test_array();

    return 0;
}


