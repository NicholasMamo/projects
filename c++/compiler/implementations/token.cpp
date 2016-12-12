//
// Created by memonick on 29/02/2016.
//

#include <iostream>
#include <string>

#include "../headers/token.h"

using namespace std;

/**
 * Create a new empty token
 */
token::token() {
    token(TOK_unknown, "");
}

/**
 * Create a token with the given name and attribute
 * token_name       the name of the token
 * token_attribute  the attribute of the token
 */
token::token(name token_name, string token_attribute) {
    this->token_name = token_name;
    this->token_attribute = token_attribute;
}

/**
 * Set the attribute of the token
 * token_attribute  the attribute of the token
 */
void token::set_attribute(string token_attribute) {
    this->token_attribute = token_attribute;
}

/**
 * Set the line number of the token
 * token_line the line number of the token
 */
void token::set_line(unsigned token_line) {
    this->token_line = token_line;
}

/**
 * Set the name of the token
 * token_name       the name of the token
 */
void token::set_name(name token_name) {
    this->token_name = token_name;
}

/**
 * Get the attribute of the token
 * return           the attribute of the token
 */
string token::get_attribute() {
    return this->token_attribute;
}

/**
 * Get the line number where the token appears
 * return           the line number where the token appears
 */
unsigned token::get_line() {
    return this->token_line;
}

/**
 * Get the name of the token
 * return           the name of the token
 */
name token::get_name() {
    return this->token_name;
}

/**
 * Get the textual representation of the given name
 * n                the name for who the representation will be returned
 * return           the textual representation of the given name
 */
string token::token_to_string(name n) {
    switch(n) {
        case TOK_bracket:
            return "TOK_bracket";
        case TOK_comma:
            return "TOK_comma";
        case TOK_eos:
            return "TOK_eos";
        case TOK_string_literal:
            return "TOK_string_literal";
        case TOK_int_number:
            return "TOK_int_number";
        case TOK_real_number:
            return "TOK_real_number";
        case TOK_arithmetic:
            return "TOK_arithmetic";
        case TOK_assignment:
            return "TOK_assignment";
        case TOK_simple_assignment:
            return "TOK_simple_assignment";
        case TOK_boolean:
            return "TOK_boolean";
        case TOK_identifier:
            return "TOK_identifier";
        case TOK_keyword:
            return "TOK_keyword";
        case TOK_eof:
            return "TOK_eof";
        case TOK_bool_literal:
            return "TOK_bool_literal";
        case TOK_var_type:
            return "TOK_var_type";
        case TOK_string_start:
            return "TOK_string_start";
        case TOK_colon:
            return "TOK_colon";
        case TOK_string:
            return "TOK_string";
        case TOK_unknown:
            return "TOK_unknown";
        default:
            return "";
    }
}

/**
 * Get the textual representation of the token
 * return           the textual representation of the token
 */
string token::token_to_string() {
    return token::token_to_string(this->token_name);
}

string token::to_string() {
    string s = '<' + this->token_to_string() + ", " + this->token_attribute + '>';
    return s;
}

