//
// Created by memonick on 11/04/2016.
//

#include "../../headers/exceptions/unexpected_input.h"

/**
 * Initialize the parse_exception with the given input
 * found            the input that was found
 * required         the input that was required
 */
unexpected_input::unexpected_input(string found, unsigned line) : parse_exception(line) {
    this->found = found;
}

/**
 * Initialize the parse_exception with the given input
 * found            the input that was found
 * required         the input that was required
 */
unexpected_input::unexpected_input(string found, string required, unsigned line) : parse_exception(line) {
    this->found = found;
}

/**
 * Get the textual representation of the parse_exception
 * return           the textual representation of the parse_exception
 */
string unexpected_input::to_string() {
    string s = "";
    s += "Unexpected input: found ";
    s += this->found;
    if (required != "") {
        s += ", required ";
        s += this->required;
    }
    s += " on line ";
    s += std::to_string(this->line) + "\n";
    return s;
}