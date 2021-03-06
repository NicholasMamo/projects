//
// Created by memonick on 09/04/2016.
//

#include "../../headers/AST/AST_identifier_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * name             the name of the identifier
 */
AST_identifier_node::AST_identifier_node(unsigned level, string name) {
    this->set_level(level);
    this->name = name;
}

/**
 * Delete the node
 */
AST_identifier_node::~AST_identifier_node() {}

void AST_identifier_node::set_name(string name) {
    this->name = name;
}

/**
 * Get the name of the identifier
 * return           the name of the identifier
 */
string AST_identifier_node::get_name() {
    return this->name;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_identifier_node::accept(visitor * v) {
    v->visit(this);
}
