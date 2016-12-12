//
// Created by memonick on 15/03/2016.
//

using namespace std;

#ifndef LEXER_AST_PROGRAM_NODE_H
#define LEXER_AST_PROGRAM_NODE_H

#include "AST_node.h"
#include "AST_statement_node.h"
#include "../visitor/visitor.h"
#include <string>
#include <vector>

class AST_program_node : public virtual AST_node {

    public:
        AST_program_node(unsigned level);
        virtual ~AST_program_node();

        void add_statement(AST_statement_node * node);

        vector<AST_statement_node *> get_statements();

        virtual void set_level(unsigned level);
        virtual void accept(visitor * v);

    private:
        vector<AST_statement_node *> statements;

};

#endif //LEXER_AST_PROGRAM_NODE_H
