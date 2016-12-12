//
// Created by memonick on 23/03/2016.
//

#include <iostream>
#include <string>

using namespace std;

#ifndef LEXER_PRINTER_VISITOR_H
#define LEXER_PRINTER_VISITOR_H

#include "../stack.h"
#include "visitor.h"

class printer_visitor: public visitor {

    public:
        string get_last();

        virtual void visit(AST_actual_parameters_node * actual_parameters_node);
        virtual void visit(AST_assignment_node * assignment_node);
        virtual void visit(AST_arithmetic_factor_node * arithmetic_factor_node);
        virtual void visit(AST_arithmetic_term_node * arithmetic_term_node);
        virtual void visit(AST_block_node * block_node);
        virtual void visit(AST_boolean_node * bool_node);
        virtual void visit(AST_boolean_factor_node * boolean_factor_node);
        virtual void visit(AST_boolean_term_node * boolean_term_node);
        virtual void visit(AST_expression_node * expression_node);
        virtual void visit(AST_formal_parameter_node * formal_parameter_node);
        virtual void visit(AST_formal_parameters_node * formal_parameters_node);
        virtual void visit(AST_func_call_node * function_call_node);
        virtual void visit(AST_func_declaration_node * function_declaration_node);
        virtual void visit(AST_identifier_node * identifier_node);
        virtual void visit(AST_if_node * if_node);
        virtual void visit(AST_int_number_node * int_number_node);
        virtual void visit(AST_program_node * program_node);
        virtual void visit(AST_real_number_node * real_number_node);
        virtual void visit(AST_return_node * return_node);
        virtual void visit(AST_statement_node * statement_node);
        virtual void visit(AST_string_node * string_node);
        virtual void visit(AST_type_node * type_node);
        virtual void visit(AST_unary_node * unary_node);
        virtual void visit(AST_var_declaration_node * var_declaration_node);
        virtual void visit(AST_while_node * while_node);
        virtual void visit(AST_write_statement_node * write_statement_node);
        
        string get_tabs(AST_node * node);

    private:
        stack<string> printer_stack;

};

#include "../AST/AST_actual_parameters_node.h"
#include "../AST/AST_assignment_node.h"
#include "../AST/AST_block_node.h"
#include "../AST/AST_boolean_node.h"
#include "../AST/AST_formal_parameter_node.h"
#include "../AST/AST_formal_parameters_node.h"
#include "../AST/AST_func_call_node.h"
#include "../AST/AST_func_declaration_node.h"
#include "../AST/AST_identifier_node.h"
#include "../AST/AST_if_node.h"
#include "../AST/AST_int_number_node.h"
#include "../AST/AST_program_node.h"
#include "../AST/AST_return_node.h"
#include "../AST/AST_real_number_node.h"
#include "../AST/AST_statement_node.h"
#include "../AST/AST_string_node.h"
#include "../AST/AST_type_node.h"
#include "../AST/AST_unary_node.h"
#include "../AST/AST_var_declaration_node.h"
#include "../AST/AST_while_node.h"
#include "../AST/AST_write_statement_node.h"

#endif //LEXER_PRINTER_VISITOR_H
