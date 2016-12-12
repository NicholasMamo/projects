//
// Created by memonick on 29/02/2016.
//

#include <iostream>
#include <string>

using namespace std;

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

enum name {TOK_bracket, TOK_comma, TOK_eos, TOK_string_literal, TOK_string, TOK_int_number, TOK_real_number, TOK_boolean, TOK_boolean_operator, TOK_arithmetic, TOK_assignment, TOK_simple_assignment, TOK_identifier, TOK_keyword, TOK_eof, TOK_bool_literal, TOK_var_type, TOK_string_start, TOK_colon, TOK_unknown};

class token {

    public:
        token();
        token(name token_name, string token_attribute);

        void set_attribute(string token_attribute);
        void set_line(unsigned token_line);
        void set_name(name token_name);

        string get_attribute();
        unsigned get_line();
        name get_name();

        string token_to_string();
        string to_string();

        static string token_to_string(name n);

    private:
        unsigned token_line = 0;
        name token_name;
        string token_attribute;

};

#endif //LEXER_TOKEN_H
