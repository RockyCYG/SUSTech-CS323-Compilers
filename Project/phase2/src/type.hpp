#pragma once

#include <string>

using namespace std;

class Type;

class Array;

class FieldList;

enum class Category {
    PRIMITIVE, ARRAY, STRUCTURE
};

enum class Primitive {
    INT, FLOAT, CHAR
};

union InnerType {
    Primitive primitive;
    Array *array;
    FieldList *structure;
};

class Type {
public:
    string name;
    Category category{};
    InnerType innerType{};

    Type() = default;

    Type(string name, Category category, InnerType innerType) : name(std::move(name)), category(category),
                                                                innerType(innerType) {}
    
    string info() {
        if (category == Category::PRIMITIVE) {
            if (innerType.primitive == Primitive::INT) {
                return "INT";
            } else if (innerType.primitive == Primitive::FLOAT) {
                return "FLOAT";
            } else {
                return "CHAR";
            }
        } else if (category == Category::ARRAY) {
            return "ARRAY"; 
        } else {
            return "STRUCTURE: " + name;
        }
    }
};

class Array {
public:
    Type *base{};
    int size{};

    Array() = default;

    Array(Type *base, int size) : base(base), size(size) {}
};

class FieldList {
public:
    string name;
    Type *type{};
    FieldList *next{};

    FieldList() = default;

    FieldList(string name, Type *type, FieldList *next) : name(std::move(name)), type(type), next(next) {}
};