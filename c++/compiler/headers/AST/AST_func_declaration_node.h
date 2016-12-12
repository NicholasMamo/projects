//
// Created by memonick on 12/04/2016.
//

#ifndef LEXER_AST_FUNC_DECLARATION_NODE_H
#define LEXER_AST_FUNC_DECLARATION_NODE_H

#include "AST_node.h"
#include "AST_block_node.h"
#include "AST_formal_parameters_node.h"
#include "AST_identifier_node.h"
#include "AST_statement_node.h"
#include "AST_type_node.h"
#include "../visitor/visitor.h"
#include <string>
#include <vector>

class AST_func_declaration_node : public virtual AST_statement_node {

	public:
		AST_func_declaration_node(unsigned level);
		virtual ~AST_func_declaration_node();

		void set_block(AST_block_node * block_node);
		void set_identifier(AST_identifier_node * identifier_node);
		void set_type(AST_type_node * type_node);
		void set_formal_parameters(AST_formal_parameters_node * node);

		AST_block_node * get_block();
		AST_identifier_node * get_identifier();
		AST_type_node * get_type();
		AST_formal_parameters_node * get_formal_parameters();

		virtual void set_level(unsigned level);
		virtual void accept(visitor * v);

	private:
		AST_block_node * block = nullptr;
		AST_identifier_node * identifier = nullptr;
		AST_type_node * type = nullptr;
		AST_formal_parameters_node * formal_parameters = nullptr;

};

#endif //LEXER_AST_FUNC_DECLARATION_NODE_H
