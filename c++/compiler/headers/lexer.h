//
// Created by memonick on 01/03/2016.
//

#include <string>

#include "token.h"

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

class lexer {

    const string KEYWORDS[9] {"def", "return", "if", "else", "for", "set", "var", "while", "write"};
    const string TYPES[4] {"real", "int", "bool", "string"};
    const string BOOL_LITERAL[2] {"true", "false"};
    const string BOOL_OPERATOR[3] {"and", "or", "not"};

    public:
        lexer();
        lexer(string program);

        void set_program(string program);

        string get_program();

        token * get_next_token();
        token * peek();
        token * peek(int n);
        bool at_eof();
        void reset();

    private:
        unsigned line = 1;
        unsigned position = 0;
        string program = "";
        bool is_string = false;

        void fetch_attribute(token * t);
        void fetch_name(token * t);
        void postprocess(token * t);

        void skip();
        void skip_comments();

        bool is_alpha(char c);
        bool is_bracket(char c);
        bool is_comma(char c);
        bool is_eos(char c);
        bool is_number(char c);
        bool is_boolean_operator();
        bool is_operator(char c);
        bool is_assignment();
        bool is_simple_assignment();
        bool is_string_start(char c);
        bool is_colon(char c);
        bool is_identifier(char c);
        bool is_identifier(string string_literal);
        bool is_printable(char c);
        bool is_string_literal(string string_literal);

        string get_bracket();
        string get_comma();
        string get_eos();
        string get_number();
        string get_boolean_operator();
        string get_operator();
        string get_assignment();
        string get_simple_assignment();
        string get_string_start();
        string get_string();
        string get_colon();
        string get_identifier();

        void check_keyword(token * t);
        void check_real(token * t);

};

#endif //LEXER_LEXER_H
