//
// Created by memonick on 09/04/2016.
//

#include "../../headers/exceptions/unexpected_token.h"

/**
 * Initialize the parse_exception with the given token names
 * found            the token that was found
 */
unexpected_token::unexpected_token(name found, unsigned line) : parse_exception(line) {
    this->found = found;
    this->required = TOK_unknown;
}

/**
 * Initialize the parse_exception with the given token names
 * found            the token that was found
 * required         the token that was required
 */
unexpected_token::unexpected_token(name found, name required, unsigned line) : parse_exception(line) {
    this->found = found;
    this->required = required;
}

/**
 * Get the textual representation of the parse_exception
 * return           the textual representation of the parse_exception
 */
string unexpected_token::to_string() {
    string s = "";
    s += "Unexpected token: found ";
    s += token::token_to_string(this->found);
    if (this->required != TOK_unknown) {
        s += ", required ";
        s += token::token_to_string(this->required);
    }
    s += " on line ";
    s += std::to_string(this->line) + "\n";
    return s;
}