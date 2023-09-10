#pragma once

#include "../value/value.hpp"

class Pair
{
public:
    Pair() {}
    Pair(Value first) : _first(first) {}
    Pair(Value first, Value second) : _first(first), _second(second) {}
    Value first();
    Value second();
    void first(Value first);
    void second(Value second);

private:
    Value _first;
    Value _second;
};