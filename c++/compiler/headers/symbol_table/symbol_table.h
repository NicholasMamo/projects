//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_SYMBOL_TABLE_H
#define LEXER_SYMBOL_TABLE_H

#include "../AST/AST_block_node.h"
#include "../AST/AST_formal_parameters_node.h"
#include "../AST/AST_func_declaration_node.h"
#include "../exceptions/undeclared_func_exception.h"
#include "../stack.h"

#include "symbol_var.h"
#include "symbol_func.h"

#include <string>
#include <vector>

using namespace std;

class symbol_table {

    public:
        symbol_table();

        void add_symbol(string s_name);
        void add_symbol(symbol_var var);
        void add_symbol(AST_func_declaration_node * function);

        void set_type(string s_name, var_type type);
        void set_value(string s_name, int value);
        void set_value(string s_name, double value);
        void set_value(string s_name, bool value);
        void set_value(string s_name, string value);

        symbol_func * get_function(string s_name);
        symbol_var * get_variable(string s_name);
        var_type get_function_type(string s_name);
        AST_formal_parameters_node * get_parameters(string s_name);
        string get_string_value(string s_name);
        var_type get_type(string s_name);
        var_value get_value(string s_name);
        bool remove(string s_name);

        bool is_in_scope(string s_name);
        bool is_function(string s_name);
        bool is_int(string s_name);
        bool is_real(string s_name);
        bool is_bool(string s_name);
        bool is_string(string s_name);

        void clear_replaced();
        bool is_replaced(string s_name);
        void set_replaced(symbol_var var);

        static symbol_table * clone(const symbol_table * other);
        string to_string();

    private:
        vector<symbol_func *> functions;
        vector<symbol_var *> variables;
        vector<symbol_var> replaced_variables;

};

#endif //LEXER_SYMBOL_TABLE_H