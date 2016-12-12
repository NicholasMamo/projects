//
// Created by memonick on 15/03/2016.
//

#include "../headers/parser.h"

/**
 * Create the parser that works on the given lexer
 * l                the lexer on which the parser will work
 */
parser::parser(lexer * l) {
    this->l = l;
}

/**
 * Parse the program given by the lexer
 */
AST_program_node * parser::parse() {
    token * t;
    AST_program_node * program_node = new AST_program_node(0);

    t = this->l->peek();
    try {
        while (t->get_name() != TOK_eof) {
            AST_statement_node *statement_node = this->parse_statement();
            AST_statement_node *statement = new AST_statement_node(0);
            statement->set_child(statement_node);
            program_node->add_statement(statement);
            t = this->l->peek();
        }
    } catch (unexpected_input * exception) {
        cout << exception->to_string() << endl;
        delete exception;
    } catch (unexpected_token * exception) {
        cout << exception->to_string() << endl;
        delete exception;
    } catch (missing_bracket * exception){
        cout << exception->to_string() << endl;
        delete exception;
    }

    delete t;

    return program_node;
}

/**
 * Consume the next token if it is the same as the one given
 * n                the name of the token to consume
 */
void parser::consume(name n) {
    token * tentative = this->l->peek(); // peek at the next token
    if (tentative->get_name() == n) { // if the token has the correct name
        this->l->get_next_token();
    } else {
        throw new unexpected_token(tentative->get_name(), n, tentative->get_line());
    }
}

/**
 * Consume the next token if it is the same as the one given and has the same attribute
 * n                the name of the token to consume
 * s                the value of the token to consume
 */
void parser::consume(name n, string s) {
    token * tentative = this->l->peek(); // peek at the next token
    if (tentative->get_name() == n) { // if the token has the correct name
        if (tentative->get_attribute() == s) {
            this->l->get_next_token();
        } else {
            throw new unexpected_input(tentative->get_attribute(), s, tentative->get_line());
        }
    } else {
        if (n == TOK_bracket) {
            throw new missing_bracket(s.at(0), tentative->get_line());
        } else {
            throw new unexpected_token(tentative->get_name(), n, tentative->get_line());
        }
    }
}

/**
 * Parse the function arguments
 * return           the function arguments found
 */
AST_actual_parameters_node * parser::parse_actual_parameters() {
    AST_actual_parameters_node * actual_parameters = new AST_actual_parameters_node(0);
    this->consume(TOK_bracket, "(");
    token * t = this->l->peek();
    while (t->get_name() != TOK_bracket) {
        actual_parameters->add_actual_parameter(this->parse_expression());
        t = this->l->peek();
        if (t->get_name() == TOK_comma) {
            this->l->get_next_token();
        } else if (t->get_name() != TOK_bracket) {
            throw new unexpected_token(t->get_name(), TOK_bracket, t->get_line());
        }
        t = this->l->peek();
    }

    this->consume(TOK_bracket, ")");
    return actual_parameters;
}

/**
 * Parse the variable assignment and return the AST node that represents it
 * return           the AST_assignment_node that is parsed
 */
AST_assignment_node * parser::parse_assignment() {
    AST_assignment_node * assignment_node = new AST_assignment_node(0);
    this->consume(TOK_keyword, "set");
    assignment_node->set_identifier(this->parse_identifier());
    this->consume(TOK_assignment, "=");
    assignment_node->set_expression(this->parse_expression());
    return assignment_node;
}

/**
 * Parse the block
 * return           the block node
 */
AST_block_node * parser::parse_block() {
    AST_block_node * block_node = new AST_block_node(0);
    this->consume(TOK_bracket, "{");
    token * t = this->l->peek(); // peek at the next token
    while (t->get_name() != TOK_bracket && t->get_attribute() != "}") { // repeat until the block is finished
        block_node->add_statement(this->parse_statement()); // get the next statement and add it to the block
        t = this->l->peek(); // peek at the next token
    }
    this->consume(TOK_bracket, "}");
    return block_node;
}

/**
 * Parse the boolean literal
 * return           the boolean node
 */
AST_boolean_node * parser::parse_boolean_literal() {
    token * t = this->l->peek();
    if (t->get_name() == TOK_bool_literal) {
        t = this->l->get_next_token();
        AST_boolean_node * boolean_node = new AST_boolean_node(0, t->get_attribute());
        return boolean_node;
    } else {
        throw new unexpected_token(t->get_name(), TOK_bool_literal, t->get_line());
    }
}

/**
 * Parse the simple expression
 * return           the parsed expression node
 */
AST_node * parser::parse_expression() {
    AST_node * parent = this->parse_simple_expression(); // get the first part of the expression
    token * t = this->l->peek();
    while (t->get_name() == TOK_boolean) { // if there is a right-hand side
        t = this->l->get_next_token(); // get the operator
        AST_node * left = parent; // the current side (first part) becomes the left-hand side
        AST_expression_node * parent = new AST_expression_node(0, t->get_attribute()); // create the parent (boolean) operator
        parent->set_left_child(left); // set the left-hand side of the of the operator
        AST_node * right = this->parse_expression(); // get the right-hand side of the operator
        parent->set_right_child(right); // set the right-hand side of the operator
        return parent;
    }

    return parent;
}

/**
 * Parse the factor
 * return           the factor found
 */
AST_node * parser::parse_factor() {
    token * t = this->l->peek();
    token * t2 = this->l->peek(1);
    switch (t->get_name()) {
        case TOK_arithmetic:
            return this->parse_unary_node();
        case TOK_boolean_operator:
            if (t->get_attribute() == "not") {
                return this->parse_unary_node();
            } else {
                throw new unexpected_input(t->get_attribute(), t->get_line());
            }
        case TOK_bool_literal:
            return this->parse_boolean_literal();
        case TOK_bracket:
            return this->parse_subexpression();
        case TOK_identifier:
            if (t2->get_name() == TOK_bracket && t2->get_attribute() == "(") {
                return this->parse_function_call();
            } else {
                return this->parse_identifier();
            }
        case TOK_int_number:
        case TOK_real_number:
            return this->parse_number();
        case TOK_string_start:
            return this->parse_string();
        default:
            throw new unexpected_token(t->get_name(), t->get_line());
    }
}

/**
 * Parse the function parameter
 * return           the function parameter found
 */
AST_formal_parameter_node * parser::parse_formal_parameter() {
    AST_formal_parameter_node * formal_parameter = new AST_formal_parameter_node(0);
    formal_parameter->set_identifier(this->parse_identifier());
    this->consume(TOK_colon);
    formal_parameter->set_type(this->parse_type());
    return formal_parameter;
}

/**
 * Parse the function parameters
 * return           the function parameters found
 */
AST_formal_parameters_node * parser::parse_formal_parameters() {
    AST_formal_parameters_node * formal_parameters = new AST_formal_parameters_node(0);
    this->consume(TOK_bracket, "(");
    token * t = this->l->peek();
    while (t->get_name() != TOK_bracket) {
        formal_parameters->add_formal_parameter(this->parse_formal_parameter());
        t = this->l->peek();
        if (t->get_name() == TOK_comma) {
            this->l->get_next_token();
        } else if (t->get_name() != TOK_bracket) {
            throw new unexpected_token(t->get_name(), TOK_bracket, t->get_line());
        }
        t = this->l->peek();
    }

    this->consume(TOK_bracket, ")");
    return formal_parameters;
}

/**
 * Parse the function call
 * return           the function call found
 */
AST_func_call_node * parser::parse_function_call() {
    AST_func_call_node * function_call = new AST_func_call_node(0);
    function_call->set_identifier(this->parse_identifier());
    function_call->set_actual_parameters(this->parse_actual_parameters());
    return function_call;
}

/**
 * Parse the function declaration
 * return           the function declaration found
 */
AST_func_declaration_node * parser::parse_function_declaration() {
    AST_func_declaration_node * function_declaration = new AST_func_declaration_node(0);
    this->consume(TOK_keyword, "def");
    function_declaration->set_identifier(this->parse_identifier());
    function_declaration->set_formal_parameters(this->parse_formal_parameters());
    this->consume(TOK_colon);
    function_declaration->set_type(this->parse_type());
    function_declaration->set_block(this->parse_block());
    return function_declaration;
}

/**
 * Parse the identifier
 * return           the parsed identifier node
 */
AST_identifier_node * parser::parse_identifier() {
    token * t = this->l->get_next_token();
    if (t->get_name() == TOK_identifier) {
        return new AST_identifier_node(0, t->get_attribute());
    } else {
        throw new unexpected_token(t->get_name(), TOK_identifier, t->get_line());
    }
}

/**
 * Parse the if statement
 * return           the parsed if node
 */
AST_if_node * parser::parse_if_statement() {
    AST_if_node * if_node = new AST_if_node(0);
    this->consume(TOK_keyword, "if");
    if_node->set_expression(this->parse_subexpression()); // get the expression
    if_node->set_block(this->parse_block()); // get the block
    token * t = this->l->peek();
    if (t->get_name() == TOK_keyword && t->get_attribute() == "else") { // if there is an alternate block
        this->l->get_next_token(); // consume the "else" keyword
        if_node->set_else_block(this->parse_block()); // get the alternate block
    }
    return if_node;
}

/**
 * Parse the number
 * return           the parsed number node
 */
AST_number_node * parser::parse_number() {
    token * t = this->l->get_next_token();
    if (t->get_name() == TOK_int_number) {
        return new AST_int_number_node(0, t->get_attribute());
    } else if (t->get_name() == TOK_real_number) {
        return new AST_real_number_node(0, t->get_attribute());
    } else {
        throw new unexpected_token(t->get_name(), t->get_line());
    }
}

/**
 * Parse the return statement and return the AST node that represents it
 * return           the AST_return_node that is parsed
 */
AST_return_node * parser::parse_return_statement() {
    AST_return_node * return_node = new AST_return_node(0);
    this->consume(TOK_keyword, "return");
    AST_node * expression_node = this->parse_expression();
    return_node->set_expression(expression_node);
    return return_node;
}

/**
 * Parse the simple expression
 * return           the parsed expression node
 */
AST_node * parser::parse_simple_expression() {
    printer_visitor * v = new printer_visitor();
    AST_node * parent = this->parse_term(); // get the first part of the expression
    token * t = this->l->peek();
    vector<AST_node *> terms;
    terms.push_back(parent);
    while ((t->get_name() == TOK_arithmetic && (t->get_attribute() == "+" || t->get_attribute() == "-")) ||
           (t->get_name() == TOK_boolean_operator && t->get_attribute() == "or")) {
        t = this->l->get_next_token(); // get the operator
        AST_node * left = terms.at(terms.size() - 1); // the current side (first part) becomes the left-hand side
        AST_term_node * parent;
        if (t->get_name() == TOK_arithmetic) {
            parent = new AST_arithmetic_term_node(0, t->get_attribute()); // create the parent (additive) operator
        } else {
            parent = new AST_boolean_term_node(0, t->get_attribute()); // create the parent (additive) operator
        }
        parent->set_left_child(left); // set the left-hand side of the operator
        AST_node * right = this->parse_term(); // get the right-hand side of the operator
        parent->set_right_child(right); // set the right-hand side of the operator
        terms.push_back(parent);
        t = this->l->peek();
    }

    return terms.at(terms.size()-1);
}

/**
 * Parse the next statement from the program
 * return           the next statement from the program
 */
AST_statement_node * parser::parse_statement() {
    token * t = this->l->peek();
    AST_statement_node * statement_node;
    switch (t->get_name()) {
        case TOK_keyword:
            if (t->get_attribute() == "var" || t->get_attribute() == "set" || t->get_attribute() == "write" || t->get_attribute() == "return") {
                if (t->get_attribute() == "var") {
                    statement_node = this->parse_var_declaration();
                } else if (t->get_attribute() == "set") {
                    statement_node = this->parse_assignment();
                } else if (t->get_attribute() == "write") {
                    statement_node = this->parse_write_statement();
                } else if (t->get_attribute() == "return") {
                    statement_node = this->parse_return_statement();
                }

                this->consume(TOK_eos);
            } else if (t->get_attribute() == "while") {
                return this->parse_while_statement();
            } else if (t->get_attribute() == "if") {
                return this->parse_if_statement();
            } else if (t->get_attribute() == "def") {
                return this->parse_function_declaration();
            } else {
                throw new unexpected_input(t->get_attribute(), token::token_to_string(TOK_keyword), t->get_line());
            }
            break;
        case TOK_bracket:
            if (t->get_attribute() == "{") {
                return this->parse_block();
            } else {
                throw new unexpected_input(t->get_attribute(), "{", t->get_line());
            }
        default:
            throw new unexpected_token(t->get_name(), t->get_line());
    }
    return statement_node;
}

/**
 * Parse the string
 * return           the string
 */
AST_string_node * parser::parse_string() {
    AST_string_node * ret = new AST_string_node(0, "");
    this->consume(TOK_string_start, "\"");
    if (this->l->peek()->get_name() == TOK_string_start) { // in case of empty string, there is no content
        ret->set_value("");
    } else {
        ret->set_value(this->l->get_next_token()->get_attribute());
    }
    this->consume(TOK_string_start, "\"");
    return ret;
}

/**
 * Parse the sub-expression
 * return           the sub-expression
 */
AST_node * parser::parse_subexpression() {
    AST_node * ret;
    this->consume(TOK_bracket, "(");
    ret = this->parse_expression();
    this->consume(TOK_bracket, ")");
    return ret;
}

/**
 * Parse the term
 * return           the term found
 */
AST_node * parser::parse_term() {
    AST_node * parent = this->parse_factor(); // get the first part of the expression
    token * t = this->l->peek();
    while ((t->get_name() == TOK_arithmetic && (t->get_attribute() == "*" || t->get_attribute() == "/")) ||
            (t->get_name() == TOK_boolean_operator && t->get_attribute() == "and")) { // if there is a right-hand side
        t = this->l->get_next_token(); // get the operator
        AST_node * left = parent; // the current side (first part) becomes the left-hand side
        AST_factor_node * parent;
        if (t->get_name() == TOK_arithmetic) {
            parent = new AST_arithmetic_factor_node(0, t->get_attribute()); // create the parent (multiplicative) operator
        } else {
            parent = new AST_boolean_factor_node(0, t->get_attribute()); // create the parent (multiplicative) operator
        }
        parent->set_left_child(left); // set the left-hand side of the of the operator
        AST_node * right = this->parse_term(); // get the right-hand side of the operator
        parent->set_right_child(right); // set the right-hand side of the operator
        return parent;
    }

    return parent;
}

/**
 * Parse the type
 * return           the parsed type node
 */
AST_type_node * parser::parse_type() {
    token * t = this->l->get_next_token();
    if (t->get_name() == TOK_var_type) {
        return new AST_type_node(0, t->get_attribute());
    } else {
        throw new unexpected_token(t->get_name(), TOK_var_type);
    }
}

/**
 * Parse the unary symbol
 * return           the unary symbol found
 */
AST_node * parser::parse_unary_node() {
    token * t = this->l->get_next_token();
    AST_unary_node * unary = new AST_unary_node(0);
    AST_node * left_expression = this->parse_expression();
    unary->set_type(t->get_attribute());
    unary->set_expression(left_expression);
    return unary;
}

/**
 * Parse the variable declaration and return the AST node that represents it
 * return           the AST_var_declaration_node that is parsed
 */
AST_var_declaration_node * parser::parse_var_declaration() {
    AST_var_declaration_node * var_declaration_node = new AST_var_declaration_node(0);
    this->consume(TOK_keyword, "var");
    var_declaration_node->set_identifier(this->parse_identifier());
    this->consume(TOK_colon);
    var_declaration_node->set_type(this->parse_type());
    this->consume(TOK_assignment, "=");
    var_declaration_node->set_expression(this->parse_expression());
    return var_declaration_node;
}

/**
 * Parse the while statement and return the AST node that represents it
 * return           the AST_while_node that is parsed
 */
AST_while_node * parser::parse_while_statement() {
    AST_while_node * while_node = new AST_while_node(0);
    this->consume(TOK_keyword, "while");
    while_node->set_expression(this->parse_subexpression()); // the next part should be a subexpression
    while_node->set_block(this->parse_block()); // the next part should be a block
    return while_node;
}

/**
 * Parse the write statement and return the AST node that represents it
 * return           the AST_write_node that is parsed
 */
AST_write_statement_node * parser::parse_write_statement() {
    AST_write_statement_node * write_statement_node = new AST_write_statement_node(0);
    this->consume(TOK_keyword, "write");
    AST_node * expression_node = this->parse_expression();
    write_statement_node->set_expression(expression_node);
    return write_statement_node;
}