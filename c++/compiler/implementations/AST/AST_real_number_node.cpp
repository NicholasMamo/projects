//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_real_number_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * value            the value of the node
 */
AST_real_number_node::AST_real_number_node(int level, string value) : AST_number_node(level, value) {
    this->real_value = stod(value);
}

/**
 * Set the real value of the node
 * real_value       the new real value of the node
 */
void AST_real_number_node::set_real_value(double real_value) {
    this->real_value = real_value;
}

/**
 * Get the real value of the node
 * return           the real value of the node
 */
double AST_real_number_node::get_real_value() {
    return this->real_value;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_real_number_node::accept(visitor * v) {
    v->visit(this);
}
