#pragma once

#include <iostream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>
#include "node.hpp"

using namespace std;

string translate_Program(Node *node);
string translate_ExtDefList(Node *node);
string translate_ExtDef(Node *node);
string translate_ExtDecList(Node *node);
string translate_Specifier(Node *node);
string translate_StructSpecifier(Node *node);
string translate_VarDec(Node *node);
string translate_FunDec(Node *node);
string translate_VarList(Node *node);
string translate_ParamDec(Node *node);
string translate_CompSt(Node *node);
string translate_StmtList(Node *node);
string translate_Stmt(Node *node);
string translate_DefList(Node *node);
string translate_Def(Node *node);
string translate_DecList(Node *node);
string translate_Dec(Node *node);
string translate_Exp(Node *node, const string &place);
string translate_Cond_Exp(Node *node, const string &lb_t, const string &lb_f);
string translate_Args(Node *node, vector<string> &arg_list);

string translate(Node *root);