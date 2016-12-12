//
// Created by memonick on 20/04/2016.
//

#include "../../headers/exceptions/missing_return_exception.h"

/**
 * Initialize the exception with the given variable type
 * type             the return type of the function
 */
missing_return_exception::missing_return_exception(var_type type) {
    this->type = type;
}

/**
 * Get the textual representation of the exception
 * return           the textual representation of the exception
 */
string missing_return_exception::to_string() {
    return "missing return statement for function returning " + symbol::type_to_string(this->type);
}