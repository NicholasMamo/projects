//
// Created by memonick on 19/04/2016.
//

#include "../../headers/symbol_table/symbol_func.h"

/**
 * Initialize the variable with the given name
 * name             the name of the variable
 */
symbol_func::symbol_func(string name): symbol(name) {}

/**
 * Set the body of the function
 * value            the body of the function
 */
void symbol_func::set_body(AST_block_node * body) {
    this->body = body;
}

/**
 * Set the parameters of the function
 * value            the parameters of the function
 */
void symbol_func::set_parameters(AST_formal_parameters_node * parameters) {
    this->parameters = parameters;
}


/**
 * Get the body of the function
 * return            the body of the function
 */
AST_block_node * symbol_func::get_body() {
    return this->body;
}

/**
 * Get the parameters of the function
 * return            the parameters of the function
 */
AST_formal_parameters_node * symbol_func::get_parameters() {
    return this->parameters;
}

/**
 * Get the textual representation of the variable
 * return           the textual representation of the variable
 */
string symbol_func::to_string() {
    string s = this->name;
    s += "(" + std::to_string(this->parameters->get_formal_parameters().size()) + ")";
    s += ": ";
    s += symbol_func::type_to_string(this->type);
    return s;
}