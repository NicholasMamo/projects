//
// Created by memonick on 19/04/2016.
//

#include "../../headers/exceptions/incompatible_types_exception.h"

/**
 * Initialize the exception with one variable type
 * type_1           the variable type encountered
 */
incompatible_types_exception::incompatible_types_exception(var_type type_1) {
    this->type_1 = type_1;
    this->has_type_1 = true;
}

/**
 * Initialize the exception with two variable types
 * type_1           the first variable type encountered
 * type_2           the second variable type encountered
 */
incompatible_types_exception::incompatible_types_exception(var_type type_1, var_type type_2) {
    this->type_1 = type_1;
    this->has_type_1 = true;
    this->type_2 = type_2;
    this->has_type_2 = true;
}

string incompatible_types_exception::to_string() {
    string s = "incompatible types; found ";
    if (this->has_type_1) {
        s += symbol::type_to_string(this->type_1);
    }

    if (this->has_type_2) {
        s += ", required ";
        s += symbol::type_to_string(this->type_2);
    }

    return s;
}