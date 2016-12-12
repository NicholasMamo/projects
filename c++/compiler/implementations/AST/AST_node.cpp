//
// Created by memonick on 15/03/2016.
//

#include "../../headers/AST/AST_node.h"

/**
 * Set the level of the node
 * level            the level of the node
 */
void AST_node::set_level(unsigned level) {
    this->level = level;
}

/**
 * Get the level of the node
 * return           the level of the node
 */
unsigned AST_node::get_level() {
    return this->level;
}