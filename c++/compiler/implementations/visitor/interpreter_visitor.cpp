//
// Created by memonick on 20/04/2016.
//

#include "../../headers/visitor/interpreter_visitor.h"

interpreter_visitor::interpreter_visitor() {
    this->scope.push(new symbol_table());
}

/**
 * Analyze the program given
 * program          the program to analyze
 */
void interpreter_visitor::analyze(AST_program_node * program) {
    try {
        program->accept(this);
    } catch (general_exception * exception) {
        cout << exception->to_string() << endl;
        delete exception;
    }
}

/**
 * Get the last calculation made by the interpreter
 * return           the last calculation made by the interpreter
 */
symbol_var interpreter_visitor::get_last() {
    this->last.set_name("last");
    return this->last;
}

/**
 * Get the interpreter's current symbol table
 * return           the current symbol table
 */
symbol_table * interpreter_visitor::get_symbol_table() {
    return this->scope.peek();
}

/**
 * Visit the given actual parameters node, and any children it may have, and interpret it
 * actual_parameters the node to visit
 */
void interpreter_visitor::visit(AST_actual_parameters_node * actual_parameters_node) {
    string function_name = this->var_stack.pop().get_name();
    vector<AST_node *> parameters = actual_parameters_node->get_actual_parameters();
    symbol_func * function = this->scope.peek()->get_function(function_name);
    vector<AST_formal_parameter_node *> formal_parameters = function->get_parameters()->get_formal_parameters();
    for (unsigned i = 0; i < formal_parameters.size(); i++) {
        string name = formal_parameters.at(i)->get_identifier()->get_name();
        symbol_var new_var = symbol_var(name);
        parameters.at(i)->accept(this);
        symbol_var actual = this->var_stack.pop();
        switch (actual.get_type()) {
            case type_int:
                if (symbol::string_to_type(formal_parameters.at(i)->get_type()->get_type()) == type_real) {
                    new_var.set_value((double)actual.get_int_value());
                } else {
                    new_var.set_value(actual.get_int_value());
                }
                break;
            case type_real:
                new_var.set_value(actual.get_real_value());
                break;
            case type_bool:
                new_var.set_value(actual.get_bool_value());
                break;
            case type_string:
                new_var.set_value(actual.get_string_value());
                break;
        }
        this->scope.peek()->add_symbol(new_var);
        this->scope.peek()->set_replaced(symbol_var(name));
    }
}

/**
 * Visit the given assignment_node, and interpret it
 * assignment_node  the node to visit
 */
void interpreter_visitor::visit(AST_assignment_node * assignment_node) {
    assignment_node->get_identifier()->accept(this);
    symbol_var var = this->var_stack.pop();
    assignment_node->get_expression()->accept(this);
    symbol_var expression = this->var_stack.pop();
    bool replaced = false;
    if (var.get_type() == expression.get_type()) {
        switch (expression.get_type()) {
            case type_int:
                for (unsigned i = 0; i < this->scope.size(); i++) {
                    if (!replaced) {
                        this->scope.peek(i)->set_value(var.get_name(), expression.get_int_value());
                        replaced = this->scope.peek(i)->is_replaced(var.get_name());
                    }
                }
                break;
            case type_real:
                for (unsigned i = 0; i < this->scope.size(); i++) {
                    if (!replaced) {
                        this->scope.peek(i)->set_value(var.get_name(), expression.get_real_value());
                        replaced = this->scope.peek(i)->is_replaced(var.get_name());
                    }
                }
                break;
            case type_bool:
                for (unsigned i = 0; i < this->scope.size(); i++) {
                    if (!replaced) {
                        this->scope.peek(i)->set_value(var.get_name(), expression.get_bool_value());
                        replaced = this->scope.peek(i)->is_replaced(var.get_name());
                    }
                }
                break;
            case type_string:
                for (unsigned i = 0; i < this->scope.size(); i++) {
                    if (!replaced) {
                        this->scope.peek(i)->set_value(var.get_name(), expression.get_string_value());
                        replaced = this->scope.peek(i)->is_replaced(var.get_name());
                    }
                }
                break;
        }
    } else if (symbol_var::is_number_type(var) && symbol_var::is_number_type(expression)) {
        if (var.get_type() == type_real) {
            for (unsigned i = 0; i < this->scope.size(); i++) {
                if (!replaced) {
                    this->scope.peek(i)->set_value(var.get_name(), (double)expression.get_int_value());
                    replaced = this->scope.peek(i)->is_replaced(var.get_name());
                }
            }
        } else {
            throw new incompatible_types_exception(expression.get_type(), type_int);
        }
    } else {
        throw new incompatible_types_exception(expression.get_type(), var.get_type());
    }
}

/**
 * Visit the given arithmetic_factor_node, and interpret it
 * arithmetic_factor_node the node to visit
 */
void interpreter_visitor::visit(AST_arithmetic_factor_node * arithmetic_factor_node) {
    arithmetic_factor_node->get_left_child()->accept(this);
    symbol_var var_1 = this->var_stack.pop();
    arithmetic_factor_node->get_right_child()->accept(this);
    symbol_var var_2 = this->var_stack.pop();
    this->resolve_operation(arithmetic_factor_node->get_value(), var_1, var_2);
}

/**
 * Visit the given arithmetic_term_node, and interpret it
 * arithmetic_term_node the node to visit
 */
void interpreter_visitor::visit(AST_arithmetic_term_node * arithmetic_term_node) {
    arithmetic_term_node->get_left_child()->accept(this);
    symbol_var var_1 = this->var_stack.pop();
    arithmetic_term_node->get_right_child()->accept(this);
    symbol_var var_2 = this->var_stack.pop();
    this->resolve_operation(arithmetic_term_node->get_value(), var_1, var_2);
}

/**
 * Visit the given boolean expression node, and any children it may have, and interpret it
 * node             the node to visit
 */
void interpreter_visitor::visit(AST_block_node * block_node) {
    vector<AST_statement_node *> statements = block_node->get_statements();
    this->scope.push(symbol_table::clone(this->scope.peek())); // create a new scope
    for (unsigned i = 0; i < statements.size(); i++) {
        if (this->return_stack.size() <= call_stack) {
            statements.at(i)->accept(this);
        }
    }
    this->scope.pop(); // remove the new scope
}

/**
 * Visit the given boolean node and interpret it
 * boolean_node     the node to visit
 */
void interpreter_visitor::visit(AST_boolean_node * boolean_node) {
    symbol_var var = symbol_var("");
    var.set_value(boolean_node->get_bool_value());
    this->var_stack.push(var);
    this->last = var;
}

/**
 * Visit the given boolean_factor_node, and interpret it
 * boolean_factor_node the node to visit
 */
void interpreter_visitor::visit(AST_boolean_factor_node * boolean_factor_node) {
    boolean_factor_node->get_left_child()->accept(this);
    symbol_var var_1 = this->var_stack.pop();
    boolean_factor_node->get_right_child()->accept(this);
    symbol_var var_2 = this->var_stack.pop();
    this->resolve_operation(boolean_factor_node->get_value(), var_1, var_2);
}

/**
 * Visit the given boolean_term_node, and interpret it
 * boolean_term_node the node to visit
 */
void interpreter_visitor::visit(AST_boolean_term_node * boolean_term_node) {
    boolean_term_node->get_left_child()->accept(this);
    symbol_var var_1 = this->var_stack.pop();
    boolean_term_node->get_right_child()->accept(this);
    symbol_var var_2 = this->var_stack.pop();
    this->resolve_operation(boolean_term_node->get_value(), var_1, var_2);
}

/**
 * Visit the given expression node, and any children it may have, and interpret it
 * expression_node  the node to visit
 */
void interpreter_visitor::visit(AST_expression_node * expression_node) {
    expression_node->get_left_child()->accept(this);
    symbol_var var_1 = this->var_stack.pop();
    expression_node->get_right_child()->accept(this);
    symbol_var var_2 = this->var_stack.pop();
    this->resolve_operation(expression_node->get_value(), var_1, var_2);
}

/**
 * Visit the given var_declaration_node, and interpret it
 * var_declaration_node         the var_declaration_node to visit
 */
void interpreter_visitor::visit(AST_formal_parameter_node * formal_parameter_node) {
}

/**
 * Visit the given formal parameters node, and any children it may have, and interpret it
 * formal_parameters the node to visit
 */
void interpreter_visitor::visit(AST_formal_parameters_node * formal_parameters) {
}

/**
 * Visit the given function call node and interpret it
 * func_call_node   the node to visit
 */
void interpreter_visitor::visit(AST_func_call_node * func_call_node) {
    string name = func_call_node->get_identifier()->get_name();
    if (this->scope.peek()->is_in_scope(name) && this->scope.peek()->is_function(name)) {
        this->call_stack++;
        this->scope.push(symbol_table::clone(this->scope.peek())); // create a new scope
        this->var_stack.push(symbol_var(name));
        func_call_node->get_actual_parameters()->accept(this);
        this->scope.peek()->get_function(name)->get_body()->accept(this);
        this->var_stack.push(this->return_stack.pop());
        this->call_stack--;
        this->scope.pop(); // remove the new scope
    } else {
        throw new undeclared_func_exception(name);
    }
}

/**
 * Visit the given function declaration node and interpret it
 * func_declaration_node        the node to visit
 */
void interpreter_visitor::visit(AST_func_declaration_node * func_declaration_node) {
    this->scope.peek()->add_symbol(func_declaration_node);
}

/**
 * Visit the given identifier_node, and interpret it
 * identifier_node             the node to visit
 */
void interpreter_visitor::visit(AST_identifier_node * identifier_node) {
    string name = identifier_node->get_name();
    if (this->scope.peek()->is_in_scope(name)) {
        this->var_stack.push(*this->scope.peek()->get_variable(name));
    } else {
        this->var_stack.push(symbol_var(""));
    }
}

/**
 * Visit the given if_node, and interpret it
 * if_node             the node to visit
 */
void interpreter_visitor::visit(AST_if_node * if_node) {
    if_node->get_expression()->accept(this);
    symbol_var condition = this->var_stack.pop();
    if (condition.get_bool_value()) {
        if_node->get_block()->accept(this);
    } else if (if_node->get_else_block() != nullptr) {
        if_node->get_else_block()->accept(this);
    }
}

/**
 * Visit the given integer number node and interpret it
 * node             the node to visit
 */
void interpreter_visitor::visit(AST_int_number_node * int_number_node) {
    symbol_var var = symbol_var("");
    var.set_value(int_number_node->get_int_value());
    this->var_stack.push(var);
    this->last = var;
}

/**
 * Visit the given boolean expression node, and any children it may have, and interpret it
 * node             the node to visit
 */
void interpreter_visitor::visit(AST_program_node * program_node) {
    vector<AST_statement_node *> statements = program_node->get_statements();
    for (unsigned i = 0; i < statements.size(); i++) {
        statements.at(i)->accept(this);
    }
}

/**
 * Visit the given integer number node and interpret it
 * node             the node to visit
 */
void interpreter_visitor::visit(AST_real_number_node * real_number_node) {
    symbol_var var = symbol_var("");
    var.set_value(real_number_node->get_real_value());
    this->var_stack.push(var);
    this->last = var;
}

/**
 * Visit the given return node, and interpret it
 * return_node             the node to visit
 */
void interpreter_visitor::visit(AST_return_node * return_node) {
    return_node->get_expression()->accept(this);
    this->return_stack.push(this->var_stack.pop());
}

/**
 * Visit the given statement node, and any children it may have, and interpret it
 * node             the node to visit
 */
void interpreter_visitor::visit(AST_statement_node * statement_node) {
    statement_node->get_child()->accept(this);
}

/**
 * Visit the given var_type node and interpret it
 * string_node      the node to visit
 */
void interpreter_visitor::visit(AST_string_node * string_node) {
    symbol_var var = symbol_var("");
    var.set_value(string_node->get_value());
    this->var_stack.push(var);
    this->last = var;
}

/**
 * Visit the given type_node, and interpret it
 * type_node             the node to visit
 */
void interpreter_visitor::visit(AST_type_node * type_node) {
    symbol_var var = symbol_var("");
    var.set_type(symbol::string_to_type(type_node->get_type()));
    this->var_stack.push(var);
}

/**
 * Visit the given unary node, and its expression, and interpret them
 * node             the node to visit
 */
void interpreter_visitor::visit(AST_unary_node * node) {
    node->get_expression()->accept(this);
    symbol_var var = this->var_stack.pop();
    this->resolve_operation(node->get_type(), var);
}

/**
 * Visit the given var_declaration_node, and interpret it
 * var_declaration_node             the var_declaration_node to visit
 */
void interpreter_visitor::visit(AST_var_declaration_node * var_declaration_node) {
    string name = var_declaration_node->get_identifier()->get_name();
    var_declaration_node->get_expression()->accept(this);
    symbol_var var = this->var_stack.pop();
    var_declaration_node->get_type()->accept(this);
    symbol_var type = this->var_stack.pop();

    var.set_name(name);
    this->scope.peek()->add_symbol(var);
    this->scope.peek()->set_replaced(name);

    if (var.get_type() == type.get_type()) {

    } else if (symbol_var::is_number_type(var) && symbol_var::is_number_type(type) && type.get_type() == type_real){
        this->scope.peek()->set_value(name, (double) var.get_int_value());
    } else {
        throw new incompatible_types_exception(var.get_type(), type.get_type());
    }
}

/**
 * Visit the given while_node, and interpret it
 * while_node             the node to visit
 */
void interpreter_visitor::visit(AST_while_node * while_node) {
    while_node->get_expression()->accept(this);
    symbol_var condition = this->var_stack.pop();
    while(condition.get_bool_value()) {
        while_node->get_block()->accept(this);
        while_node->get_expression()->accept(this);
        condition = this->var_stack.pop();
    }
}

/**
 * Visit the given write_statement_node , and interpret it
 * write_statement_node             the node to visit
 */
void interpreter_visitor::visit(AST_write_statement_node * write_statement_node) {
    write_statement_node->get_expression()->accept(this);
    cout << this->var_stack.pop().value_to_string() << endl;
}

/**
 * Resolve the solution of the unary operation and the operand
 */
void interpreter_visitor::resolve_operation(string op, symbol_var operand) {
    symbol_var result = symbol_var("");
    if (op == "+") {
        result = operand;
    } else if (op == "-") {
        result = operand - operand - operand;
    } else if (op == "not") {
        result = not(operand);
    }

    this->last = result;

    this->var_stack.push(result);
}

/**
 * Resolve the solution of the operation and the two operands
 */
void interpreter_visitor::resolve_operation(string op, symbol_var operand_1, symbol_var operand_2) {
    symbol_var result = symbol_var("");
    if (op == "+") {
        result = operand_1 + operand_2;
    } else if (op == "-") {
        result = operand_1 - operand_2;
    } else if (op == "*") {
        result = operand_1 * operand_2;
    } else if (op == "/") {
        result = operand_1 / operand_2;
    } else if (op == "<") {
        result = operand_1 < operand_2;
    } else if (op == "<=") {
        result = operand_1 <= operand_2;
    } else if (op == ">") {
        result = operand_1 > operand_2;
    } else if (op == ">=") {
        result = operand_1 >= operand_2;
    } else if (op == "==") {
        result = operand_1 == operand_2;
    } else if (op == "!=") {
        result = operand_1 != operand_2;
    } else if (op == "or") {
        result = operand_1 || operand_2;
    } else if (op == "and") {
        result = operand_1 && operand_2;
    }

    this->last = result;

    this->var_stack.push(result);
}