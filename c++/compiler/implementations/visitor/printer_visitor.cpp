//
// Created by memonick on 23/03/2016.
//

#include "../../headers/visitor/printer_visitor.h"

/**
 * Get the last string stored in the stack
 * return           the last string stored in the stack
 */
string printer_visitor::get_last() {
    return this->printer_stack.pop();
}

/**
 * Visit the given actual parameters node, and any children it may have, and print it
 * actual_parameters the node to visit
 */
void printer_visitor::visit(AST_actual_parameters_node * actual_parameters_node) {
    vector<AST_node *> actual_parameters_vector = actual_parameters_node->get_actual_parameters();
    string s = "";
    s += this->get_tabs(actual_parameters_node);
    s += "<actual_parameters>";
    s += '\n';
    for (unsigned i = 0; i < actual_parameters_vector.size(); i++) {
        actual_parameters_vector.at(i)->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(actual_parameters_node);
    s += "</actual_parameters>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given assignment_node, and print it
 * assignment_node  the node to visit
 */
void printer_visitor::visit(AST_assignment_node * assignment_node) {
    string s = "";
    s += this->get_tabs(assignment_node);
    s += "<assignment>";
    s += '\n';
    assignment_node->get_identifier()->accept(this);
    s += this->printer_stack.pop();
    assignment_node->get_expression()->accept(this);
    s += this->printer_stack.pop();
    s += this->get_tabs(assignment_node);
    s += "</assignment>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given arithmetic_factor_node, and print it
 * arithmetic_factor_node the node to visit
 */
void printer_visitor::visit(AST_arithmetic_factor_node * arithmetic_factor_node) {
    string s = "";
    s += this->get_tabs(arithmetic_factor_node);
    s += "<arithmetic_factor operator = \"";
    s += arithmetic_factor_node->get_value();
    s += "\">";
    s += '\n';
    if (arithmetic_factor_node->contains_left_child()) {
        arithmetic_factor_node->get_left_child()->accept(this);
        s += this->printer_stack.pop();
    }
    if (arithmetic_factor_node->contains_right_child()) {
        arithmetic_factor_node->get_right_child()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(arithmetic_factor_node);
    s += "</arithmetic_factor>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given arithmetic_term_node, and print it
 * arithmetic_term_node the node to visit
 */
void printer_visitor::visit(AST_arithmetic_term_node * arithmetic_term_node) {
    string s = "";
    s += this->get_tabs(arithmetic_term_node);
    s += "<arithmetic_term operator = \"";
    s += arithmetic_term_node->get_value();
    s += "\">";
    s += '\n';
    if (arithmetic_term_node->contains_left_child()) {
        arithmetic_term_node->get_left_child()->accept(this);
        s += this->printer_stack.pop();
    }
    if (arithmetic_term_node->contains_right_child()) {
        arithmetic_term_node->get_right_child()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(arithmetic_term_node);
    s += "</arithmetic_term>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given boolean expression node, and any children it may have, and print it
 * node             the node to visit
 */
void printer_visitor::visit(AST_block_node * block_node) {
    vector<AST_statement_node *> statements = block_node->get_statements();
    string s = "";
    s += this->get_tabs(block_node);
    s += "<block>";
    s += '\n';
    for (unsigned i = 0; i < statements.size(); i++) {
        statements.at(i)->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(block_node);
    s += "</block>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given booelan node and print it
 * boolean_node     the node to visit
 */
void printer_visitor::visit(AST_boolean_node * boolean_node) {
    string s = "";
    s += this->get_tabs(boolean_node);
    s += "<boolean_node value = \"";
    s += boolean_node->get_bool_value() ? "true" : "false";
    s += "\">";
    s += '\n';
    s += this->get_tabs(boolean_node);
    s += "</boolean_node>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given boolean_factor_node, and print it
 * boolean_factor_node the node to visit
 */
void printer_visitor::visit(AST_boolean_factor_node * boolean_factor_node) {
    string s = "";
    s += this->get_tabs(boolean_factor_node);
    s += "<boolean_factor operator = \"";
    s += boolean_factor_node->get_value();
    s += "\">";
    s += '\n';
    if (boolean_factor_node->contains_left_child()) {
        boolean_factor_node->get_left_child()->accept(this);
        s += this->printer_stack.pop();
    }
    if (boolean_factor_node->contains_right_child()) {
        boolean_factor_node->get_right_child()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(boolean_factor_node);
    s += "</boolean_factor>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given boolean_term_node, and print it
 * boolean_term_node the node to visit
 */
void printer_visitor::visit(AST_boolean_term_node * boolean_term_node) {
    string s = "";
    s += this->get_tabs(boolean_term_node);
    s += "<boolean_term operator = \"";
    s += boolean_term_node->get_value();
    s += "\">";
    s += '\n';
    if (boolean_term_node->contains_left_child()) {
        boolean_term_node->get_left_child()->accept(this);
        s += this->printer_stack.pop();
    }
    if (boolean_term_node->contains_right_child()) {
        boolean_term_node->get_right_child()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(boolean_term_node);
    s += "</boolean_term>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given expression node, and any children it may have, and print it
 * expression_node  the node to visit
 */
void printer_visitor::visit(AST_expression_node * expression_node) {
    string s = "";
    s += this->get_tabs(expression_node);
    s += "<binary_expression_node operation = \"";
    s += expression_node->get_value();
    s += "\">";
    s += '\n';
    if (expression_node->contains_left_child()) {
        expression_node->get_left_child()->accept(this);
        s += this->printer_stack.pop();
    }
    if (expression_node->contains_right_child()) {
        expression_node->get_right_child()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(expression_node);
    s += "</binary_expression_node>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given var_declaration_node, and print it
 * var_declaration_node         the var_declaration_node to visit
 */
void printer_visitor::visit(AST_formal_parameter_node * formal_parameter_node) {
    string s = "";
    s += this->get_tabs(formal_parameter_node);
    s += "<formal_parameter>";
    s += '\n';
    formal_parameter_node->get_identifier()->accept(this);
    s += this->printer_stack.pop();
    formal_parameter_node->get_type()->accept(this);
    s += this->printer_stack.pop();
    s += this->get_tabs(formal_parameter_node);
    s += "</formal_parameter>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given formal parameters node, and any children it may have, and print it
 * formal_parameters the node to visit
 */
void printer_visitor::visit(AST_formal_parameters_node * formal_parameters) {
    vector<AST_formal_parameter_node *> formal_parameters_vector = formal_parameters->get_formal_parameters();
    string s = "";
    s += this->get_tabs(formal_parameters);
    s += "<formal_parameters>";
    s += '\n';
    for (unsigned i = 0; i < formal_parameters_vector.size(); i++) {
        formal_parameters_vector.at(i)->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(formal_parameters);
    s += "</formal_parameters>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given function call node and print it
 * func_call_node   the node to visit
 */
void printer_visitor::visit(AST_func_call_node * func_call_node) {
    string s = "";
    s += this->get_tabs(func_call_node);
    s += "<func_call>";
    s += '\n';
    func_call_node->get_identifier()->accept(this);
    s += this->printer_stack.pop();
    func_call_node->get_actual_parameters()->accept(this);
    s += this->printer_stack.pop();
    s += this->get_tabs(func_call_node);
    s += "</func_call>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given function declaration node and print it
 * func_declaration_node        the node to visit
 */
void printer_visitor::visit(AST_func_declaration_node * func_declaration_node) {
    string s = "";
    s += this->get_tabs(func_declaration_node);
    s += "<func_declaration>";
    s += '\n';
    func_declaration_node->get_identifier()->accept(this);
    s += this->printer_stack.pop();
    func_declaration_node->get_formal_parameters()->accept(this);
    s += this->printer_stack.pop();
    func_declaration_node->get_type()->accept(this);
    s += this->printer_stack.pop();
    func_declaration_node->get_block()->accept(this);
    s += this->printer_stack.pop();
    s += this->get_tabs(func_declaration_node);
    s += "</func_declaration>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given identifier_node, and print it
 * identifier_node             the node to visit
 */
void printer_visitor::visit(AST_identifier_node * identifier_node) {
    string s = "";
    s += this->get_tabs(identifier_node);
    s += "<identifier name = \"";
    s += identifier_node->get_name();
    s += "\">";
    s += "</identifier>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given if_node, and print it
 * if_node             the node to visit
 */
void printer_visitor::visit(AST_if_node * if_node) {
    string s = "";
    s += this->get_tabs(if_node);
    s += "<if>";
    s += '\n';
    if (if_node->get_expression() != nullptr) {
        if_node->get_expression()->accept(this);
        s += this->printer_stack.pop();
    }
    if (if_node->get_block() != nullptr) {
        if_node->get_block()->accept(this);
        s += this->printer_stack.pop();
    }
    if (if_node->get_else_block() != nullptr) {
        if_node->get_else_block()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(if_node);
    s += "</if>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given integer number node and print it
 * node             the node to visit
 */
void printer_visitor::visit(AST_int_number_node * int_number_node) {
    string s = "";
    s += this->get_tabs(int_number_node);
    s += "<integer>";
    s += to_string(int_number_node->get_int_value());
    s += "</integer>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given boolean expression node, and any children it may have, and print it
 * node             the node to visit
 */
void printer_visitor::visit(AST_program_node * program_node) {
    vector<AST_statement_node *> statements = program_node->get_statements();
    string s = "";
    s += this->get_tabs(program_node);
    s += "<program>";
    s += '\n';
    for (unsigned i = 0; i < statements.size(); i++) {
        statements.at(i)->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(program_node);
    s += "</program>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given integer number node and print it
 * node             the node to visit
 */
void printer_visitor::visit(AST_real_number_node * real_number_node) {
    string s = "";
    s += this->get_tabs(real_number_node);
    s += "<real>";
    s += to_string(real_number_node->get_real_value());
    s += "</real>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given return node, and print it
 * return_node             the node to visit
 */
void printer_visitor::visit(AST_return_node * return_node) {
    string s = "";
    s += this->get_tabs(return_node);
    s += "<return>";
    s += '\n';
    if (return_node->get_expression() != nullptr) {
        return_node->get_expression()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(return_node);
    s += "</return>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given statement node, and any children it may have, and print it
 * node             the node to visit
 */
void printer_visitor::visit(AST_statement_node * statement_node) {
    string s = "";
    s += this->get_tabs(statement_node);
    s += "<statement>";
    s += "\n";
    if (statement_node->get_child() != nullptr) {
        statement_node->get_child()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(statement_node);
    s += "</statement>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given string node and print it
 * string_node      the node to visit
 */
void printer_visitor::visit(AST_string_node * string_node) {
    string s = "";
    s += this->get_tabs(string_node);
    s += "<string value = \"";
    s += string_node->get_value();
    s += "\">";
    s += "\n";
    s += this->get_tabs(string_node);
    s += "</string>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given type_node, and print it
 * type_node             the node to visit
 */
void printer_visitor::visit(AST_type_node * type_node) {
    string s = "";
    s += this->get_tabs(type_node);
    s += "<type>";
    s += type_node->get_type();
    s += "</type>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given unary node, and its expression, and print them
 * node             the node to visit
 */
void printer_visitor::visit(AST_unary_node * node) {
    string s = "";
    s += this->get_tabs(node);
    s += "<unary type = \"";
    s += node->get_type();
    s += "\">";
    s += '\n';
    if (node->get_expression() != nullptr) {
        node->get_expression()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(node);
    s += "</unary>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given var_declaration_node, and print it
 * var_declaration_node             the var_declaration_node to visit
 */
void printer_visitor::visit(AST_var_declaration_node * var_declaration_node) {
    string s = "";
    s += this->get_tabs(var_declaration_node);
    s += "<var_declaration>";
    s += '\n';
    var_declaration_node->get_identifier()->accept(this);
    s += this->printer_stack.pop();
    var_declaration_node->get_type()->accept(this);
    s += this->printer_stack.pop();
    var_declaration_node->get_expression()->accept(this);
    s += this->printer_stack.pop();
    s += this->get_tabs(var_declaration_node);
    s += "</var_declaration>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given while_node, and print it
 * while_node             the node to visit
 */
void printer_visitor::visit(AST_while_node * while_node) {
    string s = "";
    s += this->get_tabs(while_node);
    s += "<while>";
    s += '\n';
    if (while_node->get_expression() != nullptr) {
        while_node->get_expression()->accept(this);
        s += this->printer_stack.pop();
    }
    if (while_node->get_block() != nullptr) {
        while_node->get_block()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(while_node);
    s += "</while>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Visit the given write_statement_node , and print it
 * write_statement_node             the node to visit
 */
void printer_visitor::visit(AST_write_statement_node * write_statement_node) {
    string s = "";
    s += this->get_tabs(write_statement_node);
    s += "<write>";
    s += '\n';
    if (write_statement_node->get_expression() != nullptr) {
        write_statement_node->get_expression()->accept(this);
        s += this->printer_stack.pop();
    }
    s += this->get_tabs(write_statement_node);
    s += "</write>";
    s += '\n';
    this->printer_stack.push(s);
}

/**
 * Get a textual representation of the tabs, using the number of levels
 * node             the node whose tabs will be created
 * return           a textual representation of the tabs
 */
string printer_visitor::get_tabs(AST_node * node) {
    string tabs = "";
    for (int i = 0; i < node->get_level(); i++) {
        tabs += '\t';
    }
    return tabs;
}
