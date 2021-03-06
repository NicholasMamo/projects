//
// Created by memonick on 09/04/2016.
//

#include "../../headers/AST/AST_type_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 * type             the type of the node
 */
AST_type_node::AST_type_node(unsigned level, string type) {
    this->set_level(level);
    this->type = type;
}

/**
 * Delete the node
 */
AST_type_node::~AST_type_node() {}

void AST_type_node::set_type(string type) {
    this->type = type;
}

/**
 * Get the type of the identifier
 * return           the type of the identifier
 */
string AST_type_node::get_type() {
    return this->type;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_type_node::accept(visitor * v) {
    v->visit(this);
}
