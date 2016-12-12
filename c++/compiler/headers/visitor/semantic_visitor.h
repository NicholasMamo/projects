//
// Created by memonick on 18/04/2016.
//

#ifndef LEXER_SEMANTIC_VISITOR_H
#define LEXER_SEMANTIC_VISITOR_H

#include "../stack.h"
#include "../symbol_table/symbol_table.h"
#include "../exceptions/incompatible_types_exception.h"
#include "../exceptions/incorrect_parameter_count.h"
#include "../exceptions/incorrect_return_type_exception.h"
#include "../exceptions/missing_return_exception.h"
#include "../exceptions/undeclared_func_exception.h"
#include "../exceptions/undeclared_var_exception.h"
#include "../exceptions/unexpected_input.h"
#include "visitor.h"

#include <iostream>

using namespace std;

class semantic_visitor: public visitor {

    public:
        semantic_visitor();

        bool analyze(AST_program_node * program);

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

    private:

        bool is_number_type(var_type type);

        void resolve(var_type type_1, var_type type_2);
        void resolve_boolean(var_type type_1, var_type type_2);
        void resolve_comparison(string operation, var_type type_1, var_type type_2);
        void resolve_number(var_type type_1, var_type type_2);
        void resolve_operator(var_type type_1, var_type type_2);

        stack<var_type> return_stack;
        stack<symbol_table *> scope;
        stack<var_type> semantic_stack;

};

#endif //LEXER_SEMANTIC_VISITOR_H
