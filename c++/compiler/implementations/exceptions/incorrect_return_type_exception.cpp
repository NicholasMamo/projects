//
// Created by memonick on 20/04/2016.
//

#include "../../headers/exceptions/incorrect_return_type_exception.h"

/**
 * Initialize the exception with the given variable type
 * found            the type returned by the function
 * required         the type that the function should return
 */
incorrect_return_type_exception::incorrect_return_type_exception(var_type found, var_type required) {
    this->found = found;
    this->required = required;
}

/**
 * Get the textual representation of the exception
 * return           the textual representation of the exception
 */
string incorrect_return_type_exception::to_string() {
    return "incorrect return for function returning " + symbol::type_to_string(this->required) + "; found " + symbol::type_to_string(this->found);
}