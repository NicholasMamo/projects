//
// Created by memonick on 19/04/2016.
//

#include "../../headers/symbol_table/symbol_table.h"

/**
 * Initialize the symbol table
 */
symbol_table::symbol_table() {}

/**
 * Add a variable with the given name into the symbol table
 * s_name           the name of the variable to add
 */
void symbol_table::add_symbol(string s_name) {
    if (this->is_in_scope(s_name) && !this->is_function(s_name)) {
        this->remove(s_name);
    }
    this->variables.push_back(new symbol_var(s_name));
}

/**
 * Add the given variable into the symbol table
 * s_name           the name of the variable to add
 */
void symbol_table::add_symbol(symbol_var var) {
    if (this->is_in_scope(var.get_name()) && !this->is_function(var.get_name())) {
        this->remove(var.get_name());
    }
    this->variables.push_back(symbol_var::clone(var));
}

/**
 * Add a function with the given into the symbol table
 * function         the function to add
 */
void symbol_table::add_symbol(AST_func_declaration_node * function) {
    string s_name = function->get_identifier()->get_name();
    if (!this->is_in_scope(s_name) || !this->is_function(s_name)) {
        symbol_func * func = new symbol_func(s_name);
        func->set_type(symbol::string_to_type(function->get_type()->get_type()));
        func->set_body(function->get_block());
        func->set_parameters(function->get_formal_parameters());
        this->functions.push_back(func);
    }
}

/**
 * Set the type of the variable with the given name to the one provided
 * value            the new value of the variable
 */
void symbol_table::set_type(string s_name, var_type type) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            this->variables.at(i)->set_type(type);
        }
    }
}

/**
 * Set the value of the variable with the given name to the one provided
 * value            the new value of the variable
 */
void symbol_table::set_value(string s_name, int value) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            this->variables.at(i)->set_value(value);
        }
    }
}

/**
 * Set the value of the variable with the given name to the one provided
 * value            the new value of the variable
 */
void symbol_table::set_value(string s_name, double value) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            this->variables.at(i)->set_value(value);
        }
    }
}

/**
 * Set the value of the variable with the given name to the one provided
 * value            the new value of the variable
 */
void symbol_table::set_value(string s_name, bool value) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            this->variables.at(i)->set_value(value);
        }
    }
}

/**
 * Set the value of the variable with the given name to the one provided
 * value            the new value of the variable
 */
void symbol_table::set_value(string s_name, string value) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            this->variables.at(i)->set_value(value);
        }
    }
}

/**
 * Go through the functions and retrieve the function with the given name
 * s_name           the name of the function
 * return           the function
 */
symbol_func * symbol_table::get_function(string s_name) {
    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name) {
            return this->functions.at(i);
        }
    }
    return new symbol_func("");
}

/**
 * Go through the variables and retrieve the variable with the given name
 * s_name           the name of the variable
 * return           the variable
 */
symbol_var * symbol_table::get_variable(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            return this->variables.at(i);
        }
    }
    return new symbol_var("");
}

/**
 * Go through the functions and retrieve the type of the function with the given name
 * s_name           the name of the function
 * return           the type of the function
 */
var_type symbol_table::get_function_type(string s_name) {
    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name) {
            return this->functions.at(i)->get_type();
        }
    }
    return type_other;
}

AST_formal_parameters_node * symbol_table::get_parameters(string s_name) {
    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name) {
            return this->functions.at(i)->get_parameters();
        }
    }
    throw new undeclared_func_exception(s_name);
}

/**
 * Go through the variables and retrieve the string value of the variable with the given name
 * s_name           the name of the variable
 * return           the string value of the variable
 */
string symbol_table::get_string_value(string s_name) {
    string s = "";
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            symbol_var * variable = this->variables.at(i);
            if(variable->get_type() == type_string) {
                s = variable->get_string_value();
                return s;
            }
        }
    }
    return s;
}

/**
 * Go through the variables and retrieve the type of the variable with the given name
 * s_name           the name of the variable
 * return           the type of the variable
 */
var_type symbol_table::get_type(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            return this->variables.at(i)->get_type();
        }
    }
    return type_other;
}

/**
 * Go through the variables and retrieve the value of the variable with the given name
 * s_name           the name of the variable
 * return           the value of the variable
 */
var_value symbol_table::get_value(string s_name) {
    var_value v = {-1};
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            symbol_var * variable = this->variables.at(i);
            switch(variable->get_type()) {
                case type_int:
                    v.i = variable->get_int_value();
                    break;
                case type_real:
                    v.d = variable->get_real_value();
                    break;
                case type_bool:
                    v.b = variable->get_bool_value();
                    break;
            }
        }
    }
    return v;
}

/**
 * Remove the variable (never called for functions) with the given name
 * s_name           the name of the variable to remove
 * return           a boolean indicating whether the variable was found and removed (true), or not (false)
 */
bool symbol_table::remove(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            this->variables.erase(this->variables.begin() + i);
            return true;
        }
    }
    return false;
}

/**
 * Go through the variables and functions and check whether the variable or function with the given name is declared
 * s_name           the name of the symbol (variable or function)
 * return           a boolean indicating whether the symbol with the given name is declared in the scope (true), or not (false)
 */
bool symbol_table::is_in_scope(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name) {
            return true;
        }
    }

    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name) {
            return true;
        }
    }

    return false;
}

/**
 * Go through the functions and check whether the function with the given name is declared
 * s_name           the name of the function
 * return           a boolean indicating whether the function with the given name is declared (true), or not (false)
 */
bool symbol_table::is_function(string s_name) {
    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name) {
            return true;
        }
    }
    return false;
}

/**
 * Go through the variables and functions and check whether the variable or function with the given name returns an integer or not
 * s_name           the name of the symbol (variable or function)
 * return           a boolean indicating whether the symbol with the given name returns an integer (true), or not (false)
 */
bool symbol_table::is_int(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name && this->variables.at(i)->get_type() == type_int) {
            return true;
        }
    }

    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name && this->functions.at(i)->get_type() == type_int) {
            return true;
        }
    }

    return false;
}

/**
 * Go through the variables and functions and check whether the variable or function with the given name returns a real value or not
 * s_name           the name of the symbol (variable or function)
 * return           a boolean indicating whether the symbol with the given name returns a real value (true), or not (false)
 */
bool symbol_table::is_real(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name && this->variables.at(i)->get_type() == type_real) {
            return true;
        }
    }

    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name && this->functions.at(i)->get_type() == type_real) {
            return true;
        }
    }

    return false;
}

/**
 * Go through the variables and functions and check whether the variable or function with the given name returns a boolean value or not
 * s_name           the name of the symbol (variable or function)
 * return           a boolean indicating whether the symbol with the given name returns a boolean value (true), or not (false)
 */
bool symbol_table::is_bool(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name && this->variables.at(i)->get_type() == type_bool) {
            return true;
        }
    }

    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name && this->functions.at(i)->get_type() == type_bool) {
            return true;
        }
    }

    return false;
}

/**
 * Go through the variables and functions and check whether the variable or function with the given name returns a string or not
 * s_name           the name of the symbol (variable or function)
 * return           a boolean indicating whether the symbol with the given name returns a string (true), or not (false)
 */
bool symbol_table::is_string(string s_name) {
    for (unsigned i = 0; i < this->variables.size(); i++) {
        if (this->variables.at(i)->get_name() == s_name && this->variables.at(i)->get_type() == type_string) {
            return true;
        }
    }

    for (unsigned i = 0; i < this->functions.size(); i++) {
        if (this->functions.at(i)->get_name() == s_name && this->functions.at(i)->get_type() == type_string) {
            return true;
        }
    }

    return false;
}

/**
 * Clone the given symbol table and return the clone
 * other            the symbol table to clone
 * retun            the cloned symbol table
 */
symbol_table * symbol_table::clone(const symbol_table * other) {
    symbol_table * new_symbol_table = new symbol_table();
    for (unsigned i = 0; i < other->variables.size(); i++) {
        symbol_var * variable = other->variables.at(i);
        new_symbol_table->add_symbol(variable->get_name());
        switch(variable->get_type()) {
            case type_int:
                new_symbol_table->set_value(other->variables.at(i)->get_name(), variable->get_int_value());
                break;
            case type_real:
                new_symbol_table->set_value(other->variables.at(i)->get_name(), variable->get_real_value());
                break;
            case type_bool:
                new_symbol_table->set_value(other->variables.at(i)->get_name(), variable->get_bool_value());
                break;
            case type_string:
                new_symbol_table->set_value(other->variables.at(i)->get_name(), variable->get_string_value());
                break;
        }
    }

    for (unsigned i = 0; i < other->functions.size(); i++) {
        AST_func_declaration_node * function_clone = new AST_func_declaration_node(0);
        symbol_func * function = other->functions.at(i);
        function_clone->set_identifier(new AST_identifier_node(0, function->get_name()));
        function_clone->set_type(new AST_type_node(0, symbol::type_to_string(function->get_type())));
        function_clone->set_formal_parameters(function->get_parameters());
        function_clone->set_block(function->get_body());
        new_symbol_table->add_symbol(function_clone);
    }

    return new_symbol_table;
}

/**
 * Get the textual representation of the symbol table
 * return           the textual representation of the symbol table
 */
string symbol_table::to_string() {
    string s = "";
    s += "variables: \n";
    for (unsigned i = 0; i < this->variables.size(); i++) {
        s += this->variables.at(i)->to_string() + "\n";
    }

    s += "\n";
    s += "functions: \n";
    for (unsigned i = 0; i < this->functions.size(); i++) {
        s += this->functions.at(i)->to_string() + "\n";
    }

    return s;
}

/**
 * Clear the list of replaced variables
 */
void symbol_table::clear_replaced() {
    this->replaced_variables.clear();
}

/**
 * Check whether the variable with the given name has been replaced or not
 * s_name           the name of the variable
 * return           a boolean indicating whether the variable has been replaced (true), or not (false)
 */
bool symbol_table::is_replaced(string s_name) {
    for (unsigned i = 0; i < this->replaced_variables.size(); i++) {
        if (this->replaced_variables.at(i).get_name() == s_name) {
            return true;
        }
    }

    return false;
}

/**
 * Set the variable given to indicate to have been replacced
 * var              the variable that will be marked as having been replaced
 */
void symbol_table::set_replaced(symbol_var var) {
    this->replaced_variables.push_back(var);
}