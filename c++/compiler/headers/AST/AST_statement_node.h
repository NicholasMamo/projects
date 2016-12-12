//
// Created by memonick on 09/04/2016.
//

#ifndef LEXER_AST_STATEMENT_NODE_H
#define LEXER_AST_STATEMENT_NODE_H

class visitor;

#include "AST_node.h"
#include <string>

class AST_statement_node : public virtual AST_node {

    public:
        AST_statement_node(unsigned level);
        ~AST_statement_node();

        void set_child(AST_statement_node * child);

        AST_statement_node * get_child();

        virtual void accept(visitor * v);
        virtual void set_level(unsigned level);

    private:
        AST_statement_node * child = nullptr;

};

#endif //LEXER_AST_STATEMENT_NODE_H
