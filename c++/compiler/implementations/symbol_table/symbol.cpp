//
// Created by memonick on 19/04/2016.
//

#include "../../headers/symbol_table/symbol.h"

symbol::symbol(string name) {
    this->set_name(name);
}

/**
 * Set the name of the variable
 * name             the name of the variable
 */
void symbol::set_name(string name) {
    this->name = name;
}

/**
 * Set the type of the variable
 * type             the type of the variable
 */
void symbol::set_type(var_type type) {
    this->type = type;
}

/**
 * Get the name of the variable
 * return           the name of the variable
 */
string symbol::get_name() {
    return this->name;
}

/**
 * Get the type of the variable
 * return           the type of the variable
 */
var_type symbol::get_type() {
    return this->type;
}

/**
 * Get the textual representation of the variable type
 * type         the variable type
 * return           the textual representation of the variable type
 */
string symbol::type_to_string(var_type type) {
    switch(type) {
        case type_string:
            return "string";
        case type_int:
            return "int";
        case type_real:
            return "real";
        case type_bool:
            return "bool";
        case type_other:
            return "other";
        default:
            return "unknown";
    }
}

/**
 * Get the textual representation of the variable type
 * type         the variable type
 * return           the textual representation of the variable type
 */
var_type symbol::string_to_type(string type) {
    if (type == "int" || type == "-" || type == "+") {
        return type_int;
    } else if (type == "real") {
        return type_real;
    } else if (type == "bool" || type == "not") {
        return type_bool;
    } else if (type == "string") {
        return type_string;
    } else {
        return type_other;
    }
}