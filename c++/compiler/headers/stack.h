//
// Created by memonick on 19/04/2016.
//

#ifndef LEXER_STACK_H
#define LEXER_STACK_H

#include "exceptions/stack_empty_exception.h"

#include <vector>

using namespace std;

template <class Type>

class stack {

    public:
        stack();

        Type peek();
        Type peek(unsigned i);
        Type pop();
        void push(Type t);
        unsigned size();

    private:
        vector<Type> v;

};

template <typename Type>
stack<Type>::stack() {}

template <typename Type>
Type stack<Type>::peek(unsigned i) {
    return this->v.at(v.size() - i - 1);
}

template <typename Type>
Type stack<Type>::peek() {
    return this->peek(0);
}

template <typename Type>
Type stack<Type>::pop() {
    Type t = this->v.at(v.size() - 1);
    this->v.pop_back();
    return t;
}

template <typename Type>
void stack<Type>::push(Type t) {
    this->v.push_back(t);
}

template <typename Type>
unsigned stack<Type>::size() {
    return this->v.size();
}

#endif //LEXER_STACK_H