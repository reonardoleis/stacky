#ifndef VALUE_HPP
#define VALUE_HPP

#include <string>
#include <stdexcept>

class Value {
public:
    enum Type { None, Int, String, Bool };

    Value() : type(None) {}

    Value(int intValue) : type(Int), intValue(intValue) {}

    Value(const std::string& stringValue) : type(String), stringValue(stringValue) {}

    Value(bool boolValue) : type(Bool), boolValue(boolValue) {}

    Value operator+(const Value& other) const;
    Value operator-(const Value& other) const;
    Value operator*(const Value& other) const;
    Value operator/(const Value& other) const;

    std::string getStringValue() const;
    Type type;
    int intValue;
    std::string stringValue;
    bool boolValue;

  
};

#endif  // VALUE_HPP