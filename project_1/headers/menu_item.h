#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <string>

// this code is from stack overflow, i have now goddam idea how
// it works, but i know how to use it
// OT => Object Type
// RT => Return Type
// A ... => Arguments
template<typename OT, typename RT, typename ... A>
struct lambda_expression {
    OT _object;
    RT(OT::*_function)(A...)const;

    lambda_expression(const OT & object)
            : _object(object), _function(&decltype(_object)::operator()) {}

    RT operator() (A ... args) const {
    return (_object.*_function)(args...);
}

class MenuItem{
    private:
        std::string item_name;
        lambda_expression
    
    public:
        void on_select();
        
        MenuItem(std::string item_name, lambda_expression func);
};
};

#endif