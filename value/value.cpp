#include "value.hpp"
#include <iostream>
Value Value::operator+(const Value& other) const {
    if ((type == Int && other.type == Int) || (type == Bool && other.type == Bool)) {
        return Value(intValue + other.intValue);
    } else if (type == String || other.type == String) {
        return Value(getStringValue() + other.getStringValue());
    } else {
        throw std::runtime_error("+ is not supported with boolean values");
    }
}

Value Value::operator-(const Value& other) const {
    if ((type == Int && other.type == Int) || (type == Bool && other.type == Bool)) {
        return Value(intValue - other.intValue);
    } else if (type == String || other.type == String) {
        throw std::runtime_error("- is not supported with string values");
    } else {
        throw std::runtime_error("- is not supported with boolean values");
    }
}

Value Value::operator*(const Value& other) const {
    if ((type == Int && other.type == Int) || (type == Bool && other.type == Bool)) {
        return Value(intValue * other.intValue);
    } else if (type == String || other.type == String) {
        throw std::runtime_error("* is not supported with string values");
    } else {
        std::cout << type << " - " << other.type << std::endl;
        throw std::runtime_error("* is not supported with boolean values");
    }
}

std::string Value::getStringValue() const {
    if (type == String) {
        return stringValue;
    } else if (type == Int) {
        return std::to_string(intValue);
    } else if (type == Bool) {
        return boolValue ? "true" : "false";
    } else {
        throw std::runtime_error("Tipo inválido.");
    }
}