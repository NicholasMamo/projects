//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_BOOLEAN_TERM_NODE_H
#define LEXER_AST_BOOLEAN_TERM_NODE_H

class AST_term_node;

#include "AST_term_node.h"
#include "../visitor/visitor.h"

class AST_boolean_term_node : public virtual AST_term_node {

    public:
        AST_boolean_term_node(unsigned level, string value);

        virtual void accept(visitor * v);
};

#endif //LEXER_AST_BOOLEAN_TERM_NODE_H
