//
// Created by memonick on 11/04/2016.
//

#include "../../headers/AST/AST_block_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 */
AST_block_node::AST_block_node(unsigned level) : AST_statement_node(level) {
    this->set_level(level);
}

/**
 * Delete the node
 */
AST_block_node::~AST_block_node() {
    for (unsigned i = 0; i < this->statements.size(); i++) {
        delete this->statements.at(i);
    }
}

/**
 * Add a statement to the program
 * statement        the statement to add to the program
 */
void AST_block_node::add_statement(AST_statement_node * statement) {
    statement->set_level(this->level + 1);
    this->statements.push_back(statement);
}

/**
 * Get the list of statements in the program
 * return           the list of statements in the program
 */
vector<AST_statement_node *> AST_block_node::get_statements() {
    return this->statements;
}

/**
 * Set the level of the node, and any children it may have, to the one given
 * level            the new level of the node
 */
void AST_block_node::set_level(unsigned level) {
    this->level = level;
    for (unsigned i = 0; i < this->statements.size(); i++) {
        this->statements.at(i)->set_level(level + 1);
    }
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_block_node::accept(visitor * v) {
    v->visit(this);
}
