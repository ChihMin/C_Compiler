#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "literal.h"


extern int cur_id;
extern int ir_num;
extern int cur_offset;
extern int symbol_num;
extern Instruction IR[];
extern int yyerror(char *);
extern FILE *f_asm;
extern int mc_num;
extern char **code_ptr;
extern char **code_base;

Register reg[REG_MAX];
int cur_time;

Symbol* alloc_symbol() {
    Symbol *symbol = (Symbol*)malloc(sizeof(Symbol));
    memset(symbol, 0, sizeof(Symbol));
    symbol->id = cur_id++;
    return symbol; 
}

void push_symbol(char *name, int scope, int type) {
    int i;
    for (i = 0; i < symbol_num; ++i) {
        if (!strcmp(name, table[i].name) && scope == table[i].scope) {
            yyerror(NULL);
        }
    }
    
    table[symbol_num].id = symbol_num; 
    table[symbol_num].name = name;
    table[symbol_num].offset = cur_offset;
    table[symbol_num].type = type;

    cur_offset += 4;
    symbol_num += 1;
}

int lookup_symbol(char *name, int scope) {
    int i, isfind = 0;
    for (i = symbol_num - 1; i >= 0; i--) {
        if (!strcmp(name, table[i].name)) {
            return table[i].offset;
        }
    }
    return -1;
}


void gen_ir_mov(Symbol *op1, Symbol *op2) {
    IR[ir_num].opc = OP_MOV;
    IR[ir_num].operands[0] = op1;
    IR[ir_num].operands[1] = op2;
    IR[ir_num].operand_num = 2;
    ir_num++;
}

void gen_ir_movi(Symbol* operand, int immediate) {
    IR[ir_num].opc = OP_MOVI;
    IR[ir_num].operands[0] = operand;
    IR[ir_num].operand_num = 1;
    ir_num++;
}

// r1 = r2 + r3
void gen_ir_add(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_ADD;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
    ir_num++;
}

// r1 = r2 - r3
void gen_ir_sub(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_SUB;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
    ir_num++;
}

// r1 = r2 * r3
void gen_ir_mul(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_MUL;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
    ir_num++;
}

// r1 = r2 / r3
void gen_ir_div(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_DIV;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
    ir_num++;
}

// r1 = r2 % r3
void gen_ir_mod(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_MOD;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
    ir_num++;
}

// ID(memory) = reg
void gen_ir_str(Symbol *op, int offset) {
    op->offset = offset;
    IR[ir_num].opc = OP_STR;
    IR[ir_num].operands[0] = op;
    IR[ir_num].operand_num = 1;
    ir_num++;
}

void gen_ir_ldr(Symbol *op, int offset) {
    op->offset = offset;
    IR[ir_num].opc = OP_LDR;
    IR[ir_num].operands[0] = op;
    IR[ir_num].operand_num = 1;
    ir_num++;
}

/*********** BACKEND ************/

void free_reg(int idx) {
    Symbol *symbol = reg[idx].target;
    if (symbol) {
        symbol->in_reg = 0;
        symbol->reg = -1;
    }
    memset(&reg[idx], 0, sizeof(Register));
}

void push_reg_to_stack(int idx) {
    Symbol *symbol = reg[idx].target;
    if (symbol) {
        symbol->in_reg = 0;
        symbol->sp_offset = cur_offset;
        symbol->in_sp = 1;
    } else {
        printf("Warning, push temporary register to stack ...\n");
        exit(-1);
    }
    sprintf(*(code_ptr++), "swi $r%d, [$sp + %d]", idx, cur_offset);
    free_reg(idx);
    cur_offset += 4; 
}

int get_reg(Symbol *symbol) {
    int i;
    int tar_reg = -1;
    int lu_reg = -1;
    int time = 0x7FFFFFFF;
    for (i = 0; i < REG_MAX; ++i) {
        if (!reg[i].in_use) {
            tar_reg = i;
            break;
        } else if (!reg[i].is_temp && reg[i].time < time) {
            // avoid get temporary register
            // and select least use of register 
            time = reg[i].time;
            lu_reg = i;
        }
    }
    
    if (tar_reg < 0) {
        push_reg_to_stack(lu_reg);
        tar_reg = lu_reg;
    }
    
    reg[tar_reg].in_use = 1;
    reg[tar_reg].target = symbol;
    reg[tar_reg].time = cur_time++;
    
    // void allocate temporary register
    if (symbol) {
        symbol->reg = tar_reg;
        symbol->in_reg = 1;
    } else {
        reg[tar_reg].is_temp = 1;
    }
    
    return tar_reg;
}

int load_back_reg(Symbol *symbol) {
    if (symbol->in_sp) {
        // load contents back from stack
        symbol->in_sp = 0;
        int sp_offset = symbol->sp_offset;
        int r = get_reg(symbol);
        sprintf(*(code_ptr++), "lwi\t$r%d, [$sp + %d]", r, sp_offset); 
        return r;
    } 
    
    if (!symbol->in_reg)
        get_reg(symbol);
    
    return symbol->reg;
}

void gen_mc_movi(Symbol *symbol, int val) {
    int r = get_reg(symbol);
    int h = ((val & 0xFFF00000) >> 20) & 0xFFF;
    int l = val & 0xFFFFF;
    
    if (h)
        sprintf(*(code_ptr++), "sethi\t$r%d, %d", r, h); 
    sprintf(*(code_ptr++), "movi\t$r%d, %d", r, l); 
}

void gen_mc_add(Symbol *op0, Symbol *op1, Symbol *op2) {
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    sprintf(*(code_ptr++), "add\t$r%d, $r%d, $r%d", r0, r1, r2);
    free_reg(r1);
    free_reg(r2);
}

void gen_mc_sub(Symbol *op0, Symbol *op1, Symbol *op2) {
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    sprintf(*(code_ptr++), "sub\t$r%d, $r%d, $r%d", r0, r1, r2);
    free_reg(r1);
    free_reg(r2);
}

void gen_mc_mul(Symbol *op0, Symbol *op1, Symbol *op2) {
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    sprintf(*(code_ptr++), "mul\t$r%d, $r%d, $r%d", r0, r1, r2);
    free_reg(r1);
    free_reg(r2);
}

void gen_mc_divsr(Symbol *op0, Symbol *op1, Symbol *op2, int OP) {
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    if (OP == OP_MOD) {
        sprintf(*(code_ptr++), 
            "divsr\t$r%d, r%d, $r%d, $r%d", r3, r0, r1, r2);
    } else {
        sprintf(*(code_ptr++), 
            "divsr\t$r%d, r%d, $r%d, $r%d", r0, r3, r1, r2);
    }
    printf("free %d %d %d\n", r1,r2,r3);
    free_reg(r1);
    free_reg(r2);
    free_reg(r3);
}

void gen_mc_swi(Symbol *op, int offset, int type) {
    int r = load_back_reg(op);
    sprintf(*(code_ptr++), "swi\t$r%d, [$sp + %d]", r, offset);
    free_reg(r);
}

void gen_mc_lwi(Symbol *op, int offset, int type) {
    int r = load_back_reg(op);
    sprintf(*(code_ptr++), "lwi\t$r%d, [$sp + %d]", r, offset);
}

void gen_mc_inst() {
    memset(reg, 0, sizeof(reg));
    int i;
    for (i = 0; i < ir_num; ++i) {
        int opc = IR[i].opc;
        int symbol_id;
        Symbol **operands = IR[i].operands;
        Symbol *op0, *op1, *op2;
        op0 = operands[0];
        op1 = operands[1];
        op2 = operands[2];
        
        switch (opc) {
        case OP_MOVI:
            gen_mc_movi(op0, op0->ival);
            break;
        
        case OP_ADD:
            gen_mc_add(op0, op1, op2); 
            break;
        
        case OP_SUB:
            gen_mc_sub(op0, op1, op2);
            break;
        
        case OP_MUL:
            gen_mc_mul(op0, op1, op2);
            break;
        
        case OP_DIV:
            gen_mc_divsr(op0, op1, op2, OP_DIV);
            break;
        
        case OP_MOD:
            gen_mc_divsr(op0, op1, op2, OP_MOD);
            break;
        
        case OP_STR:
            // printf("store [%d] to offset %d(%s)\n", op0->id, op0->offset, op0->name);
            gen_mc_swi(op0, op0->offset, 0);
            break;
        case OP_LDR:
            // printf("Load offset %d(%s) to [%d]\n", op0->offset, op0->name, op0->id);
            gen_mc_lwi(op0, op0->offset, 0);
            break;
        default:
            printf("Unsupport IR OPCode ... \n");
            exit(-1);
        }
    }
    #ifdef DEBUG
    printf("\x1B[36m"); 
    printf("\taddi\t$sp, $sp - %d\n", cur_offset);
    char **ptr;
    for (ptr = code_base; ptr != code_ptr; ++ptr) {
        printf("\t%s\n", *ptr);
    }
    printf("\taddi\t$sp, $sp + %d\n", cur_offset);
    printf("\tpop.s\t{ $lp }\n");
    printf("\tret\n");
    #endif
}

void printIR() {
    printf("\x1B[31m");
    printf("******** DORA-IR *********\n");
    int i;
    for (i = 0; i < ir_num; ++i) {
        int opc = IR[i].opc;
        int symbol_id;
        Symbol **operands = IR[i].operands;
        Symbol *op0, *op1, *op2;
        op0 = operands[0];
        op1 = operands[1];
        op2 = operands[2];
        
        switch (opc) {
        case OP_MOVI:
            printf("[%d] = %d\n", op0->id, op0->ival);
            break;
        case OP_ADD:
            printf("[%d] = [%d] + [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_SUB:
            printf("[%d] = [%d] - [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_MUL:
            printf("[%d] = [%d] * [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_DIV:
            printf("[%d] = [%d] / [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_MOD:
            printf("[%d] = [%d] mod [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_STR:
            printf("store [%d] to offset %d(%s)\n", op0->id, op0->offset, op0->name);
            break;
        case OP_LDR:
            printf("Load offset %d(%s) to [%d]\n", op0->offset, op0->name, op0->id);
            break;
        default:
            printf("Unsupport IR OPCode ... \n");
            exit(-1);
        }
    }
}
