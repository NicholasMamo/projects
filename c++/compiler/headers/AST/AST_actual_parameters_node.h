//
// Created by memonick on 13/04/2016.
//

#ifndef LEXER_AST_ACTUAL_PARAMETERS_NODE_H
#define LEXER_AST_ACTUAL_PARAMETERS_NODE_H

#include "AST_node.h"
#include "AST_node.h"
#include "../visitor/visitor.h"
#include <string>
#include <vector>

class AST_actual_parameters_node : public virtual AST_node {

	public:
		AST_actual_parameters_node(unsigned level);
		virtual ~AST_actual_parameters_node();

		void add_actual_parameter(AST_node * node);

		vector<AST_node *> get_actual_parameters();

		virtual void set_level(unsigned level);
		virtual void accept(visitor * v);

	private:
		vector<AST_node *> actual_parameters;

};

#endif //LEXER_AST_ACTUAL_PARAMETERS_NODE_H
