//
// Created by memonick on 09/04/2016.
//

#include "../../headers/AST/AST_var_declaration_node.h"

/**
 * Initialize the node with the given level
 * level            the level of the node
 */
AST_statement_node::AST_statement_node(unsigned level) {
    this->set_level(level);
}

/**
 * Delete the node
 */
AST_statement_node::~AST_statement_node() {
    delete this->child;
}

/**
 * Set the child of this node
 */
void AST_statement_node::set_child(AST_statement_node * child) {
    this->child = child;
}

/**
 * Get the child of this node
 */
AST_statement_node * AST_statement_node::get_child() {
    return this->child;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_statement_node::accept(visitor * v) {
    v->visit(this);
}

/**
 * Set the level of the node, recursively changing the level of its children
 * level            the new level of the node
 */
void AST_statement_node::set_level(unsigned level) {
    this->level = level;
    if (this->child != nullptr) {
        this->child->set_level(level + 1);
    }
}
