//
// Created by memonick on 10/04/2016.
//

#ifndef LEXER_AST_TERM_NODE_H
#define LEXER_AST_TERM_NODE_H

#include "AST_binary_expression_node.h"

class visitor;

class AST_term_node : public virtual AST_binary_expression_node {

    public:
        AST_term_node(unsigned level, string value);

        virtual void accept(visitor * v) = 0;

};

#include "../visitor/visitor.h"

#endif //LEXER_AST_TERM_NODE_H
