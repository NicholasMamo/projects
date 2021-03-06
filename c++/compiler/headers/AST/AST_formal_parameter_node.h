//
// Created by memonick on 12/04/2016.
//

#ifndef LEXER_AST_FORMAL_PARAMETER_NODE_H
#define LEXER_AST_FORMAL_PARAMETER_NODE_H

#include "AST_node.h"
#include "AST_identifier_node.h"
#include "AST_type_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_formal_parameter_node : public virtual AST_node {

public:
    AST_formal_parameter_node(unsigned level);
    virtual ~AST_formal_parameter_node();

    void set_identifier(AST_identifier_node * identifier_node);
    void set_type(AST_type_node * type_node);

    AST_identifier_node * get_identifier();
    AST_type_node * get_type();

    virtual void accept(visitor * v);
    virtual void set_level(unsigned level);

private:
    AST_identifier_node * identifier = nullptr;
    AST_type_node * type = nullptr;

};

#endif //LEXER_AST_FORMAL_PARAMETER_NODE_H
