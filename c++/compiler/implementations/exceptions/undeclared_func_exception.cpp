//
// Created by memonick on 20/04/2016.
//

#include "../../headers/exceptions/undeclared_func_exception.h"

/**
 * Initialize the exception with the given function name
 */
undeclared_func_exception::undeclared_func_exception(string name) {
    this->name = name;
}

/**
 * Get the textual representation of the exception
 */
string undeclared_func_exception::to_string() {
    return "using undeclared function " + this->name;
}