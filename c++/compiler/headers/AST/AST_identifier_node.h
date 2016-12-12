//
// Created by memonick on 09/04/2016.
//

#ifndef LEXER_AST_IDENTIFIER_NODE_H
#define LEXER_AST_IDENTIFIER_NODE_H

#include "AST_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_identifier_node : public virtual AST_node {

    public:
        AST_identifier_node(unsigned level, string name);
        virtual ~AST_identifier_node();

        void set_name(string name);

        string get_name();

        virtual void accept(visitor * v);

    private:
        string name;

};

#endif //LEXER_AST_IDENTIFIER_NODE_H
