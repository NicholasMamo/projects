//
// Created by memonick on 13/04/2016.
//

#include "../../headers/AST/AST_boolean_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * value            the value of the node
 */
AST_boolean_node::AST_boolean_node(unsigned level, string value) {
    this->set_level(level);
    if (value == "true") {
        this->set_bool_value(true);
    } else if (value == "false") {
        this->set_bool_value(false);
    }
}

/**
 * Delete the node
 */
AST_boolean_node::~AST_boolean_node() {}

/**
 * Set the boolean value of the node
 */
void AST_boolean_node::set_bool_value(bool bool_value) {
    this->bool_value = bool_value;
}

/**
 * Get the value of the node
 * return           the value of the node
 */
bool AST_boolean_node::get_bool_value() {
    return this->bool_value;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_boolean_node::accept(visitor * v) {
    v->visit(this);
}
