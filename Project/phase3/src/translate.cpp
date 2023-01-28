#include "translate.hpp"

// 程序变量名 -> 寄存器v开头的名称 ({var_name: v_name})
unordered_map<string, string> vars_map;

int var_count = 0;
int temp_count = 0;
int label_count = 0;

// 调试，打印所有子节点的名字
void print_children(Node *node) {
    cout << "current node: " << node->name << "\n";
    cout << "node->children: ";
    for (Node *child : node->children) {
        cout << child->name << " ";
    }
    cout << "\n";
}

// 调试，打印vars_map
void print_vars_map() {
    cout << "vars_map:\n";
    for (const pair<string, string> &p : vars_map) {
        cout << p.first << ": " << p.second << "\n";
    }
}

string new_var() { return "v" + to_string(var_count++); }

string new_temp() { return "t" + to_string(temp_count++); }

string new_label() { return "label" + to_string(label_count++); }

// 获取变量对应的v_name
string get_v_name(const string &var_name) {
    if (vars_map.find(var_name) == vars_map.end()) {
        vars_map[var_name] = new_var();
    }
    // cout << "get_v_name(): " << var_name << ": " << vars_map[var_name] << "\n";
    return vars_map[var_name];
}

// Program -> ExtDefList
string translate_Program(Node *node) { return translate_ExtDefList(node->children[0]); }

// ExtDefList -> ExtDef ExtDefList
// | $
string translate_ExtDefList(Node *node) {
    // node可能为NULL
    if (node->children.empty()) {
        return "";
    }
    string code1 = translate_ExtDef(node->children[0]);
    string code2 = translate_ExtDefList(node->children[1]);
    return code1 + code2;
}

// ExtDef -> Specifier ExtDecList SEMI
// | Specifier SEMI
// | Specifier FunDec CompSt
string translate_ExtDef(Node *node) {
    string name = node->children[1]->name;
    if (name == "ExtDecList") {
        return translate_ExtDecList(node->children[1]);
    } else if (name == "SEMI") {
        return translate_Specifier(node->children[0]);
    } else {
        string code1 = translate_FunDec(node->children[1]);
        string code2 = translate_CompSt(node->children[2]);
        return code1 + code2;
    }
}

// ExtDecList -> VarDec
// | VarDec COMMA ExtDecList
string translate_ExtDecList(Node *node) {
    if (node->children.size() == 1) {
        return translate_VarDec(node->children[0]);
    } else {
        string code1 = translate_VarDec(node->children[0]);
        string code2 = translate_ExtDecList(node->children[2]);
        return code1 + code2;
    }
}

// Specifier -> TYPE
// | StructSpecifier
string translate_Specifier(Node *node) {
    if (node->name.substr(0, 4) == "TYPE") {
        return "";
    } else {
        return translate_StructSpecifier(node);
    }
}

// StructSpecifier -> STRUCT ID LC DefList RC
// | STRUCT ID
// 结构体，不需要完成
string translate_StructSpecifier(Node *node) { return ""; }

// VarDec -> ID
// | VarDec LB INT RB
string translate_VarDec(Node *node) {
    // cout << "VarDec: " << node->children[0]->name << "\n";
    if (node->children.size() == 1) {
        string var_name = node->children[0]->name.substr(4);
        // 产生新的变量名
        get_v_name(var_name);
        return "";
    } else {
        // 数组，不需要完成
        return translate_VarDec(node->children[0]);
    }
}

// FunDec -> ID LP VarList RP
// | ID LP RP
string translate_FunDec(Node *node) {
    // ID: main
    string fun_name = node->children[0]->name.substr(4);
    string code = "FUNCTION " + fun_name + " :" + "\n";
    if (node->children.size() == 4) {
        code += translate_VarList(node->children[2]);
    }
    return code;
}

// VarList -> ParamDec COMMA VarList
// | ParamDec
string translate_VarList(Node *node) {
    // cout << "VarList: " << node->children[0]->children[1]->children[0]->name << "\n";
    // print_children(node);
    if (node->children.size() == 1) {
        return translate_ParamDec(node->children[0]);
    } else {
        // return translate_ParamDec(node->children[0]) + translate_VarList(node->children[2]);
        string code1 = translate_ParamDec(node->children[0]);
        string code2 = translate_VarList(node->children[2]);
        return code1 + code2;
    }
}

// ParamDec -> Specifier VarDec
string translate_ParamDec(Node *node) {
    // cout << "ParamDec: " << node->children[1]->children[0]->name << "\n";
    // string v_name = translate_VarDec(node->children[1]);
    string var_name = node->children[1]->children[0]->name.substr(4);
    string v_name = get_v_name(var_name);
    // print_vars_map();
    return "PARAM " + v_name + "\n";
}

// CompSt -> LC DefList StmtList RC
string translate_CompSt(Node *node) {
    string code1 = translate_DefList(node->children[1]);
    string code2 = translate_StmtList(node->children[2]);
    return code1 + code2;
}

// StmtList -> Stmt StmtList
// | $
string translate_StmtList(Node *node) {
    if (node->children.empty()) {
        return "";
    }
    string code1 = translate_Stmt(node->children[0]);
    string code2 = translate_StmtList(node->children[1]);
    return code1 + code2;
}

// Stmt -> Exp SEMI
// | CompSt
// | RETURN Exp SEMI
// | IF LP Exp RP Stmt
// | IF LP Exp RP Stmt ELSE Stmt
// | WHILE LP Exp RP Stmt
string translate_Stmt(Node *node) {
    // print_children(node);
    if (node->children.size() == 1) {
        // CompSt
        return translate_CompSt(node->children[0]);
    } else if (node->children.size() == 2) {
        // Exp SEMI
        return translate_Exp(node->children[0], "");
    } else if (node->children.size() == 3) {
        // RETURN Exp SEMI
        string tp;
        // 优化：如果Exp可以被重写为ID或INT
        Node *Exp = node->children[1];
        bool flag = false;
        if (Exp->children.size() == 1) {
            string name = Exp->children[0]->name;
            if (name.substr(0, 3) == "INT") {
                tp = "#" + name.substr(5);
            } else {
                tp = get_v_name(name.substr(4));
            }
            flag = true;
        }
        if (tp.empty()) {
            tp = new_temp();
        }
        string code = flag ? "" : translate_Exp(node->children[1], tp);
        return code + "RETURN " + tp + "\n";
    } else if (node->children.size() == 5) {
        if (node->children[0]->name == "IF") {
            // | IF LP Exp RP Stmt
            string lb1 = new_label();
            string lb2 = new_label();
            string code1 = translate_Cond_Exp(node->children[2], lb1, lb2) + "LABEL " + lb1 + " :\n";
            string code2 = translate_Stmt(node->children[4]) + "LABEL " + lb2 + " :\n";
            return code1 + code2;
        } else {
            // | WHILE LP Exp RP Stmt
            string lb1 = new_label();
            string lb2 = new_label();
            string lb3 = new_label();
            string code1 = "LABEL " + lb1 + " :\n" + translate_Cond_Exp(node->children[2], lb2, lb3);
            string code2 = "LABEL " + lb2 + " :\n" + translate_Stmt(node->children[4]) + "GOTO " + lb1 + "\n";
            return code1 + code2 + "LABEL " + lb3 + " :\n";
        }
    } else {
        // IF LP Exp RP Stmt ELSE Stmt
        string lb1 = new_label();
        string lb2 = new_label();
        string lb3 = new_label();
        string code1 = translate_Cond_Exp(node->children[2], lb1, lb2) + "LABEL " + lb1 + " :\n";
        string code2 = translate_Stmt(node->children[4]) + "GOTO " + lb3 + "\n" + "LABEL " + lb2 + " :\n";
        string code3 = translate_Stmt(node->children[6]) + "LABEL " + lb3 + " :\n";
        return code1 + code2 + code3;
    }
}

// DefList -> Def DefList
// | $
string translate_DefList(Node *node) {
    if (node->children.empty()) {
        return "";
    } else {
        string code1 = translate_Def(node->children[0]);
        string code2 = translate_DefList(node->children[1]);
        return code1 + code2;
    }
}

// Def -> Specifier DecList SEMI
string translate_Def(Node *node) { return translate_DecList(node->children[1]); }

// DecList -> Dec
// | Dec COMMA DecList
string translate_DecList(Node *node) {
    if (node->children.size() == 1) {
        return translate_Dec(node->children[0]);
    } else {
        string code1 = translate_Dec(node->children[0]);
        string code2 = translate_DecList(node->children[2]);
        return code1 + code2;
    }
}

// Dec -> VarDec
// | VarDec ASSIGN Exp
string translate_Dec(Node *node) {
    if (node->children.size() == 1) {
        return "";
    } else {
        string var_name = node->children[0]->children[0]->name.substr(4);
        string v_name = get_v_name(var_name);
        return translate_Exp(node->children[2], v_name);
    }
}

// Exp -> Exp ASSIGN Exp
// | Exp PLUS Exp
// | Exp MINUS Exp
// | Exp MUL Exp
// | Exp DIV Exp
// | LP Exp RP
// | MINUS Exp
// | ID LP Args RP
// | ID LP RP
// | Exp LB Exp RB (×)
// | Exp DOT ID (×)
// | ID
// | INT
// | FLOAT (×)
// | CHAR (×)
string translate_Exp(Node *node, const string &place) {
    // print_children(node);
    if (node->children.size() == 1) {
        if (node->children[0]->name.substr(0, 3) == "INT") {
            int val = stoi(node->children[0]->name.substr(5));
            return place + " := #" + to_string(val) + "\n";
        } else if (node->children[0]->name.substr(0, 2) == "ID") {
            string var_name = node->children[0]->name.substr(4);
            string v_name = get_v_name(var_name);
            return place + " := " + v_name + "\n";
        }
    } else if (node->children.size() == 2) {
        if (node->children[0]->name == "MINUS") {
            string tp;
            // 优化：如果Exp可以被重写为ID或INT
            Node *Exp = node->children[1];
            bool flag = false;
            if (Exp->children.size() == 1) {
                string name = Exp->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    tp = "#" + name.substr(5);
                } else {
                    tp = get_v_name(name.substr(4));
                }
                flag = true;
            }
            if (tp.empty()) {
                tp = new_temp();
            }
            string code1 = flag ? "" : translate_Exp(node->children[1], tp);
            string code2 = place + " := #0 - " + tp + "\n";
            return code1 + code2;
        }
    } else if (node->children.size() == 3) {
        if (node->children[1]->name == "ASSIGN") {
            // string tp;
            // 左边的Exp会被重写成ID
            // TODO: 一行中出现连续等式
            string var_name = node->children[0]->children[0]->name.substr(4);
            string v_name = get_v_name(var_name);
            Node *Exp2 = node->children[2];
            // 优化：如果Exp2是ID, INT, ID LP RP, ID LP Args RP中的任何一个
            bool flag = false;
            if (Exp2->children.size() == 1 || Exp2->children[0]->name.substr(0, 2) == "ID") {
                // tp = v_name;
                flag = true;
            }
            // if (tp.empty()) {
            //     tp = new_temp();
            // }
            // 不考虑连等的情况，只考虑Exp1为ID的情况，直接传v_name
            string code1 = translate_Exp(node->children[2], v_name);
            // string code2 = flag ? "" : v_name + " := " + tp + "\n";
            string code2 = "";
            string code3 = "";
            // 规约的时候如果到了最外层，place为空，不需要code3
            // 好像没有用？
            // if (!place.empty()) {
            //     code3 = place + " := " + v_name + "\n";
            // }
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "PLUS") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = place + " := " + t1 + " + " + t2 + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "MINUS") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = place + " := " + t1 + " - " + t2 + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "MUL") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = place + " := " + t1 + " * " + t2 + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "DIV") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = place + " := " + t1 + " / " + t2 + "\n";
            return code1 + code2 + code3;
        } else if (node->children[0]->name == "LP") {
            return translate_Exp(node->children[1], place);
        } else if (node->children[0]->name.substr(0, 2) == "ID") {
            // ID LP RP
            string fun_name = node->children[0]->name.substr(4);
            if (fun_name == "read") {
                return "READ " + place + "\n";
            } else {
                // 函数没有返回值接收，用新变量接收一下
                string tp = place.empty() ? new_temp() : place;
                return tp + " := CALL " + fun_name + "\n";
            }
        }
    } else {
        // ID LP Args RP
        // print_children(node);
        if (node->children[0]->name.substr(0, 2) == "ID") {
            if (node->children[0]->name.substr(4) == "write") {
                string tp;
                // 优化：如果Exp可以被重写为ID或INT
                Node *Exp = node->children[2]->children[0];
                bool flag = false;
                if (Exp->children.size() == 1) {
                    string name = Exp->children[0]->name;
                    if (name.substr(0, 3) == "INT") {
                        tp = "#" + name.substr(5);
                    } else {
                        tp = get_v_name(name.substr(4));
                    }
                    flag = true;
                }
                if (tp.empty()) {
                    tp = new_temp();
                }
                string code = flag ? "" : translate_Exp(node->children[2]->children[0], tp);
                code += "WRITE " + tp + "\n";
                return code;
            } else {
                string fun_name = node->children[0]->name.substr(4);
                vector<string> arg_list;
                string code1 = translate_Args(node->children[2], arg_list);
                string code2 = "";
                // 倒序输出ARG
                for (int i = arg_list.size() - 1; i >= 0; i--) {
                    code2 += "ARG " + arg_list[i] + "\n";
                }
                // 函数没有返回值接收，用新变量接收一下
                string tp = place.empty() ? new_temp() : place;
                return code1 + code2 + tp + " := CALL " + fun_name + "\n";
            }
        }
    }
    return "";
}

// Exp -> Exp AND Exp
// | Exp OR Exp
// | Exp LT Exp
// | Exp LE Exp
// | Exp GT Exp
// | Exp GE Exp
// | Exp NE Exp
// | Exp EQ Exp
// | NOT Exp
string translate_Cond_Exp(Node *node, const string &lb_t, const string &lb_f) {
    if (node->children.size() == 2) {
        // NOT Exp
        return translate_Cond_Exp(node->children[1], lb_f, lb_t);
    } else if (node->children.size() == 3) {
        if (node->children[1]->name == "AND") {
            string lb = new_label();
            string code1 = translate_Cond_Exp(node->children[0], lb, lb_f) + "LABEL " + lb + " :\n";
            string code2 = translate_Cond_Exp(node->children[2], lb_t, lb_f);
            return code1 + code2;
        } else if (node->children[1]->name == "OR") {
            string lb = new_label();
            string code1 = translate_Cond_Exp(node->children[0], lb_t, lb) + "LABEL " + lb + " :\n";
            string code2 = translate_Cond_Exp(node->children[2], lb_t, lb_f);
            return code1 + code2;
        } else if (node->children[1]->name == "LT") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = "IF " + t1 + " < " + t2 + " GOTO " + lb_t + "\n" + "GOTO " + lb_f + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "LE") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = "IF " + t1 + " <= " + t2 + " GOTO " + lb_t + "\n" + "GOTO " + lb_f + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "GT") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = "IF " + t1 + " > " + t2 + " GOTO " + lb_t + "\n" + "GOTO " + lb_f + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "GE") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = "IF " + t1 + " >= " + t2 + " GOTO " + lb_t + "\n" + "GOTO " + lb_f + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "NE") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = "IF " + t1 + " != " + t2 + " GOTO " + lb_t + "\n" + "GOTO " + lb_f + "\n";
            return code1 + code2 + code3;
        } else if (node->children[1]->name == "EQ") {
            string t1;
            string t2;
            // 优化：如果Exp1或Exp2可以被重写为ID或INT
            Node *Exp1 = node->children[0];
            bool flag1 = false;
            if (Exp1->children.size() == 1) {
                string name = Exp1->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t1 = "#" + name.substr(5);
                } else {
                    t1 = get_v_name(name.substr(4));
                }
                flag1 = true;
            }
            Node *Exp2 = node->children[2];
            bool flag2 = false;
            if (Exp2->children.size() == 1) {
                string name = Exp2->children[0]->name;
                if (name.substr(0, 3) == "INT") {
                    t2 = "#" + name.substr(5);
                } else {
                    t2 = get_v_name(name.substr(4));
                }
                flag2 = true;
            }
            if (t1.empty()) {
                t1 = new_temp();
            }
            if (t2.empty()) {
                t2 = new_temp();
            }
            string code1 = flag1 ? "" : translate_Exp(node->children[0], t1);
            string code2 = flag2 ? "" : translate_Exp(node->children[2], t2);
            string code3 = "IF " + t1 + " == " + t2 + " GOTO " + lb_t + "\n" + "GOTO " + lb_f + "\n";
            return code1 + code2 + code3;
        }
    }
    return "";
}

// Args -> Exp COMMA Args
// | Exp
string translate_Args(Node *node, vector<string> &arg_list) {
    // print_children(node);
    if (node->children.size() == 1) {
        string tp;
        // 优化：如果Exp可以被重写为ID或INT
        Node *Exp = node->children[0];
        bool flag = false;
        if (Exp->children.size() == 1) {
            string name = Exp->children[0]->name;
            if (name.substr(0, 3) == "INT") {
                tp = "#" + name.substr(5);
            } else {
                tp = get_v_name(name.substr(4));
            }
            flag = true;
        }
        if (tp.empty()) {
            tp = new_temp();
        }
        string code = flag ? "" : translate_Exp(node->children[0], tp);
        arg_list.push_back(tp);
        return code;
    } else {
        string tp;
        // 优化：如果Exp可以被重写为ID或INT
        Node *Exp = node->children[0];
        bool flag = false;
        if (Exp->children.size() == 1) {
            string name = Exp->children[0]->name;
            if (name.substr(0, 3) == "INT") {
                tp = "#" + name.substr(5);
            } else {
                tp = get_v_name(name.substr(4));
            }
            flag = true;
        }
        if (tp.empty()) {
            tp = new_temp();
        }
        string code1 = flag ? "" : translate_Exp(node->children[0], tp);
        arg_list.push_back(tp);
        string code2 = translate_Args(node->children[2], arg_list);
        return code1 + code2;
    }
}

unordered_map<string, string> labels_map;

string translate(Node *root) {
    string ir_code = translate_Program(root);
    stringstream ss;
    ss << ir_code;
    string line;
    vector<string> lines;
    while (getline(ss, line, '\n')) {
        lines.push_back(line);
    }
    string target_label;
    unordered_set<int> idxs;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i].length() >= 5 && lines[i].substr(0, 5) == "LABEL") {
            string cur_label = lines[i].substr(6);
            cur_label.pop_back();
            cur_label.pop_back();
            if (i > 0 && lines[i - 1].length() >= 5 && lines[i - 1].substr(0, 5) == "LABEL") {
                idxs.insert(i);
            } else {
                target_label = cur_label;
            }
            labels_map[cur_label] = target_label;
        } else {
            target_label = "";
        }
    }
    ir_code = "";
    for (int i = 0; i < lines.size(); i++) {
        if (idxs.find(i) == idxs.end()) {
            line = lines[i];
            if (line.find("GOTO") != string::npos) {
                string cur_label = line.substr(line.find("GOTO") + 5);
                if (labels_map.find(cur_label) != labels_map.end()) {
                    string target_label = labels_map[cur_label];
                    line = line.substr(0, line.find("GOTO") + 5) + target_label;
                }
            }
            if (line.find("LABEL") != string::npos) {
                string cur_label = line.substr(line.find("LABEL") + 6);
                if (labels_map.find(cur_label) != labels_map.end()) {
                    string target_label = labels_map[cur_label];
                    line = line.substr(0, line.find("LABEL") + 6) + target_label;
                }
            }
            ir_code += line + "\n";
        }
    }
    return ir_code;
}