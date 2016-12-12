//
// Created by memonick on 11/04/2016.
//

#include "../../headers/exceptions/parse_exception.h"

/**
 * Initialize the parse_exception with the given line number
 */
parse_exception::parse_exception(unsigned line) {
    this->line = line;
}

/**
 * Set the line number of the parse_exception
 * line             the line number where the parse_exception occurred
 */
void parse_exception::set_line(unsigned line) {
    this->line = line;
}

/**
 * Get the line number of the parse_exception
 * return           the line number where the parse_exception occurred
 */
unsigned parse_exception::get_line() {
    return this->line;
}