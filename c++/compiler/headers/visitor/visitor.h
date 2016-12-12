//
// Created by memonick on 23/03/2016.
//

#ifndef LEXER_VISITOR_H
#define LEXER_VISITOR_H

#include "../AST/AST_node.h"
#include "../AST/AST_binary_expression_node.h"
#include "../AST/AST_arithmetic_factor_node.h"
#include "../AST/AST_boolean_factor_node.h"
#include "../AST/AST_expression_node.h"
#include "../AST/AST_arithmetic_term_node.h"
#include "../AST/AST_boolean_term_node.h"

#include <vector>

class AST_node;
class AST_actual_parameters_node;
class AST_assignment_node;
class AST_arithmetic_factor_node;
class AST_arithmetic_term_node;
class AST_binary_expression_node;
class AST_block_node;
class AST_boolean_node;
class AST_boolean_factor_node;
class AST_boolean_term_node;
class AST_expression_node;
class AST_formal_parameter_node;
class AST_formal_parameters_node;
class AST_func_call_node;
class AST_func_declaration_node;
class AST_identifier_node;
class AST_if_node;
class AST_int_number_node;
class AST_program_node;
class AST_real_number_node;
class AST_return_node;
class AST_statement_node;
class AST_string_node;
class AST_term_node;
class AST_type_node;
class AST_unary_node;
class AST_var_declaration_node;
class AST_while_node;
class AST_write_statement_node;

class visitor {

    public:
        virtual void visit(AST_actual_parameters_node * actual_parameters_node) = 0;
        virtual void visit(AST_assignment_node * assignment_node) = 0;
        virtual void visit(AST_arithmetic_factor_node * arithmetic_factor_node) = 0;
        virtual void visit(AST_arithmetic_term_node * arithmetic_term_node) = 0;
        virtual void visit(AST_block_node * block_node) = 0;
        virtual void visit(AST_boolean_node * bool_node) = 0;
        virtual void visit(AST_boolean_factor_node * boolean_factor_node) = 0;
        virtual void visit(AST_boolean_term_node * boolean_term_node) = 0;
        virtual void visit(AST_expression_node * expression_node) = 0;
        virtual void visit(AST_formal_parameter_node * formal_parameter_node) = 0;
        virtual void visit(AST_formal_parameters_node * formal_parameters_node) = 0;
        virtual void visit(AST_func_call_node * function_call_node) = 0;
        virtual void visit(AST_func_declaration_node * function_declaration_node) = 0;
        virtual void visit(AST_identifier_node * identifier_node) = 0;
        virtual void visit(AST_if_node * if_node) = 0;
        virtual void visit(AST_int_number_node * int_number_node) = 0;
        virtual void visit(AST_program_node * program_node) = 0;
        virtual void visit(AST_real_number_node * real_number_node) = 0;
        virtual void visit(AST_return_node * return_node) = 0;
        virtual void visit(AST_statement_node * statement_node) = 0;
        virtual void visit(AST_string_node * string_node) = 0;
        virtual void visit(AST_type_node * type_node) = 0;
        virtual void visit(AST_unary_node * unary_node) = 0;
        virtual void visit(AST_var_declaration_node * var_declaration_node) = 0;
        virtual void visit(AST_while_node * while_node) = 0;
        virtual void visit(AST_write_statement_node * write_statement_node) = 0;
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

#endif //LEXER_VISITOR_H
