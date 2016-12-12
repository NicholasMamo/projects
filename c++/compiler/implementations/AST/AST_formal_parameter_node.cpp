//
// Created by memonick on 12/04/2016.
//

#include "../../headers/AST/AST_formal_parameter_node.h"

/**
 * Initialize the node with the given level
 * level            the level of the node
 */
AST_formal_parameter_node::AST_formal_parameter_node(unsigned level) {
    this->level = level;
}

/**
 * Delete the node
 */
AST_formal_parameter_node::~AST_formal_parameter_node() {
    delete this->type;
    delete this->identifier;
}

/**
 * Set the identifier of the node
 * identifier_node  the identifier of the node
 */
void AST_formal_parameter_node::set_identifier(AST_identifier_node * identifier_node) {
    this->identifier = identifier_node;
}

/**
 * Set the type of the node
 * type_node  the type of the node
 */
void AST_formal_parameter_node::set_type(AST_type_node * type_node) {
    this->type = type_node;
}

/**
 * Get the identifier of the node
 * return           the identifier of the node
 */
AST_identifier_node * AST_formal_parameter_node::get_identifier() {
    return this->identifier;
}

/**
 * Get the type of the node
 * return           the type of the node
 */
AST_type_node * AST_formal_parameter_node::get_type() {
    return this->type;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_formal_parameter_node::accept(visitor * v) {
    v->visit(this);
}

/**
 * Set the level of the node, recursively changing the level of its children
 * level            the new level of the node
 */
void AST_formal_parameter_node::set_level(unsigned level) {
    this->level = level;
    if (this->identifier != nullptr) {
        this->identifier->set_level(level + 1);
    }
    if (this->type != nullptr) {
        this->type->set_level(level + 1);
    }
}
