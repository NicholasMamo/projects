//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_EXPRESSION_NODE_H
#define LEXER_AST_EXPRESSION_NODE_H

#include "AST_binary_expression_node.h"

class visitor;

class AST_expression_node : public virtual AST_binary_expression_node {

    public:
        AST_expression_node(unsigned level, string value);

        virtual void accept(visitor * v);

};

#include "../visitor/visitor.h"

#endif //LEXER_AST_EXPRESSION_NODE_H
