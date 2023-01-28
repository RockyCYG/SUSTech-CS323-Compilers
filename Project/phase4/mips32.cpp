#include "mips32.hpp"
#include<bits/stdc++.h>

/* the output file descriptor, may not be explicitly used */
FILE *fd;

#define tac_kind(tac) (((tac)->code).kind)
#define tac_quadruple(tac) (((tac)->code).tac)
#define reg_name(reg) regs[reg].name

RegDesc regs[Register::NUM_REGS];
VarDesc *vars;
int tot_var;
std::map<std::string,int> var_id;
Register register_map[100005];
int address_map[100005];
std::string cur_func;
Register name2Register(const char *name){
    if(name == "$zero") return zero;
    if(name == "$at") return at;
    if(name == "$v0") return v0;
    if(name == "$v1") return v1;
    if(name == "$a0") return a0;
    if(name == "$a1") return a1;
    if(name == "$a2") return a2;
    if(name == "$a3") return a3;
    if(name == "$t0") return t0;
    if(name == "$t1") return t1;
    if(name == "$t2") return t2;
    if(name == "$t3") return t3;
    if(name == "$t4") return t4;
    if(name == "$t5") return t5;
    if(name == "$t6") return t6;
    if(name == "$t7") return t7;
    if(name == "$s0") return s0;
    if(name == "$s1") return s1;
    if(name == "$s2") return s2;
    if(name == "$s3") return s3;
    if(name == "$s4") return s4;
    if(name == "$s5") return s5;
    if(name == "$s6") return s6;
    if(name == "$s7") return s7;
    if(name == "$t8") return t8;
    if(name == "$t9") return t9;
    if(name == "$k0") return k0;
    if(name == "$k1") return k1;
}
void mips_iprintf(const char *fmt, ...);
Register get_empty_register(){
    int id=Register::s0;
    for(int i=Register::s0;i<=Register::s7;i++){
        if(regs[i].dirty == false) return name2Register(regs[i].name);
        if(regs[i].cnt<regs[id].cnt) id=i;
    }
    return name2Register(regs[id].name);
}
int store_top = 0;
void store_var_in_register(char *var,Register x,int addr){
    //char old_var[8]={};
    //memcpy(old_var,regs[x].var,strlen(regs[x].var)+1);
    //std::cout<<old_var<<std::endl;
    if(strlen(regs[x].var)>0){
        //mips_iprintf("la $t0,a");
        //mips_iprintf("sw %s,%d($t0)",reg_name(x),store_top);
        //int old_id = var_id[regs[x].var];
        //address_map[old_id]=store_top;
        //store_top += 4;
        //register_map[old_id]=zero;
    }
    int new_id = var_id[var];
    memcpy(regs[x].var,var,sizeof(var));
    //address_map[new_id] = 0;
    register_map[new_id] = x;
    //std::cout<<"var = "<<var<<"      new_var = "<<new_var<<std::endl;
    //std::cout<<" !!! var = "<<var<<"     "<<register_map[var]<<regs[x].var<<std::endl;
    //mips_iprintf("=====================register_map(%s)=%s",var,reg_name(x));
    if(regs[x].dirty == false)
    {
        regs[x].dirty = true;
    }
    regs[x].cnt++;
    mips_iprintf("la $t0,a");
    mips_iprintf("lw %s,%d($t0)",reg_name(x),addr);
}
Register get_register_by_var(char *var){
    char new_var[8]={};
    memcpy(new_var,var,strlen(var));
    int id = var_id[new_var];
    std::cout<<"id "<<new_var<<"="<<id<<" "<<tot_var<<std::endl;
    if(!id) id = var_id[new_var]=++tot_var;
    /*if(register_map[id]) 
    {
        //mips_iprintf("+++++++++++++++++++++++++%s: %s",var,reg_name(register_it->second));
        return register_map[id];
    }*/
    //address_it = address_map.find(var);
    if(address_map[id] ){
        //Register temp_reg = get_empty_register();
        //store_var_in_register(var,temp_reg,address_map[id]);
        //return temp_reg;
    }
    else 
    {
        store_top+=4;
        address_map[id]=store_top;
        std::cout<<"addr("<<id<<")="<<address_map[id]<<std::endl;
    }
    Register temp_reg = get_empty_register();
    store_var_in_register(var,temp_reg,address_map[id]);
    std::cout<<"get_register()"<<var<<"   "<<reg_name(temp_reg)<<std::endl;
    return temp_reg;
}
Register get_register(tac_opd *opd) {
    assert(opd->kind == tac_opd::OP_VARIABLE);
    char *var = opd->char_val;
    //register_it = register_map.find(var);
    //std::cout<<" var = "<<var<<"     "<<register_map[var]<<std::endl;
    return get_register_by_var(var);
    /* COMPLETE the register allocation */
    return t0;
}
void write_back(char *var,Register write_reg){
    int id = var_id[var];
    
    if(!id) id = var_id[var]=++tot_var;
    std::cout<<"id "<<var<<"="<<id<<" "<<tot_var<<"    "<<address_map[id]<<std::endl;
    int addr = address_map[id];
    if(!addr) {
        store_top+=4,addr = address_map[id]=store_top;
        std::cout<<"addr = "<<addr<<std::endl;
    }
    mips_iprintf("la $t0,a");
    mips_iprintf("sw %s,%d($t0)",reg_name(write_reg),addr);
}
void reg_to_memory(Register x){
    char *var = regs[x].var;
    int id = var_id[var];
    write_back(var,x);
}
Register get_register_w(tac_opd *opd) {
    assert(opd->kind == tac_opd::OP_VARIABLE);
    char *var = opd->char_val;
    Register reg_ret = get_register(opd);
    //write_back(var,reg_ret);
    return reg_ret;
    /* COMPLETE the register allocation (for write) */
    return s0;
}

void spill_register(Register reg) {
    /* COMPLETE the register spilling */
}


void mips_printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(fd, fmt, args);
    va_end(args);
    fputs("\n", fd);
}

void mips_iprintf(const char *fmt, ...) {
    va_list args;
    fputs("  ", fd); // `iprintf` stands for indented printf
    va_start(args, fmt);
    vfprintf(fd, fmt, args);
    va_end(args);
    fputs("\n", fd);
}


/* PARAM: a pointer to `struct tac_node` instance
   RETURN: the next instruction to be translated */
tac *emit_label(tac *label) {
    assert(tac_kind(label) == tac_inst::LABEL);
    mips_printf("label%d:", tac_quadruple(label).labelno->int_val);
    return label->next;
}

tac *emit_function(tac *function) {
    cur_func = tac_quadruple(function).funcname;
    mips_printf("%s:", tac_quadruple(function).funcname);
    return function->next;
}

tac *emit_assign(tac *assign) {
    Register x, y;

    x = get_register_w(tac_quadruple(assign).left);
    if (tac_quadruple(assign).right->kind == tac_opd::OP_CONSTANT) {
        mips_iprintf("li %s, %d", reg_name(x),
                     tac_quadruple(assign).right->int_val);
    } else {
        y = get_register(tac_quadruple(assign).right);
        mips_iprintf("move %s, %s", reg_name(x), reg_name(y));
    }
    reg_to_memory(x);
    return assign->next;
}

tac *emit_add(tac *add) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(add).left);
    if (tac_quadruple(add).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(add).r2);
        mips_iprintf("addi %s, %s, %d", reg_name(x),
                     reg_name(y),
                     tac_quadruple(add).r1->int_val);
    } else if (tac_quadruple(add).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(add).r1);
        mips_iprintf("addi %s, %s, %d", reg_name(x),
                     reg_name(y),
                     tac_quadruple(add).r2->int_val);
    } else {
        y = get_register(tac_quadruple(add).r1);
        z = get_register(tac_quadruple(add).r2);
        mips_iprintf("add %s, %s, %s", reg_name(x),
                     reg_name(y),
                     reg_name(z));
    }
    reg_to_memory(x);
    return add->next;
}

tac *emit_sub(tac *sub) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(sub).left);
    if (tac_quadruple(sub).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(sub).r2);
        mips_iprintf("neg %s, %s", reg_name(y), reg_name(y));
        mips_iprintf("addi %s, %s, %d", reg_name(x),
                     reg_name(y),
                     tac_quadruple(sub).r1->int_val);
    } else if (tac_quadruple(sub).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(sub).r1);
        mips_iprintf("addi %s, %s, -%d", reg_name(x),
                     reg_name(y),
                     tac_quadruple(sub).r2->int_val);
    } else {
        y = get_register(tac_quadruple(sub).r1);
        z = get_register(tac_quadruple(sub).r2);
        mips_iprintf("sub %s, %s, %s", reg_name(x),
                     reg_name(y),
                     reg_name(z));
    }
    reg_to_memory(x);
    return sub->next;
}

tac *emit_mul(tac *mul) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(mul).left);
    if (tac_quadruple(mul).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register_w(tac_quadruple(mul).r1);
        z = get_register(tac_quadruple(mul).r2);
        mips_iprintf("lw %s, %d", reg_name(y),
                     tac_quadruple(mul).r1->int_val);
    } else if (tac_quadruple(mul).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(mul).r1);
        z = get_register_w(tac_quadruple(mul).r2);
        mips_iprintf("lw %s, %d", reg_name(z),
                     tac_quadruple(mul).r2->int_val);
    } else {
        y = get_register(tac_quadruple(mul).r1);
        z = get_register(tac_quadruple(mul).r2);
    }
    mips_iprintf("mul %s, %s, %s", reg_name(x),
                 reg_name(y),
                 reg_name(z));
    reg_to_memory(x);
    return mul->next;
}

tac *emit_div(tac *div) {
    Register x, y, z;

    x = get_register_w(tac_quadruple(div).left);
    if (tac_quadruple(div).r1->kind == tac_opd::OP_CONSTANT) {
        y = get_register_w(tac_quadruple(div).r1);
        z = get_register(tac_quadruple(div).r2);
        mips_iprintf("lw %s, %d", reg_name(y),
                     tac_quadruple(div).r1->int_val);
    } else if (tac_quadruple(div).r2->kind == tac_opd::OP_CONSTANT) {
        y = get_register(tac_quadruple(div).r1);
        z = get_register_w(tac_quadruple(div).r2);
        mips_iprintf("lw %s, %d", reg_name(z),
                     tac_quadruple(div).r2->int_val);
    } else {
        y = get_register(tac_quadruple(div).r1);
        z = get_register(tac_quadruple(div).r2);
    }
    mips_iprintf("div %s, %s", reg_name(y), reg_name(z));
    mips_iprintf("mflo %s", reg_name(x));
    reg_to_memory(x);
    return div->next;
}

tac *emit_addr(tac *addr) {
    Register x, y;

    x = get_register_w(tac_quadruple(addr).left);
    y = get_register(tac_quadruple(addr).right);
    mips_iprintf("move %s, %s", reg_name(x), reg_name(y));
    reg_to_memory(x);
    return addr->next;
}

tac *emit_fetch(tac *fetch) {
    Register x, y;

    x = get_register_w(tac_quadruple(fetch).left);
    y = get_register(tac_quadruple(fetch).raddr);
    mips_iprintf("lw %s, 0(%s)", reg_name(x), reg_name(y));
    reg_to_memory(x);
    return fetch->next;
}

tac *emit_deref(tac *deref) {
    Register x, y;

    x = get_register(tac_quadruple(deref).laddr);
    y = get_register(tac_quadruple(deref).right);
    mips_iprintf("sw %s, 0(%s)", reg_name(y), reg_name(x));
    return deref->next;
}

tac *emit_goto(tac *goto_) {
    mips_iprintf("j label%d", tac_quadruple(goto_).labelno->int_val);
    return goto_->next;
}
tac *emit_iflt(tac *iflt) {
    Register x,y,t1,t2;
    x = get_register(tac_quadruple(iflt).c1);
    y = get_register(tac_quadruple(iflt).c2);
    mips_iprintf("add $t1,$zero,%s",reg_name(x));
    mips_iprintf("add $t2,$zero,%s",reg_name(y));
    mips_iprintf("slt $t0,$t1,$t2");
    mips_iprintf("bne $t0,$0, label%d",tac_quadruple(iflt).labelno->int_val);
    /* COMPLETE emit function */
    return iflt->next;
}

tac *emit_ifle(tac *ifle) {
    Register x,y;
    x = get_register(tac_quadruple(ifle).c1);
    y = get_register(tac_quadruple(ifle).c2);
    mips_iprintf("add $t1,$zero,%s",reg_name(x));
    mips_iprintf("add $t2,$zero,%s",reg_name(y));
    mips_iprintf("slt $t0,$t2,$t1");
    mips_iprintf("ori $1,$0,0x00000001");
    mips_iprintf("subu $8,$1,$8");//sle $t0,$t1,$t2
    mips_iprintf("bne $t0,$0, label%d",tac_quadruple(ifle).labelno->int_val);
    /* COMPLETE emit function */
    return ifle->next;
}

tac *emit_ifgt(tac *ifgt) {
    Register x,y;
    x = get_register(tac_quadruple(ifgt).c1);
    y = get_register(tac_quadruple(ifgt).c2);
    mips_iprintf("add $t1,$zero,%s",reg_name(x));
    mips_iprintf("add $t2,$zero,%s",reg_name(y));
    mips_iprintf("slt $8,$10,$9");//sgt $t0,$t1,$t2
    mips_iprintf("bne $t0,$0, label%d",tac_quadruple(ifgt).labelno->int_val);
    /* COMPLETE emit function */
    return ifgt->next;
}

tac *emit_ifge(tac *ifge) {
    Register x,y;
    x = get_register(tac_quadruple(ifge).c1);
    y = get_register(tac_quadruple(ifge).c2);
    mips_iprintf("add $t1,$zero,%s",reg_name(x));
    mips_iprintf("add $t2,$zero,%s",reg_name(y));
    mips_iprintf("slt $8,$9,$10");
    mips_iprintf("ori $t1,$0,0x00000001");
    mips_iprintf("subu $8,$t1,$8");
    mips_iprintf("bne $t0,$0, label%d",tac_quadruple(ifge).labelno->int_val);//sge $t0,$t1,$t2
    /* COMPLETE emit function */
    return ifge->next;
}

tac *emit_ifne(tac *ifne) {
    Register x,y;
    x = get_register(tac_quadruple(ifne).c1);
    y = get_register(tac_quadruple(ifne).c2);
    mips_iprintf("add $t1,$zero,%s",reg_name(x));
    mips_iprintf("add $t2,$zero,%s",reg_name(y));
    mips_iprintf("bne $t1,$t2, label%d",tac_quadruple(ifne).labelno->int_val);
    /* COMPLETE emit function */
    return ifne->next;
}

tac *emit_ifeq(tac *ifeq) {
    Register x,y;
    x = get_register(tac_quadruple(ifeq).c1);
    y = get_register(tac_quadruple(ifeq).c2);
    mips_iprintf("add $t1,$zero,%s",reg_name(x));
    mips_iprintf("add $t2,$zero,%s",reg_name(y));
    mips_iprintf("beq $t1,$t2, label%d",tac_quadruple(ifeq).labelno->int_val);
    /* COMPLETE emit function */
    return ifeq->next;
}
int cnt_para,cur_para;
Register para_register[11];
tac *emit_return(tac *return_) {
    Register x = get_register(tac_quadruple(return_).var);
    std::cout<<"return:"<<reg_name(x)<<std::endl;
    mips_iprintf("move $v0,%s",reg_name(x));
    if(cur_func!="main"&&cur_func!="MAIN"){
        //mips_iprintf("lw $ra,0($sp)");
        //mips_iprintf("addi $sp,$sp,%d",4*(cnt_para+1));
        mips_iprintf("jr $ra");
    }
    else{
        mips_iprintf("move $a0,$v0");
        mips_iprintf("li $v0, 17");
        mips_iprintf("syscall");
    }
    cnt_para = 0;
    /* COMPLETE emit function */
    return return_->next;
}

tac *emit_dec(tac *dec) {
    /* NO NEED TO IMPLEMENT */
    return dec->next;
}
int cnt_arg;
Register cur_arg[1000005];
char *param_var[100005];
tac *emit_arg(tac *arg) {
    
    Register x = get_register(tac_quadruple(arg).var);
    std::cout<<"arg:"<<reg_name(x)<<std::endl;
    //mips_iprintf("move $a%d,%s",cnt_arg,reg_name(x));
    cur_arg[cnt_arg++]=x;

    /* COMPLETE emit function */
    //if((arg->next)->code.kind!=tac_inst::ARG) cnt_arg=0;
    return arg->next;
}

tac *emit_call(tac *call) {
    Register x = get_register(tac_quadruple(call).ret);
    std::cout<<"return:"<<reg_name(x)<<std::endl;
    mips_iprintf("addi $sp,$sp,%d",-4*(cnt_arg+1));
    for(int i=0;i<cnt_arg;i++)
    {
        Register y =get_register_by_var(param_var[i]);
        mips_iprintf("sw %s,%d($sp)",reg_name(y),4*i);
    }
    mips_iprintf("sw $ra, %d($sp)",4*cnt_arg);
    for(int i=0;i<cnt_arg;i++) mips_iprintf("move $a%d,%s",i,reg_name(cur_arg[cnt_arg-i-1]));
    mips_iprintf("jal %s",tac_quadruple(call).funcname);
    for(int i=0;i<cnt_arg;i++) 
    {
        Register y =get_register_by_var(param_var[i]);
        mips_iprintf("lw %s,%d($sp)",reg_name(y),4*i);
        reg_to_memory(y);
        //mips_iprintf("lw $a%d,%d($sp)",i,4*i);
    }
    mips_iprintf("lw $ra, %d($sp)",4*cnt_arg);
    mips_iprintf("addi $sp, $sp, %d",4*(cnt_arg+1));
    mips_iprintf("move %s,$v0",reg_name(x));
    reg_to_memory(x);
    cnt_arg=0;
    /* COMPLETE emit function */
    return call->next;
}

tac *emit_param(tac *param) {
    char *var = tac_quadruple(param).p->char_val;
    int id = var_id[var];
    if(!id) id = var_id[var]=++tot_var;
    Register x = get_register(tac_quadruple(param).p);
    mips_iprintf("move %s,$a%d",reg_name(x),cnt_para);
    param_var[cnt_para]=var;
    cnt_para++;
    reg_to_memory(x);
    /* COMPLETE emit function */
    return param->next;
}

tac *emit_read(tac *read) {
    Register x = get_register(tac_quadruple(read).p);

    mips_iprintf("addi $sp, $sp, -4");
    mips_iprintf("sw $ra, 0($sp)");
    mips_iprintf("jal read");
    mips_iprintf("lw $ra, 0($sp)");
    mips_iprintf("addi $sp, $sp, 4");
    mips_iprintf("move %s, $v0", reg_name(x));
    reg_to_memory(x);
    return read->next;
}

tac *emit_write(tac *write) {
    Register x = get_register_w(tac_quadruple(write).p);

    mips_iprintf("move $a0, %s", reg_name(x));
    mips_iprintf("addi $sp, $sp, -4");
    mips_iprintf("sw $ra, 0($sp)");
    mips_iprintf("jal write");
    mips_iprintf("lw $ra, 0($sp)");
    mips_iprintf("addi $sp, $sp, 4");
    return write->next;
}

void emit_preamble() {
    mips_printf("# SPL compiler generated assembly");
    mips_printf(".data");
    mips_printf("a: .space 20000");
    mips_printf("_prmpt: .asciiz \"Enter an integer: \"");
    mips_printf("_eol: .asciiz \"\\n\"");
    mips_printf(".globl main");
    mips_printf(".text");
}

void emit_read_function() {
    mips_printf("read:");
    mips_iprintf("li $v0, 4");
    mips_iprintf("la $a0, _prmpt");
    mips_iprintf("syscall");
    mips_iprintf("li $v0, 5");
    mips_iprintf("syscall");
    mips_iprintf("jr $ra");
}

void emit_write_function() {
    mips_printf("write:");
    mips_iprintf("li $v0, 1");
    mips_iprintf("syscall");
    mips_iprintf("li $v0, 4");
    mips_iprintf("la $a0, _eol");
    mips_iprintf("syscall");
    mips_iprintf("move $v0, $0");
    mips_iprintf("jr $ra");
}

static tac *(*emitter[])(tac *) = {
        emit_label, emit_function, emit_assign,
        emit_add, emit_sub, emit_mul, emit_div,
        emit_addr, emit_fetch, emit_deref, emit_goto,
        emit_iflt, emit_ifle, emit_ifgt, emit_ifge, emit_ifne, emit_ifeq,
        emit_return, emit_dec, emit_arg, emit_call, emit_param,
        emit_read, emit_write
};

tac *emit_code(tac *head) {
    tac *(*tac_emitter)(tac *);
    tac *tac_code = head;
    emit_preamble();
    emit_read_function();
    emit_write_function();
    while (tac_code != nullptr) {
        if (tac_kind(tac_code) != tac_inst::NONE) {
            tac_emitter = emitter[tac_kind(tac_code)];
            tac_code = tac_emitter(tac_code);
        } else {
            tac_code = tac_code->next;
        }
    }
}

/* translate a TAC list into mips32 assembly
   output the textual assembly code to _fd */
void mips32_gen(tac *head, FILE *_fd) {
    regs[zero].name = "$zero";
    regs[at].name = "$at";
    regs[v0].name = "$v0";
    regs[v1].name = "$v1";
    regs[a0].name = "$a0";
    regs[a1].name = "$a1";
    regs[a2].name = "$a2";
    regs[a3].name = "$a3";
    regs[t0].name = "$t0";
    regs[t1].name = "$t1";
    regs[t2].name = "$t2";
    regs[t3].name = "$t3";
    regs[t4].name = "$t4";
    regs[t5].name = "$t5";
    regs[t6].name = "$t6";
    regs[t7].name = "$t7";
    regs[s0].name = "$s0";
    regs[s1].name = "$s1";
    regs[s2].name = "$s2";
    regs[s3].name = "$s3";
    regs[s4].name = "$s4";
    regs[s5].name = "$s5";
    regs[s6].name = "$s6";
    regs[s7].name = "$s7";
    regs[t8].name = "$t8";
    regs[t9].name = "$t9";
    regs[k0].name = "$k0";
    regs[k1].name = "$k1";
    regs[gp].name = "$gp";
    regs[sp].name = "$sp";
    regs[fp].name = "$fp";
    regs[ra].name = "$ra";
    vars = (VarDesc *) malloc(sizeof(struct VarDesc));
    vars->next = nullptr;
    fd = _fd;
    emit_code(head);
}
