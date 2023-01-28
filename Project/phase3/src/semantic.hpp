#include <iostream>
#include "node.hpp"
#include "type.hpp"
#include "symbol.hpp"

using namespace std;

void Build_struct(string struct_name, Node *node);

void Build_type(Node *node);

void Add_struct_member(string struct_name, Type *type, Node *node);

void Check_valid_exp(Node *node);

bool Check_valid_exp(Node *node, Type *type);

bool Build_fun(Type *type, Node *node);

void Build_fun_var(string fun_name, Node *node, int cnt);

pair<string, Type *> Solve_VarDec(Node *node, Type *type);

void Build(Node *node);

void init();