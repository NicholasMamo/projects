//
// Created by memonick on 19/04/2016.
//

#include "../../headers/symbol_table/symbol_var.h"

/**
 * Initialize the variable with the given name
 * name             the name of the variable
 */
symbol_var::symbol_var(string name): symbol(name) {}

/**
 * Initialize the variable with the given name and value
 * name             the name of the variable
 * value            the value of the variable
 */
symbol_var::symbol_var(string name, int value): symbol(name) {
    this->set_value(value);
}

/**
 * Initialize the variable with the given name and value
 * name             the name of the variable
 * value            the value of the variable
 */
symbol_var::symbol_var(string name, double value): symbol(name) {
    this->set_value(value);
}

/**
 * Initialize the variable with the given name and value
 * name             the name of the variable
 * value            the value of the variable
 */
symbol_var::symbol_var(string name, bool value): symbol(name) {
    this->set_value(value);
}

/**
 * Initialize the variable with the given name and value
 * name             the name of the variable
 * value            the value of the variable
 */
symbol_var::symbol_var(string name, string value): symbol(name) {
    this->set_value(value);
}

/**
 * Perform addition with this variable and the one given
 * other            the variable to use in conjunction with addition
 * return           the addition of this variable and the one given
 */
symbol_var symbol_var::operator+(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 + operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 + operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 + operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 + operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform subtraction with this variable and the one given
 * other            the variable to use in conjunction with subtraction
 * return           the subtraction of this variable and the one given
 */
symbol_var symbol_var::operator-(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 - operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 - operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 - operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 - operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform multiplication with this variable and the one given
 * other            the variable to use in conjunction with multiplication
 * return           the multiplication of this variable and the one given
 */
symbol_var symbol_var::operator*(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 * operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 * operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 * operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 * operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform division with this variable and the one given
 * other            the variable to use in conjunction with division
 * return           the division of this variable and the one given
 */
symbol_var symbol_var::operator/(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    if (operand_1 % operand_2 != 0) {
                        result.set_value((double)(operand_1) / operand_2);
                    } else {
                        result.set_value(operand_1 / operand_2);
                    }
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 / operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 / operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 / operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform a "less than" comparison with this variable and the one given
 * other            the variable to use in conjunction with "less than"
 * return           the "less than" comparison of this variable and the one given
 */
symbol_var symbol_var::operator<(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 < operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 < operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 < operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 < operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform a "less than or equal to" comparison with this variable and the one given
 * other            the variable to use in conjunction with "less than or equal to"
 * return           the "less than or equal to" comparison of this variable and the one given
 */
symbol_var symbol_var::operator<=(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 <= operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 <= operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 <= operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 <= operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform a "greater than" comparison with this variable and the one given
 * other            the variable to use in conjunction with "greater than"
 * return           the "greater than" comparison of this variable and the one given
 */
symbol_var symbol_var::operator>(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 > operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 > operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 > operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 > operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform a "greater than or equal to" comparison with this variable and the one given
 * other            the variable to use in conjunction with "greater than or equal to"
 * return           the "greater than or equal to" comparison of this variable and the one given
 */
symbol_var symbol_var::operator>=(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 >= operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 >= operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 >= operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 >= operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_real);
    }
}

/**
 * Perform an equality comparison with this variable and the one given
 * other            the variable to use in conjunction with equality
 * return           the equality comparison of this variable and the one given
 */
symbol_var symbol_var::operator==(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this) && symbol_var::is_number_type(other)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 == operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 == operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 == operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 == operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else if (this->get_type() == other.get_type()) {
        if (this->get_type() == type_string) {
            result.set_value(this->get_string_value() == other.get_string_value());
        } else if (this->get_type() == type_bool) {
            result.set_value(this->get_bool_value() == other.get_bool_value());
        }

        return result;
    } else {
        throw new incompatible_types_exception(other.get_type(), this->get_type());
    }
}

/**
 * Perform an inequality comparison with this variable and the one given
 * other            the variable to use in conjunction with inequality
 * return           the inequality comparison of this variable and the one given
 */
symbol_var symbol_var::operator!=(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (symbol_var::is_number_type(*this) && symbol_var::is_number_type(other)) {
        if (symbol_var::is_number_type(other)) {
            if (this->type == type_int) {
                int operand_1 = this->get_int_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 != operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 != operand_2);
                }
            } else if (this->type == type_real) {
                double operand_1 = this->get_real_value();
                if (other.type == type_int) {
                    int operand_2 = other.get_int_value();
                    result.set_value(operand_1 != operand_2);
                } else if (other.type == type_real) {
                    double operand_2 = other.get_real_value();
                    result.set_value(operand_1 != operand_2);
                }
            }
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_real);
        }
    } else if (this->get_type() == other.get_type()) {
        if (this->get_type() == type_string) {
            result.set_value(this->get_string_value() != other.get_string_value());
        } else if (this->get_type() == type_bool) {
            result.set_value(this->get_bool_value() != other.get_bool_value());
        }

        return result;
    } else {
        throw new incompatible_types_exception(other.get_type(), this->get_type());
    }
}

/**
 * Perform a "boolean or" comparison with this variable and the one given
 * other            the variable to use in conjunction with "boolean or"
 * return           the "boolean or" comparison of this variable and the one given
 */
symbol_var symbol_var::operator||(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (this->get_type() == type_bool) {
        if (other.get_type() == type_bool) {
            result.set_value(this->get_bool_value() || other.get_bool_value());
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_bool);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_bool);
    }
}

/**
 * Perform a "boolean and" comparison with this variable and the one given
 * other            the variable to use in conjunction with "boolean and"
 * return           the "boolean and" comparison of this variable and the one given
 */
symbol_var symbol_var::operator&&(symbol_var& other) {
    symbol_var result = symbol_var("");
    if (this->get_type() == type_bool) {
        if (other.get_type() == type_bool) {
            result.set_value(this->get_bool_value() && other.get_bool_value());
            return result;
        } else {
            throw new incompatible_types_exception(other.get_type(), type_bool);
        }
    } else {
        throw new incompatible_types_exception(this->get_type(), type_bool);
    }
}

/**
 * Perform a "unary not" with this variable and the one given
 * other            the variable to use in conjunction with "unary not"
 * return           the "unary not" comparison of this variable and the one given
 */
symbol_var symbol_var::operator!() {
    symbol_var result = symbol_var("");
    if (this->get_type() == type_bool) {
        result.set_value(!this->get_bool_value());
        return result;
    } else {
        throw new incompatible_types_exception(this->get_type(), type_bool);
    }
}

/**
 * Set the value of the variable as an int
 * value            the new int value of the variable
 */
void symbol_var::set_value(int value) {
    this->value.i = value;
    this->type = type_int;
}

/**
 * Set the value of the variable as a double
 * value            the new double value of the variable
 */
void symbol_var::set_value(double value) {
    this->value.d = value;
    this->type = type_real;
}

/**
 * Set the value of the variable as a boolean
 * value            the new boolean value of the variable
 */
void symbol_var::set_value(bool value) {
    this->value.b = value;
    this->type = type_bool;
}

/**
 * Set the value of the variable as a string
 * value            the new string value of the variable
 */
void symbol_var::set_value(string value) {
    this->s = value;
    this->type = type_string;
}

/**
 * Get the integral value of the variable
 * return           the integral value of the variable
 */
int symbol_var::get_int_value() {
    if (this->type == type_int) {
        return this->value.i;
    } else {
        return -1;
    }
}

/**
 * Get the real value of the variable
 * return           the real value of the variable
 */
double symbol_var::get_real_value() {
    if (this->type == type_real) {
        return this->value.d;
    } else {
        return -1;
    }
}

/**
 * Get the boolean value of the variable
 * return           the boolean value of the variable
 */
bool symbol_var::get_bool_value() {
    if (this->type == type_bool) {
        return this->value.b;
    } else {
        return false;
    }
}

/**
 * Get the string value of the variable
 * return           the string value of the variable
 */
string symbol_var::get_string_value() {
    if (this->type == type_string) {
        return this->s;
    } else {
        return "";
    }
}

/**
 * Get the textual representation of the variable's value
 * return           the textual representation of the variable's value
 */
string symbol_var::value_to_string() {
    switch (this->type) {
        case type_int:
            return std::to_string(this->value.i);
        case type_real:
            return std::to_string(this->value.d);
        case type_bool:
            return (this->value.b ? "true" : "false");
        case type_string:
            return this->s;
        default:
            return "";
    }
}

/**
 * Get the textual representation of the variable
 * return           the textual representation of the variable
 */
string symbol_var::to_string() {
    return this->name + ": " + symbol_var::type_to_string(this->type) + " = " + this->value_to_string();
}

/**
 * Clone the given variable and return the new one
 * var              the variable to clone
 * return           the cloned variable
 */
symbol_var * symbol_var::clone(symbol_var var) {
    symbol_var * new_var = new symbol_var(var.get_name());
    switch(var.get_type()) {
        case type_int:
            new_var->set_value(var.get_int_value());
            break;
        case type_real:
            new_var->set_value(var.get_real_value());
            break;
        case type_bool:
            new_var->set_value(var.get_bool_value());
            break;
        case type_string:
            new_var->set_value(var.get_string_value());
            break;
    }
    return new_var;
}

/**
 * Check whether the given variable is a number or not
 * var              the variable to check
 * return           a boolean indicating whether the variable is a number (true), or not (false)
 */
bool symbol_var::is_number_type(symbol_var var) {
    return (var.get_type() == type_int || var.get_type() == type_real);
}

/**
 * Reduce the given variables to a variable type
 * var_1            the first variable to check
 * var_2            the second variable to check
 * return           a boolean indicating whether the variable is a number (true), or not (false)
 */
var_type symbol_var::reduce(symbol_var var_1, symbol_var var_2) {
    var_type type_1 = var_1.get_type();
    var_type type_2 = var_2.get_type();
    if (type_1 == type_2) {
        return type_1;
    } else if ((type_1 == type_int && type_2 == type_real) || (type_1 == type_real && type_2 == type_int)) {
        return type_real;
    } else {
        if (!symbol_var::is_number_type(var_1)) {
            throw new incompatible_types_exception(type_1);
        } else if (!symbol_var::is_number_type(var_2)) {
            throw new incompatible_types_exception(type_2);
        }
    }
}