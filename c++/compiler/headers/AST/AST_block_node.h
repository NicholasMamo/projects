//
// Created by memonick on 11/04/2016.
//

#ifndef LEXER_AST_BLOCK_NODE_H
#define LEXER_AST_BLOCK_NODE_H

#include "AST_node.h"
#include "AST_statement_node.h"
#include "../visitor/visitor.h"
#include <string>
#include <vector>

class AST_block_node : public virtual AST_statement_node {

    public:
        AST_block_node(unsigned level);
        virtual ~AST_block_node();

        void add_statement(AST_statement_node * node);

        vector<AST_statement_node *> get_statements();

        virtual void set_level(unsigned level);
        virtual void accept(visitor * v);

    private:
        vector<AST_statement_node *> statements;

};

#endif //LEXER_AST_BLOCK_NODE_H
