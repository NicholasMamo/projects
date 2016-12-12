//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_FUNCTION_CALL_NODE_H
#define LEXER_AST_FUNCTION_CALL_NODE_H

#include "AST_node.h"
#include "AST_actual_parameters_node.h"
#include "AST_identifier_node.h"
#include "AST_statement_node.h"
#include "../visitor/visitor.h"
#include <string>
#include <vector>

class AST_func_call_node : public virtual AST_statement_node {

	public:
		AST_func_call_node(unsigned level);
		virtual ~AST_func_call_node();

		void set_identifier(AST_identifier_node * identifier_node);
		void set_actual_parameters(AST_actual_parameters_node * node);

		AST_identifier_node * get_identifier();
		AST_actual_parameters_node * get_actual_parameters();

		virtual void set_level(unsigned level);
		virtual void accept(visitor * v);

	private:
		AST_identifier_node * identifier = nullptr;
		AST_actual_parameters_node * actual_parameters = nullptr;

};

#endif //LEXER_AST_FUNCTION_CALL_NODE_H
