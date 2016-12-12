//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_RETURN_NODE_H
#define LEXER_AST_RETURN_NODE_H

#include "AST_node.h"
#include "../visitor/visitor.h"
#include "AST_statement_node.h"
#include <string>

class AST_return_node : public virtual AST_statement_node {

public:
    AST_return_node(unsigned level);
    virtual ~AST_return_node();

    void set_expression(AST_node * expression_node);

    AST_node * get_expression();

    virtual void accept(visitor * v);
    virtual void set_level(unsigned level);

private:
    AST_node * expression = nullptr;

};

#endif //LEXER_AST_RETURN_NODE_H
