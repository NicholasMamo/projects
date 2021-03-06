//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_STRING_NODE_H
#define LEXER_AST_STRING_NODE_H

#include "AST_node.h"
#include "../visitor/visitor.h"
#include <string>

class AST_string_node : public virtual AST_node {

	public:
		AST_string_node(unsigned level, string value);
		virtual ~AST_string_node();

		void set_value(string value);

		string get_value();

		virtual void accept(visitor * v);

	private:
		string value;

};

#endif //LEXER_AST_STRING_NODE_H
