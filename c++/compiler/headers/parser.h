//
// Created by memonick on 15/03/2016.
//

#include <iostream>
#include <map>
#include <string>

using namespace std;

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H

#include "AST/AST_expression_node.h"
#include "AST/AST_factor_node.h"
#include "AST/AST_node.h"
#include "AST/AST_actual_parameters_node.h"
#include "AST/AST_arithmetic_factor_node.h"
#include "AST/AST_arithmetic_term_node.h"
#include "AST/AST_assignment_node.h"
#include "AST/AST_boolean_node.h"
#include "AST/AST_boolean_factor_node.h"
#include "AST/AST_boolean_term_node.h"
#include "AST/AST_identifier_node.h"
#include "AST/AST_formal_parameter_node.h"
#include "AST/AST_formal_parameters_node.h"
#include "AST/AST_func_call_node.h"
#include "AST/AST_func_declaration_node.h"
#include "AST/AST_if_node.h"
#include "AST/AST_int_number_node.h"
#include "AST/AST_number_node.h"
#include "AST/AST_program_node.h"
#include "AST/AST_real_number_node.h"
#include "AST/AST_return_node.h"
#include "AST/AST_string_node.h"
#include "AST/AST_term_node.h"
#include "AST/AST_unary_node.h"
#include "AST/AST_var_declaration_node.h"
#include "AST/AST_while_node.h"
#include "AST/AST_write_statement_node.h"
#include "exceptions/missing_bracket.h"
#include "exceptions/unexpected_input.h"
#include "exceptions/unexpected_token.h"
#include "lexer.h"
#include "visitor/printer_visitor.h"

#include <string>

class parser {

    public:
        parser(lexer * l);

        AST_program_node * parse();

    private:
        lexer * l;
        map<char, int> precedence = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'(', 3}};

        void consume(name n);
        void consume(name n, string c);
        AST_actual_parameters_node * parse_actual_parameters();
        AST_assignment_node * parse_assignment();
        AST_block_node * parse_block();
        AST_boolean_node * parse_boolean_literal();
        AST_node * parse_expression();
        AST_identifier_node * parse_identifier();
        AST_if_node * parse_if_statement();
        AST_node * parse_factor();
        AST_formal_parameter_node * parse_formal_parameter();
        AST_formal_parameters_node * parse_formal_parameters();
        AST_func_call_node * parse_function_call();
        AST_func_declaration_node * parse_function_declaration();
        AST_number_node * parse_number();
        AST_return_node * parse_return_statement();
        AST_node * parse_simple_expression();
        AST_statement_node * parse_statement();
        AST_string_node * parse_string();
        AST_node * parse_subexpression();
        AST_node * parse_term();
        AST_type_node * parse_type();
        AST_node * parse_unary_node();
        AST_var_declaration_node * parse_var_declaration();
        AST_while_node * parse_while_statement();
        AST_write_statement_node * parse_write_statement();

};

#endif //LEXER_PARSER_H
