//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_SYMBOL_VAR_H
#define LEXER_SYMBOL_VAR_H

#include "../exceptions/incompatible_types_exception.h"
#include "symbol.h"

#include <iostream>
#include <string>

using namespace std;

class symbol_var : public symbol {

    public:
        symbol_var(string name);
        symbol_var(string name, int value);
        symbol_var(string name, double value);
        symbol_var(string name, bool value);
        symbol_var(string name, string value);

        symbol_var operator+(symbol_var& other);
        symbol_var operator-(symbol_var& other);
        symbol_var operator*(symbol_var& other);
        symbol_var operator/(symbol_var& other);
        symbol_var operator<(symbol_var& other);
        symbol_var operator<=(symbol_var& other);
        symbol_var operator>(symbol_var& other);
        symbol_var operator>=(symbol_var& other);
        symbol_var operator==(symbol_var& other);
        symbol_var operator!=(symbol_var& other);
        symbol_var operator||(symbol_var& other);
        symbol_var operator&&(symbol_var& other);
        symbol_var operator!();

        void set_value(int value);
        void set_value(double value);
        void set_value(bool value);
        void set_value(string value);

        int get_int_value();
        double get_real_value();
        bool get_bool_value();
        string get_string_value();

        string value_to_string();
        virtual string to_string();

        static symbol_var * clone(symbol_var var);
        static bool is_number_type(symbol_var var);
        static var_type reduce(symbol_var var_1, symbol_var var_2);

    private:
        var_value value {0};

};



#endif //LEXER_SYMBOL_VAR_H
