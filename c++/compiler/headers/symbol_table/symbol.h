//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_SYMBOL_H
#define LEXER_SYMBOL_H

#include <iostream>
#include <string>

using namespace std;

enum var_type {type_string, type_int, type_real, type_bool, type_other};

union var_value {
    int i;
    double d;
    bool b;
    ~var_value() {};
};

class symbol {

    public:
        symbol(string name);

        void set_name(string name);
        void set_type(var_type type);

        string get_name();
        var_type get_type();

        virtual string to_string() = 0;

        static string type_to_string(var_type type);
        static var_type string_to_type(string type);

    protected:
        string name = "";
        var_type type = type_other;
        string s = "";

};

#endif //LEXER_SYMBOL_H
