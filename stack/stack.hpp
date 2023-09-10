#pragma once

#include "../value/value.hpp"
#include "../pair/pair.hpp"
#include <stack>

class Stack {
public:
    Stack();
    void push(Value value);
    Value pop();
    Pair pop2();
    
    std::string toString();

private:
    std::stack<Value> stack;
};