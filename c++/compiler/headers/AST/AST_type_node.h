//
// Created by memonick on 09/04/2016.
//

#ifndef LEXER_AST_TYPE_NODE_H
#define LEXER_AST_TYPE_NODE_H

#include "AST_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_type_node : public virtual AST_node {

    public:
        AST_type_node (unsigned level, string type);
        virtual ~AST_type_node ();

        void set_type(string type);

        string get_type();

        virtual void accept(visitor * v);

    private:
        string type;

};

#endif //LEXER_AST_TYPE_NODE_H
