#include "semantic.hpp"

int LC_count;
string fun_name_present;
vector<int> LC_stack;

void Add_LC() {
    LC_count++;
    LC_stack.push_back(LC_count);
}

void Add_RC() { LC_stack.pop_back(); }

string getid(string name) {
    // ID: a   -> a
    return name.substr(4, name.size() - 4);
}

int getint(string tmp) {
    // INT: 5 ->int a=5 return a
    tmp = tmp.substr(5, tmp.size() - 5);
    int res = 0, i = 0, p = 1;
    if (tmp[i] == '-') {
        p = -1;
        i++;
    }
    for (; i < tmp.size(); i++) {
        res = res * 10 + (tmp[i] - '0');
    }
    return res * p;
}

Type *Get_type_exp(Node *node) {
    if (node->children.size() == 0) {
        // ID
        if (node->name.substr(0, 2) == "ID") {
            string id = getid(node->name);
            // cout << "Id = " << id << "\n";
            for (int i = LC_stack.size() - 1; i >= 0; i--) {
                if (is_exist_var(id, LC_stack[i])) {
                    return get_var_type(id, LC_stack[i]);
                } else {
                    continue;
                }
            }
            // cout<<"Type 1: at line ("<<node->line<<") variable "<<id<<" is used without a definition"<<endl;
            return nullptr;
        }
        // INT
        if (node->name.substr(0, 3) == "INT") {
            return get_type_int();
        }
        // FLOAT
        if (node->name.substr(0, 5) == "FLOAT") {
            return get_type_float();
        }
        // CHAR
        if (node->name.substr(0, 4) == "CHAR") {
            return get_type_char();
        }
        return nullptr;
    }
    if (node->children.size() == 1) {
        return Get_type_exp(node->children[0]);
    }
    if (node->children[1]->name == "DOT") {
        // f.member
        Type *t = Get_type_exp(node->children[0]);
        if (t == nullptr) {
            return nullptr;
        }
        if (!is_struct(t)) {
            // cout<<"Type 13 at line ("<<node->line<<" )accessing members of a non-structure variable (i.e., misuse the dot operator)"<<endl;
            return nullptr;
        }
        string struct_name = get_struct_name(t);
        string member_name = getid(node->children[2]->name);
        t = get_struct_member(struct_name, member_name);
        if (t == nullptr) {
            // cout<<"Type 14 at line ("<<node->line<<")accessing an undefined structure member"<<endl;
            return nullptr;
        }
        return t;
    }
    if (node->children[1]->name == "LB") {
        // f[]
        Type *t = Get_type_exp(node->children[0]);
        if (t == nullptr) {
            return nullptr;
        }
        if (!is_type_array(t)) {
            // cout<<"Type 10 at line ("<<node->line<<") applying indexing operator ([...]) on non-array type variables"<<endl;
            return nullptr;
        }
        t = get_array_base(t);
        return t;
    }
    if (node->children[1]->name == "LP") {
        // f(...)
        string id = getid(node->children[0]->name);
        if (!is_exist_fun(id)) {
            bool flag = true;
            for (int i = 0; i <= LC_count; i++) {
                if (is_exist_var(id, i)) {
                    // cout<<"Error type 11 at Line "<<node->line<<": invoking non-function variable: "<<id;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                // cout<<"Type 2 at line ("<<node->line<<") a function is invoked without a definition"<<endl;
            }
            return nullptr;
        }
        return get_fun_return(id);
    }
    for (Node *child : node->children) {
        Type *t = Get_type_exp(child);
        if (t != nullptr) {
            return t;
        }
    }
    return nullptr;
}

int get_args(Node *node) {
    if (node->name == "Args") {
        if (node->children.size() == 1) {
            return get_args(node->children[0]);
        }
        return get_args(node->children[2]) + 1;
    }
    // Exp
    return 1;
}

bool Check_valid_fun_args(string fun_name, Node *node, int count) {
    if (node->name == "Args") {
        if (node->children.size() == 1) {
            return Check_valid_fun_args(fun_name, node->children[0], count);
        }
        if (!Check_valid_fun_args(fun_name, node->children[0], count)) return false;
        return Check_valid_fun_args(fun_name, node->children[2], count + 1);
    }
    // Exp
    return Check_valid_exp(node, get_fun_param_type(fun_name, count));
}

bool Check_valid_assign(Node *node) {
    if (node->name == "ASSIGN") {
        return true;
    }
    if (node->name.substr(0, 2) == "ID") {
        string id = getid(node->name);
        return true;
    }
    if (node->children.size() >= 2 && node->children[1]->name == "DOT") {
        return true;
    }
    if (node->children.size() >= 2 && node->children[1]->name == "LB") {
        return true;
    }
    if (node->name == "Exp") {
        for (Node *child : node->children) {
            if (!Check_valid_assign(child)) return false;
        }
        return true;
    }
    return false;
}

bool Check_valid_exp(Node *node, Type *type) {
    if (node->children.size() == 0) {
        // ID
        if (node->name.substr(0, 2) == "ID") {
            string id = getid(node->name);
            for (int i = LC_stack.size() - 1; i >= 0; i--) {
                if (is_exist_var(id, LC_stack[i])) {
                    return is_same_type(type, get_var_type(id, LC_stack[i]));
                } else {
                    continue;
                }
            }
            // printf("Error type 1 at Line %d: undefined variable: %s\n", node->line, id.c_str());
            return false;
        }
        // INT
        if (node->name.substr(0, 3) == "INT") {
            return type == get_type_int();
        }
        // FLOAT
        if (node->name.substr(0, 5) == "FLOAT") {
            return type == get_type_float();
        }
        // CHAR
        if (node->name.substr(0, 4) == "CHAR") {
            return type == get_type_char();
        }
        return true;
    }
    if (node->children.size() == 1) {
        return Check_valid_exp(node->children[0], type);
    }
    if (node->children[1]->name == "DOT") {
        // f.member
        // get a _type and return _type==type
        Type *t = Get_type_exp(node->children[0]);
        if (!is_struct(t)) {
            // Error type 13 at Line 19: accessing with non-struct variable
            // printf("Error type 13 at Line %d: accessing with non-struct variable\n", node->line);
            return false;
        }
        string struct_name = get_struct_name(t);
        string member_name = getid(node->children[2]->name);
        t = get_struct_member(struct_name, member_name);
        if (t == nullptr) {
            // Error type 14 at Line 10: no such member: age
            // printf("Error type 14 at Line %d: no such member: %s\n", node->line, member_name.c_str());
            return false;
        }
        return is_same_type(t, type);
    }
    if (node->children[1]->name == "LB") {
        // f[]
        Type *t = Get_type_exp(node->children[0]);
        if (!is_type_array(t)) {
            // printf("Error type 10 at Line %d: indexing on non-array variable\n", node->line);
            return false;
        }
        t = get_array_base(t);
        if (!Check_valid_exp(node->children[2], get_type_int())) {
            // Error type 12 at Line 15: indexing by non-integer
            // printf("Error type 12 at Line %d: indexing by non-integer\n", node->line);
        }
        return is_same_type(t, type);
    }
    if (node->children[1]->name == "LP") {
        // f(...)
        string id = getid(node->children[0]->name);
        if (!is_exist_fun(id)) {
            bool flag = true;
            for (int i = 0; i <= LC_count; i++) {
                if (is_exist_var(id, i)) {
                    // cout<<"Error type 11 at Line "<<node->line<<": invoking non-function variable: "<<id<<endl;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                // Error type 2 at Line 8: undefined function: add
                // printf("Error type 2 at Line %d: undefined function: %s\n", node->line, id.c_str());
            }
            return false;
        }
        int count = get_fun_count(id);
        if (node->children.size() == 3) {
            // Error type 9 at Line 12: invalid argument number for compare, expect 2, got 3
            if (count != 0) {
                // printf("Error type 9 at Line %d: invalid argument number for %s, expect %d, got %d\n", node->line,id.c_str(), get_fun_count(id), 0);
            }
        } else {
            if (count != get_args(node->children[2])) {
                // printf("Error type 9 at Line %d: invalid argument number for %s, expect %d, got %d\n", node->line,id.c_str(), count,
                // get_args(node->children[2]));
            } else if (!Check_valid_fun_args(id, node->children[2], 0)) {
                // printf("Error type 9 at Line %d: invalid argument number or type for %s\n", node->line,id.c_str());
            }
        }
        return is_same_type(get_fun_return(id), type);
    }
    for (Node *child : node->children) {
        if (!Check_valid_exp(child, type)) {
            return false;
        }
    }
    return true;
}

void Check_valid_exp(Node *node) {
    if (node->children.size() == 0) {
        if (node->name.substr(0, 2) == "ID") {
            string id = getid(node->name);
            for (int i = LC_stack.size() - 1; i >= 0; i--) {
                if (is_exist_var(id, LC_stack[i])) {
                    return;
                } else {
                    continue;
                }
            }
            // Error type 1 at Line 5: undefined variable: x3
            printf("Error type 1 at Line %d: undefined variable: %s\n", node->line, id.c_str());
            return;
        }
        return;
    }
    if (node->children.size() == 1) {
        Check_valid_exp(node->children[0]);
        return;
    }

    // cout << "Check_valid_exp()" << endl;
    // cout<<node->name<<endl;
    // for(Node*child:node->children) cout<<child->name<< " ";cout<<"\n";
    if (node->children[1]->name == "DOT") {
        // f.member
        // get a _type and return _type==type
        Type *t = Get_type_exp(node->children[0]);
        if (!is_struct(t)) {
            printf("Error type 13 at Line %d: accessing with non-struct variable\n", node->line);
            return;
        }
        string struct_name = get_struct_name(t);
        string member_name = getid(node->children[2]->name);
        // cout << struct_name << endl;
        // cout << member_name << endl;
        t = get_struct_member(struct_name, member_name);
        // cout << "t's info(): " << t->info() << "\n";
        if (t == nullptr) {
            printf("Error type 14 at Line %d: no such member: %s\n", node->line, member_name.c_str());
            return;
        }
        return;
    }
    if (node->children[1]->name == "LB") {
        // f[]
        Type *t = Get_type_exp(node->children[0]);
        if (!is_type_array(t)) {
            // Error type 10 at Line 17: indexing on non-array variable
            printf("Error type 10 at Line %d: indexing on non-array variable\n", node->line);
            return;
        }
        t = get_array_base(t);
        if (!Check_valid_exp(node->children[2], get_type_int())) {
            printf("Error type 12 at Line %d: indexing by non-integer\n", node->line);
        }
        return;
    }
    if (node->children[1]->name == "LP") {
        // f(...)
        string id = getid(node->children[0]->name);
        if (!is_exist_fun(id)) {
            bool flag = true;
            for (int i = 0; i <= LC_count; i++) {
                if (is_exist_var(id, i)) {
                    cout << "Error type 11 at Line " << node->line << ": invoking non-function variable: " << id << endl;
                    flag = false;
                    break;
                }
            }
            if (flag) {
                printf("Error type 2 at Line %d: undefined function: %s\n", node->line, id.c_str());
            }
            return;
        }
        int count = get_fun_count(id);
        if (node->children.size() == 3) {
            // Error type 9 at Line 12: invalid argument number for compare, expect 2, got 3
            if (count != 0) {
                printf("Error type 9 at Line %d: invalid argument number for %s, expect %d, got %d\n", node->line, id.c_str(), get_fun_count(id), 0);
                return;
            }
        } else {
            if (count != get_args(node->children[2])) {
                printf("Error type 9 at Line %d: invalid argument number for %s, expect %d, got %d\n", node->line, id.c_str(), count,
                       get_args(node->children[2]));
                return;
            } else if (!Check_valid_fun_args(id, node->children[2], 0)) {
                printf("Error type 9 at Line %d: invalid argument number or type for %s\n", node->line, id.c_str());
                return;
            }
        }
        return;
    }
    if (node->children.size() == 2) {
        Check_valid_exp(node->children[1]);
        return;
    }
    if (node->children[1]->name == "Exp") {
        Check_valid_exp(node->children[1]);
        return;
    }

    if (node->children[1]->name == "ASSIGN") {
        Check_valid_exp(node->children[0]);
        Check_valid_exp(node->children[2]);
        if (!Check_valid_assign(node->children[0])) {
            // Error type 6 at Line 6: left side in assignment is rvalue
            printf("Error type 6 at Line %d: left side in assignment is rvalue\n", node->line);
            return;
        }
        Type *a = Get_type_exp(node->children[0]);
        Type *b = Get_type_exp(node->children[2]);
        if (!is_same_type(a, b)) {
            // cout << Get_type_exp(node->children[0])->info() << endl;
            // cout << Get_type_exp(node->children[2])->info() << endl;
            // Error type 5 at Line 6: unmatching type on both sides of assignment
            printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", node->line);
            return;
        }
        return;
    }
    Check_valid_exp(node->children[0]);
    Check_valid_exp(node->children[2]);
    /*if (!is_same_type(Get_type_exp(node->children[0]),Get_type_exp(node->children[2]))){
        // Error type 7 at Line 10: binary operation on non-number variables
        printf("Error type 7 at Line %d: binary operation on non-number variables\n", node->line);
    }*/
    Type *a = Get_type_exp(node->children[0]);
    Type *b = Get_type_exp(node->children[2]);
    // printf("line %d: is_int(%d),is_float(%d)\n",node->line,is_int(a),is_float(a));
    if ((!is_int(a) && !is_float(a)) || (!is_int(b) && !is_float(b)) || !is_same_type(a, b)) {
        printf("Error type 7 at Line %d: binary operation on non-number variables\n", node->line);
    }
    return;
}

pair<string, Type *> Solve_VarDec(Node *node, Type *type) {
    if (node->name.substr(0, 2) == "ID") {
        // ID
        return make_pair(getid(node->name), node->type = type);
    }
    if (node->children.size() == 1) {
        return Solve_VarDec(node->children[0], type);
    } else {
        Type *new_type = get_type_array(type, getint(node->children[2]->name));
        pair<string, Type *> tmp = Solve_VarDec(node->children[0], new_type);
        node->type = tmp.second;
        return tmp;
    }
}

void Add_struct_member(string struct_name, Type *type, Node *node) {
    if (node->name == "DecList") {
        for (Node *child : node->children) {
            Add_struct_member(struct_name, type, child);
        }
        return;
    }
    if (node->name == "COMMA") {
        return;
    }
    if (node->name == "Dec") {
        Add_struct_member(struct_name, type, node->children[0]);
        if (node->children.size() == 3) {
            Check_valid_exp(node->children[2]);
            if (!Check_valid_exp(node->children[2], node->children[0]->type)) {
                // 				cout << Get_type_exp(node->children[0])->info() << endl;
                // cout << Get_type_exp(node->children[2])->info() << endl;
                printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", node->line);
            }
        }
        return;
    }
    if (node->name == "VarDec") {
        pair<string, Type *> tmp = Solve_VarDec(node, type);
        struct_add_member(struct_name, tmp.first, tmp.second);
        node->type = tmp.second;
    }
}

void Build_struct(string struct_name, Node *node) {
    if (node->name == "DefList") {
        for (Node *child : node->children) {
            Build_struct(struct_name, child);
        }
        return;
    }
    if (node->name == "Def") {
        Build_type(node->children[0]);
        Add_struct_member(struct_name, node->children[0]->type, node->children[1]);
    }
}

void Build_type(Node *node) {
    // Specifier
    if (node->name == "Specifier") {
        Build_type(node->children[0]);
        node->type = node->children[0]->type;
        return;
    }
    if (node->name == "TYPE: int") {
        node->type = get_type_int();
        return;
    }
    if (node->name == "TYPE: float") {
        node->type = get_type_float();
        return;
    }
    if (node->name == "TYPE: char") {
        node->type = get_type_char();
        return;
    }
    if (node->name == "StructSpecifier") {
        if (node->children.size() == 4) {
            generate_struct(getid(node->children[1]->name), node->line);
        }
        if (node->children.size() == 5) {
            generate_struct(getid(node->children[1]->name), node->line);
            Build_struct(getid(node->children[1]->name), node->children[3]);
        }
        node->type = get_type_struct(getid(node->children[1]->name));
        return;
    }
}

void Build_fun_var(string fun_name, Node *node, int cnt) {
    // VarList
    if (node->name == "VarList") {
        Build_fun_var(fun_name, node->children[0], cnt);
        cnt++;
        if (node->children.size() == 3) {
            Build_fun_var(fun_name, node->children[2], cnt);
        }
    }
    if (node->name == "COMMA") {
        return;
    }
    if (node->name == "ParamDec") {
        Build_type(node->children[0]);
        pair<string, Type *> tmp = Solve_VarDec(node->children[1], node->children[0]->type);
        fun_add_var(tmp.second, fun_name, cnt);
        generate_var(tmp.first, LC_stack[LC_stack.size() - 1], tmp.second, node->line);
    }
}

bool Build_fun(Type *type, Node *node) {
    // FunDec
    if (is_exist_fun(getid(node->children[0]->name))) {
        cout << "Error type 4 at Line " << to_string(node->line) << ": redefine function: " << getid(node->children[0]->name) << "\n";
        return false;
    }
    generate_fun(type, getid(node->children[0]->name));
    fun_name_present = getid(node->children[0]->name);
    if (node->children.size() == 4) {
        Build_fun_var(getid(node->children[0]->name), node->children[2], 0);
    }
    return true;
}

void Build_global_var(Type *type, Node *node) {
    // cout << "Build_global_var" << endl;
    // ExtDecList
    pair<string, Type *> tmp = Solve_VarDec(node->children[0], type);
    generate_var(tmp.first, 0, tmp.second, node->line);
    if (node->children.size() == 3) {
        Build_global_var(type, node->children[2]);
    }
}

void Build_var(Type *type, Node *node) {
    // DecList
    if (node->name == "DecList") {
        Build_var(type, node->children[0]);
        if (node->children.size() == 3) {
            Build_var(type, node->children[2]);
        }
    }
    if (node->name == "Dec") {
        Build_var(type, node->children[0]);
        if (node->children.size() == 3) {
            Check_valid_exp(node->children[2]);
            if (!Check_valid_exp(node->children[2], node->children[0]->type)) {
                // 			cout << Get_type_exp(node->children[0])->info() << endl;
                // cout << Get_type_exp(node->children[2])->info() << endl;
                printf("Error type 5 at Line %d: unmatching type on both sides of assignment\n", node->line);
            }
        }
        return;
    }
    if (node->name == "VarDec") {
        pair<string, Type *> tmp = Solve_VarDec(node, type);
        generate_var(tmp.first, LC_stack[LC_stack.size() - 1], tmp.second, node->line);
        node->type = tmp.second;
        return;
    }
}

void Build(Node *node) {
    if (node == nullptr) {
        return;
    }
    if (node->name == "ExtDef") {
        // cout<<node->line<<endl;
        // for (Node *child: node->children) {
        // 	cout<<child->name<<" ";
        // }
        // cout<<endl;

        Build_type(node->children[0]);
        if (node->children[1]->name == "ExtDecList") {
            // Specifier ExtDecList SEMI
            Build_global_var(node->children[0]->type, node->children[1]);
        } else if (node->children[1]->name == "FunDec") {
            // Specifier FunDec CompSt
            Add_LC();
            if (Build_fun(node->children[0]->type, node->children[1])) {
                Build(node->children[2]);
            }
            Add_RC();
        } else {
            // Specifier SEMI
            /* do nothing */
        }
        return;
    }
    if (node->name == "CompSt") {
        Build(node->children[1]);  // def
        Build(node->children[2]);  // stmt
        return;
    }
    if (node->name == "DefList") {
        for (Node *child : node->children) {
            Build(child);
        }
        return;
    }
    if (node->name == "StmtList") {
        for (Node *child : node->children) {
            Build(child);
        }
        return;
    }
    if (node->name == "Def") {
        Build_type(node->children[0]);
        Build_var(node->children[0]->type, node->children[1]);

        return;
    }
    if (node->name == "Stmt") {
        if (node->children[0]->name == "CompSt") {
            Add_LC();
            Build(node->children[0]);
            Add_RC();
            return;
        }
        if (node->children[0]->name == "RETURN") {
            Check_valid_exp(node->children[1]);
            if (!Check_valid_exp(node->children[1], get_fun_return(fun_name_present))) {
                // Error type 8 at Line 21: incompatiable return type
                printf("Error type 8 at Line %d: incompatiable return type\n", node->line);
            }
            return;
        }
        for (Node *child : node->children) {
            Build(child);
        }
        return;
    }
    if (node->name == "Exp") {
        Check_valid_exp(node);
        return;
    }
    for (Node *child : node->children) {
        Build(child);
    }
}

void init() {
    // 开始加入read()和write()
    generate_fun(get_type_int(), "read");
    generate_fun(get_type_int(), "write");
    fun_add_var(get_type_int(), "write", 0);
}