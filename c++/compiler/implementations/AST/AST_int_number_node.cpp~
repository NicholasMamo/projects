//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_int_number_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * value            the value of the node
 */
AST_int_number_node::AST_int_number_node(int level, string value) : AST_number_node(level, value) {
    this->int_value = stoi(value);
}

/**
 * Set the integral value of the node
 * int_value        the new integral value of the node
 */
void AST_int_number_node::set_int_value(int int_value) {
    this->int_value = int_value;
}

/**
 * Get the integral value of the node
 * return           the integral value of the node
 */
int AST_int_number_node::get_int_value() {
    return this->int_value;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_int_number_node::accept(visitor * v) {
    v->visit(this);
}
