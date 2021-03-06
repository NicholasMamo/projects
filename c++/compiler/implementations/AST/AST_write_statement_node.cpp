//
// Created by memonick on 09/04/2016.
//

#include "../../headers/AST/AST_write_statement_node.h"

/**
 * Initialize the node with the given level
 * level            the level of the node
 */
AST_write_statement_node::AST_write_statement_node(unsigned level) : AST_statement_node(level) {
    this->level = level;
}

/**
 * Delete the node
 */
AST_write_statement_node::~AST_write_statement_node() {
    delete this->expression;
}

/**
 * Set the expression of the node
 * expression_node  the expression of the node
 */
void AST_write_statement_node::set_expression(AST_node * expression_node) {
    this->expression = expression_node;
}

/**
 * Get the expression of the node
 * return           the expression of the node
 */
AST_node * AST_write_statement_node::get_expression() {
    return this->expression;
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_write_statement_node::accept(visitor * v) {
    v->visit(this);
}

/**
 * Set the level of the node, recursively changing the level of its children
 * level            the new level of the node
 */
void AST_write_statement_node::set_level(unsigned level) {
    this->level = level;
    if (this->expression != nullptr) {
        this->expression->set_level(level + 1);
    }
}
