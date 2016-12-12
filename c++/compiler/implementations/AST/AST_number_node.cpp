//
// Created by memonick on 15/03/2016.
//

#include "../../headers/AST/AST_number_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * value            the value of the node
 */
AST_number_node::AST_number_node(unsigned level, string value) {
    this->set_level(level);
    this->value = value;
}

/**
 * Delete the node
 */
AST_number_node::~AST_number_node() {}

void AST_number_node::set_value(string value) {
    this->value = value;
}

/**
 * Get the value of the node
 * return           the value of the node
 */
string AST_number_node::get_value() {
    return this->value;
}