//
// Created by memonick on 20/04/2016.
//

#include "../../headers/exceptions/undeclared_var_exception.h"

/**
 * Initialize the exception with the given variable name
 */
undeclared_var_exception::undeclared_var_exception(string name) {
    this->name = name;
}

/**
 * Get the textual representation of the exception
 */
string undeclared_var_exception::to_string() {
    return "using undeclared variable " + this->name;
}
