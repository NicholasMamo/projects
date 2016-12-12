//
// Created by memonick on 12/04/2016.
//

#include "../../headers/AST/AST_func_declaration_node.h"

/**
 * Create the node with the given level and value
 * level            the level of the node
 */
AST_func_declaration_node::AST_func_declaration_node(unsigned level) : AST_statement_node(level) {
    this->set_level(level);
    this->formal_parameters = new AST_formal_parameters_node(0);
}

/**
 * Delete the node
 */
AST_func_declaration_node::~AST_func_declaration_node() {
    delete this->formal_parameters;
    delete this->type;
    delete this->identifier;
    delete this->block;
}

/**
 * Set the block of the function
 * block_node       the block of the function
 */
void AST_func_declaration_node::set_block(AST_block_node * block_node) {
    this->block = block_node;
}

/**
 * Set the identifier of the function
 * identifier_node       the identifier of the function
 */
void AST_func_declaration_node::set_identifier(AST_identifier_node * identifier_node) {
    this->identifier = identifier_node;
}

/**
 * Set the return type of the function
 * type_node       the return type of the function
 */
void AST_func_declaration_node::set_type(AST_type_node * type_node) {
    this->type = type_node;
}

/**
 * Add a formal parameter to the program
 * formal_parameters the formal parameters to add to the program
 */
void AST_func_declaration_node::set_formal_parameters(AST_formal_parameters_node * formal_parameters) {
    this->formal_parameters = formal_parameters;
}

/**
 * Get the block of the function
 * return           the block of the function
 */
AST_block_node * AST_func_declaration_node::get_block() {
    return this->block;
}

/**
 * Get the identifier of the function
 * return           the identifier of the function
 */
AST_identifier_node * AST_func_declaration_node::get_identifier() {
    return this->identifier;
}

/**
 * Get the return type of the function
 * return           the return type of the function
 */
AST_type_node * AST_func_declaration_node::get_type() {
    return this->type;
}

/**
 * Get the formal parameters in the function
 * return           the list of statements in the program
 */
AST_formal_parameters_node * AST_func_declaration_node::get_formal_parameters() {
    return this->formal_parameters;
}

/**
 * Set the level of the node, and any children it may have, to the one given
 * level            the new level of the node
 */
void AST_func_declaration_node::set_level(unsigned level) {
    this->level = level;
    if (this->formal_parameters != nullptr) {
        this->formal_parameters->set_level(level + 1);
    }
    if (this->identifier != nullptr) {
        this->identifier->set_level(level + 1);
    }
    if (this->type != nullptr) {
        this->type->set_level(level + 1);
    }
    if (this->block != nullptr) {
        this->block->set_level(level + 1);
    }
}

/**
 * Allow the given visitor to visit this node
 * v                the visitor that will visit this node
 */
void AST_func_declaration_node::accept(visitor * v) {
    v->visit(this);
}
