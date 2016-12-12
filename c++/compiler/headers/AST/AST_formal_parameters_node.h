//
// Created by memonick on 12/04/2016.
//

#ifndef LEXER_AST_FORMAL_PARAMETERS_NODE_H
#define LEXER_AST_FORMAL_PARAMETERS_NODE_H

#include "AST_node.h"
#include "AST_formal_parameter_node.h"
#include "../visitor/visitor.h"
#include <string>
#include <vector>

class AST_formal_parameters_node : public virtual AST_node {

	public:
		AST_formal_parameters_node(unsigned level);
		virtual ~AST_formal_parameters_node();

		void add_formal_parameter(AST_formal_parameter_node * node);

		vector<AST_formal_parameter_node *> get_formal_parameters();

		virtual void set_level(unsigned level);
		virtual void accept(visitor * v);

	private:
		vector<AST_formal_parameter_node *> formal_parameters;

};

#endif //LEXER_AST_FORMAL_PARAMETERS_NODE_H
