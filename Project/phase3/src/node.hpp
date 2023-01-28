#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "type.hpp"

using namespace std;

class Node {
public:
    int line;
    bool flag; // 是否是token
    string name;
    vector<Node *> children;
    Type *type;

    Node(int line, bool flag, string name) : line(line), flag(flag), name(std::move(name)) {}

    void addEdge(Node *child) { children.push_back(child); }
};

void printAST(Node *node, int level);