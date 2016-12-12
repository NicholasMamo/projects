//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_string_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * value            the value of the node
 */
AST_string_node::AST_string_node(unsigned level, string value) {
    this->set_level(level);
    this->value = value;
}

/**
 * Delete the node
 */
AST_string_node::~AST_string_node() {}

void AST_string_node::set_value(string value) {
    this->value = value;
}

/**
 * Get the value of the node
 * return           the value of the node
 */
string AST_string_node::get_value() {
    return this->value;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_string_node::accept(visitor * v) {
    v->visit(this);
}
