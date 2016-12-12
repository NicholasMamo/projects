//
// Created by memonick on 20/04/2016.
//

#include "../../headers/exceptions/incorrect_parameter_count.h"

/**
 * Initialize the exception with the found and required parameter counts
 * found            the number of parameters found
 * required         the number of parameters required
 */
incorrect_parameter_count::incorrect_parameter_count(unsigned long found, unsigned long required) {
    this->found = found;
    this->required = required;
}

/**
 * Get the textual representation of the exception
 */
string incorrect_parameter_count::to_string() {
    return "incorrect number of parameters; found " + std::to_string(this->found) + ", required " + std::to_string(this->required);
}