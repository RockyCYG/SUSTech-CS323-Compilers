#pragma once

#include <iostream>
#include <unordered_map>
#include <utility>
#include <functional>
#include "type.hpp"

using namespace std;

void print_error(int type, int line, const string &message);

Type *get_type_int();

Type *get_type_float();

Type *get_type_char();

Type *get_type_struct(const string &struct_name);

Type *get_type_array(Type *base, int len);

bool is_exist_var(const string &var_name, int scope);

bool is_exist_fun(const string &fun_name);

bool is_type_array(Type *type);

bool is_int(Type *type);

bool is_float(Type *type);

bool is_struct(Type *type);

Type *get_array_base(Type *type);

Type *get_var_type(const string &var_name, int scope);

Type *get_fun_return(const string &fun_name);

int get_fun_count(const string &fun_name);

Type *get_fun_param_type(const string &fun_name, int id);

void generate_fun(Type *type, const string &fun_name);

void fun_add_var(Type *type, const string &fun_name, int id);

void generate_struct(const string &struct_name, int line);

void struct_add_member(const string &struct_name, const string &member_name, Type *type);

void generate_var(const string &var_name, int scope, Type *type, int line);

Type *get_struct_member(const string &struct_name, const string &member_name);

string get_struct_name(Type *type);

bool is_same_type(Type *a, Type *b);

void print_all_variables();

void print_all_member(const string &struct_name);