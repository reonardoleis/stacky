#include "pair.hpp"

Value Pair::first() 
{
    return _first;
}

Value Pair::second()
{
    return _second;
}

void Pair::first(Value first)
{
    _first = first;
}

void Pair::second(Value second)
{
    _second = second;
}