#include "stack.hpp"

Stack::Stack()
{
    stack = std::stack<Value>();
}


void Stack::push(Value value)
{
    stack.push(value);
}

Value Stack::pop()
{
    Value stackTop = stack.top();
    stack.pop();
    return stackTop;
}

Pair Stack::pop2()
{
    Pair p;
    Value stackTop = stack.top();
    p.first(stackTop);
    stack.pop();
    stackTop = stack.top();
    p.second(stackTop);
    stack.pop();
    
    return p;
}

std::string Stack::toString()
{
    std::string result = "[ ";
    std::stack<Value> tempStack = stack;

    while (!tempStack.empty())
    {
        result += tempStack.top().getStringValue() + " ";
        tempStack.pop();
    }

    result += "]";

    return result;
}