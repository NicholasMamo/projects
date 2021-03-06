//
// Created by memonick on 09/04/2016.
//

#ifndef LEXER_AST_ASSIGNMENT_NODE_H
#define LEXER_AST_ASSIGNMENT_NODE_H

#include "AST_identifier_node.h"
#include "AST_node.h"
#include "AST_statement_node.h"
#include <string>

class AST_assignment_node : public virtual AST_statement_node {

public:
    AST_assignment_node(unsigned level);
    virtual ~AST_assignment_node();

    void set_expression(AST_node * expression_node);
    void set_identifier(AST_identifier_node * identifier_node);

    AST_node * get_expression();
    AST_identifier_node * get_identifier();

    virtual void accept(visitor * v);
    virtual void set_level(unsigned level);

private:
    AST_identifier_node * identifier = nullptr;
    AST_node * expression = nullptr;

};

#endif //LEXER_AST_ASSIGNMENT_NODE_H
