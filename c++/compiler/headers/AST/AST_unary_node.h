//
// Created by memonick on 10/04/2016.
//

#ifndef LEXER_AST_UNARY_NODE_H
#define LEXER_AST_UNARY_NODE_H

#include "AST_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_unary_node : public virtual AST_node {

	public:
		AST_unary_node(unsigned level);
		virtual ~AST_unary_node();

		void set_expression(AST_node * expression_node);
		void set_type(string type);

		AST_node * get_expression();
		string get_type();

		virtual void accept(visitor * v);
		virtual void set_level(unsigned level);

	private:
		string type;
		AST_node * expression = nullptr;

};

#endif //LEXER_AST_UNARY_NODE_H
