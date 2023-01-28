#include "semantic.hpp"
#include "type.hpp"

using namespace std;

template<typename T>
inline void hash_combine(std::size_t &seed, const T &val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(std::size_t &seed, const T &val) {
    hash_combine(seed, val);
}

template<typename T, typename... Types>
inline void hash_val(std::size_t &seed, const T &val, const Types &... args) {
    hash_combine(seed, val);
    hash_val(seed, args...);
}

template<typename... Types>
inline std::size_t hash_val(const Types &... args) {
    std::size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}

struct pair_hash {
    template<class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &p) const {
        return hash_val(p.first, p.second);
    }
};

unordered_map<pair<string, int>, Type *, pair_hash> vars;
// value: 函数返回值
unordered_map<string, Type *> fun_return_types;
unordered_map<string, int> fun_param_counts;
// 函数参数
unordered_map<pair<string, int>, Type *, pair_hash> fun_params;
unordered_map<string, Type *> struct_types;

void print_error(int type, int line, const string &message) {
    printf("Error type %d at Line %d: %s", type, line, message.c_str());
}

auto TYPE_INT = new Type("", Category::PRIMITIVE, {Primitive::INT});
auto TYPE_FLOAT = new Type("", Category::PRIMITIVE, {Primitive::FLOAT});
auto TYPE_CHAR = new Type("", Category::PRIMITIVE, {Primitive::CHAR});

Type *get_type_int() {
    return TYPE_INT;
}

Type *get_type_float() {
    return TYPE_FLOAT;
}

Type *get_type_char() {
    return TYPE_CHAR;
}

Type *get_type_struct(const string &struct_name) {
    return struct_types[struct_name];
}

Type *get_type_array(Type *base, int len) {
    return new Type("", Category::ARRAY, {.array=new Array(base, len)});
}

bool is_exist_var(const string &var_name, int scope) {
    // cout << "is_exist_var(): " << var_name << " " << to_string(scope) << "\n";
    // cout << vars.count({var_name, scope}) << "\n";
    return vars.count({var_name, scope});
}

bool is_exist_fun(const string &fun_name) {
    return fun_return_types.count(fun_name);
}

bool is_type_array(Type *type) {
    return type && type->category == Category::ARRAY;
}

bool is_int(Type *type) {
    return type && type->category == Category::PRIMITIVE && type->innerType.primitive == Primitive::INT;
}

bool is_float(Type *type) {
    return type && type->category == Category::PRIMITIVE && type->innerType.primitive == Primitive::FLOAT;
}

bool is_struct(Type *type) {
    return type && type->category == Category::STRUCTURE;
}

Type *get_array_base(Type *type) {
	if (type == nullptr) {
		return nullptr;
	}
    if (type->category == Category::PRIMITIVE) {
        switch (type->innerType.primitive) {
            case Primitive::INT:
                return get_type_int();
            case Primitive::FLOAT:
                return get_type_float();
            case Primitive::CHAR:
                return get_type_char();
        }
    }
    if (type->category == Category::STRUCTURE) {
        return struct_types[type->name];
    }
    type->category = Category::ARRAY;
    return type->innerType.array->base;
}

Type *get_var_type(const string &var_name, int scope) {
    return vars[{var_name, scope}];
}

Type *get_fun_return(const string &fun_name) {
    return fun_return_types[fun_name];
}

int get_fun_count(const string &fun_name) {
    return fun_param_counts[fun_name];
}

Type *get_fun_param_type(const string &fun_name, int id) {
    return fun_params[{fun_name, id}];
}

void generate_fun(Type *type, const string &fun_name) {
    fun_return_types[fun_name] = type;
}

void fun_add_var(Type *type, const string &fun_name, int id) {
    fun_params[{fun_name, id}] = type;
    fun_param_counts[fun_name]++;
}

void generate_struct(const string &struct_name, int line) {
    // cout << struct_name << endl;
    if (struct_types.count(struct_name)) {
        // Error type 15 at Line 6: redefine struct: Child
        print_error(15, line, "redefine struct: " + struct_name + "\n");
        return;
    }
    struct_types[struct_name] = new Type(struct_name, Category::STRUCTURE, {.structure=nullptr});
}

void print_all_member(const string &struct_name) {
    InnerType &inner_type = struct_types[struct_name]->innerType;
    FieldList *cur = inner_type.structure;
    if (cur) {
        // cout << struct_name << "'s members:\n";
        while (cur->next) {
            // cout << cur->name << " ";
            cur = cur->next;
        }
        // cout << endl;
    } else {
        // cout << struct_name << " has no members!\n";
    }
}

void struct_add_member(const string &struct_name, const string &member_name, Type *type) {
    // printf("%s add the attribute: %s\n", struct_name.c_str(), member_name.c_str());
    InnerType &inner_type = struct_types[struct_name]->innerType;
    FieldList *cur = inner_type.structure;
    auto res = new FieldList(member_name, type, nullptr);
    // cout << "The first attribute " << cur << endl;
    if (cur) {
        // cout << "have" << endl;
        while (cur->next) {
            cur = cur->next;
        }
        cur->next = res;
    } else {
        inner_type.structure = res;
    }
}

void generate_var(const string &var_name, int scope, Type *type, int line) {
    if (vars.count({var_name, scope})) {
        // Error type 3 at Line 6: redefine variable: ttt
        print_error(3, line, "redefine variable: " + var_name + "\n");
        return;
    }
    if (type == nullptr) {
        print_error(1, line, "undefined variable: " + var_name + "\n");
        return;
    }
    vars[{var_name, scope}] = type;
    // printf("%s, %d, %s\n", var_name.c_str(), scope, type->info().c_str());
}

Type *get_struct_member(const string &struct_name, const string &member_name) {
    // cout << struct_name << ": " << member_name << endl;
    InnerType &inner_type = struct_types[struct_name]->innerType;
    FieldList *cur = inner_type.structure;
    while (cur) {
        if (cur->name == member_name) {
            // cout << "success find!\n";
            return cur->type;
        }
        cur = cur->next;
    }
    // cout << "fail to find!\n";
    return nullptr;
}

string get_struct_name(Type *type) {
	if (type == nullptr) {
		return "";
	}
    return type->name;
}

bool is_same_type(Type *a, Type *b) {
    // cout << a->info() << endl;
    // cout << b->info() << endl;
    if (a == nullptr || b == nullptr) {
        return false;
    }
    if (a == b) {
        return true;
    }
    if (a->category != b->category) {
        return false;
    }
    if (a->category == Category::PRIMITIVE) {
        return a->innerType.primitive == b->innerType.primitive;
    }
    if (a->category == Category::ARRAY) {
        return is_same_type(a->innerType.array->base, b->innerType.array->base);
    }
    if (a->category == Category::STRUCTURE) {
        return a->name == b->name;
    }
    return false;
}

// void print_all_variables() {
//     for (auto  : vars) {

//     }
// }
