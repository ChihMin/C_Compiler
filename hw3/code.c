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
