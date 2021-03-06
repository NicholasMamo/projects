//
// Created by memonick on 11/04/2016.
//

#ifndef LEXER_AST_WHILE_NODE_H
#define LEXER_AST_WHILE_NODE_H

#include "AST_statement_node.h"
#include "AST_block_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_while_node : public virtual AST_statement_node {

public:
    AST_while_node(unsigned level);
    virtual ~AST_while_node();

    void set_expression(AST_node * expression_node);
    void set_block(AST_block_node * block_node);

    AST_node * get_expression();
    AST_block_node * get_block();

    virtual void accept(visitor * v);
    virtual void set_level(unsigned level);

private:
    AST_block_node * block = nullptr;
    AST_node * expression = nullptr;

};

#endif //LEXER_AST_WHILE_NODE_H
