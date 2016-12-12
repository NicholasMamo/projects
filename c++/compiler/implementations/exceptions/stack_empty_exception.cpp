//
// Created by memonick on 19/04/2016.
//

#include "../../headers/exceptions/stack_empty_exception.h"

stack_empty_exception::stack_empty_exception() {}

string stack_empty_exception::to_string() {
    return this->message;
}