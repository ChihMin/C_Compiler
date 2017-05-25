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
    
    table[symbol_num].scope = scope;
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

int pop_symbol(int scope) {
    int i;
    int pop_num = 0;
    for (i = symbol_num - 1; i >= 0; i--) {
        if (table[i].scope != scope)
            break;
        pop_num++;
    }
    symbol_num -= pop_num;
    return pop_num;
}

void set_symbol_type(int number, int type) {
    int i;
    for (i = 1; i <= number; ++i) {
        int idx = symbol_num - i;
        table[i].type = type;
    }
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

void gen_ir_brcond(int label) {
    IR[ir_num].opc = OP_BRCOND;
    IR[ir_num].label = label;
    IR[ir_num].operands[0] = IR[ir_num-1].operands[0];
    IR[ir_num].operand_num = 1;
    ir_num++;
}

void gen_ir_label(int label) {
    IR[ir_num].opc = OP_LABEL;
    IR[ir_num].label = label;
    IR[ir_num].operand_num = 0;
    ir_num++;
}

void gen_ir_cmp(Symbol *op0, Symbol *op1, Symbol *op2, int type) {
    #define ins IR[ir_num]
    ins.opc = OP_CMP;
    ins.cmp_type = type;
    ins.operand_num = 3;
    ins.operands[0] = op0;
    ins.operands[1] = op1;
    ins.operands[2] = op2;
    ir_num++;
    #undef ins
}

void gen_ir_call(char *name, Symbol **argv, int argc) {
    #define ins IR[ir_num]
    int i;
    ins.opc = OP_CALL;
    ins.name = name;
    ins.operand_num = argc;
    for (i = 0; i < argc; ++i)
        ins.operands[i] = argv[i];
    ir_num++;
    #undef ins
}

void gen_ir_not(Symbol *op0, Symbol *op1) {
    #define ins IR[ir_num]
    ins.opc = OP_NOT;
    ins.operand_num = 2;
    ins.operands[0] = op0;
    ins.operands[1] = op1;
    ir_num++;
    #undef ins
}

void gen_ir_and(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_AND;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
    ir_num++;
}

void gen_ir_or(Symbol *r1, Symbol *r2, Symbol *r3) {
    IR[ir_num].opc = OP_OR;
    IR[ir_num].operands[0] = r1;
    IR[ir_num].operands[1] = r2;
    IR[ir_num].operands[2] = r3;
    IR[ir_num].operand_num = 3;
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
    
    if (!symbol->in_reg) {
        get_reg(symbol);
    } else {
        // update access time
        reg[symbol->reg].time = cur_time++;
    }
    return symbol->reg;
}

void gen_mc_movi(Symbol *symbol, int val) {
    int r = get_reg(symbol);
    int h = ((val & 0xFFFFF000) >> 12) & 0xFFFFF;
    int l = val & 0xFFF;
    
    if (h) {
        sprintf(*(code_ptr++), "movi\t$r%d, %d", r, h);
        sprintf(*(code_ptr++), "slli\t$r%d, $r%d, 12", r,r);
        sprintf(*(code_ptr++), "ori\t$r%d, $r%d, %d", r, r, l);
    } else { 
        sprintf(*(code_ptr++), "movi\t$r%d, %d", r, l); 
    }
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

void gen_mc_brcond(Symbol *op, int label) {
    int r = load_back_reg(op);
    sprintf(*(code_ptr++), "beqz\t$r%d, _L%d", r, label);
    free_reg(r);
}

void gen_mc_eq(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    
    sprintf(emit, "xor\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "slti\t$r%d, $r%d, 1", r0, r3);
    
    free_reg(r1);
    free_reg(r2);
    free_reg(r3);
    #undef emit
}

void gen_mc_ne(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    int r4 = get_temp_reg();
    
    sprintf(emit, "xor\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "slti\t$r%d, $r%d, 1", r4, r3);
    sprintf(emit, "xori\t$r%d, $r%d, 1", r0, r4);
    
    free_reg(r1);
    free_reg(r2);
    free_reg(r3);
    free_reg(r4);
    #undef emit
}

void gen_mc_ge(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
 
    sprintf(emit, "slts\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "xori\t$r%d, $r%d, 1", r0, r3);
    
    free_reg(r1);
    free_reg(r2);
    free_reg(r3);
    #undef emit
}

void gen_mc_gt(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    int r4 = get_temp_reg();

    sprintf(emit, "slts\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "xor\t$r%d, $r%d, $r%d", r4, r1, r2);
    sprintf(emit, "slti\t$r%d, $r%d, 1", r4, r4);
    sprintf(emit, "or\t$r%d, $r%d, $r%d", r0, r3, r4);
    sprintf(emit, "xori\t$r%d, $r%d, 1", r0, r0);
    
    free_reg(r1);
    free_reg(r2);
    free_reg(r3);
    free_reg(r4);
    #undef emit
}

void gen_mc_le(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    int r4 = get_temp_reg();
 
    sprintf(emit, "slts\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "xor\t$r%d, $r%d, $r%d", r4, r1, r2);
    sprintf(emit, "slti\t$r%d, $r%d, 1", r4, r4);
    sprintf(emit, "or\t$r%d, $r%d, $r%d", r0, r3, r4);
    
    free_reg(r1);
    free_reg(r2);
    free_reg(r3);
    free_reg(r4);
    #undef emit
}

void gen_mc_lt(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
 
    sprintf(emit, "slts\t$r%d, $r%d, $r%d", r0, r1, r2);
    
    free_reg(r1);
    free_reg(r2);
    #undef emit
}

void gen_mc_call(char *name, Symbol **argv,  int argc) {
    // Here only can handle five parameters to call the function ...
    #define emit *(code_ptr++)
    int i;
    int reg_stack[5];
    for (i = 0; i < argc; ++i)
        reg_stack[i] = load_back_reg(argv[i]);
    
    sprintf(emit, "addi\t$sp, $sp, -%d", argc * 4); 
    for (i = 0; i < argc; ++i)
        sprintf(emit, "swi\t$r%d, [$sp + %d]", reg_stack[i], 4 * i);
    
    for (i = 0; i < argc; ++i)
        sprintf(emit, "lwi\t$r%d, [$sp + %d]", i, 4 * i);

    sprintf(emit, "bal\t%s", name);
    
    for (i = 0; i < argc; ++i) 
        sprintf(emit, "lwi\t$r%d, [$sp + %d]", reg_stack[i], 4 * i);
    sprintf(emit, "addi\t$sp, $sp, %d", argc * 4);
    
    for (i = 0; i < argc; ++i)
        free_reg(reg_stack[i]);

    #undef emit
}

void gen_mc_not(Symbol *op0, Symbol *op1) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    
    sprintf(emit, "slti\t$r%d, $r%d, 1", r0, r1);
    free_reg(r1);

    #undef emit
}

void gen_mc_and(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    
    sprintf(emit, "slti\t$r%d, $r%d, 1", r1, r1);
    sprintf(emit, "slti\t$r%d, $r%d, 1", r2, r2);
    sprintf(emit, "or\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "xori\t$r%d, $r%d, 1", r0, r3);

    free_reg(r1);
    free_reg(r2);
    free_reg(r3);

    #undef emit
}

void gen_mc_or(Symbol *op0, Symbol *op1, Symbol *op2) {
    #define emit *(code_ptr++)
    int r0 = load_back_reg(op0);
    int r1 = load_back_reg(op1);
    int r2 = load_back_reg(op2);
    int r3 = get_temp_reg();
    
    sprintf(emit, "or\t$r%d, $r%d, $r%d", r3, r1, r2);
    sprintf(emit, "slti\t$r%d, $r%d, 1", r3, r3);
    sprintf(emit, "xori\t$r%d, $r%d, 1", r0, r3);

    free_reg(r1);
    free_reg(r2);
    free_reg(r3);

    #undef emit
}

void gen_mc_inst() {
    memset(reg, 0, sizeof(reg));
    int i, j;
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
            gen_mc_swi(op0, op0->offset, 0);
            break;
        case OP_LDR:
            gen_mc_lwi(op0, op0->offset, 0);
            break;
        
        case OP_BRCOND:
            gen_mc_brcond(op0, IR[i].label);
            break;
         
        case OP_LABEL:
            sprintf(*(code_ptr++), "_L%d:", IR[i].label);
            break;

        case OP_CMP:
            // printf("CMP [%d] = [%d] ", op0->id, op1->id);
            switch (IR[i].cmp_type) {
            case CMP_EQ:
                gen_mc_eq(op0, op1, op2);
                break;

            case CMP_NE:
                gen_mc_ne(op0, op1, op2);
                break;

            case CMP_GE:
                gen_mc_ge(op0, op1, op2);
                break;
            
            case CMP_GT:
                gen_mc_gt(op0, op1, op2);
                break;

            case CMP_LE:
                gen_mc_le(op0, op1, op2);
                break;

            case CMP_LT:
                gen_mc_lt(op0, op1, op2);
                break;
            }
            break;
        
        case OP_CALL:
            gen_mc_call(IR[i].name, IR[i].operands, IR[i].operand_num);
            break;
        
        case OP_NOT:
            gen_mc_not(op0, op1);
            break;

        case OP_AND:
            gen_mc_and(op0, op1, op2);
            break;

        case OP_OR:
            gen_mc_or(op0, op1, op2);
            break;

        default:
            printf("Unsupport IR OPCode - %d ... \n", opc);
            exit(-1);
        }
    }
    #ifdef DEBUG
    printf("\x1B[36m");
    printf("\taddi\t$sp, $sp, -%d\n", cur_offset);
    char **ptr;
    for (ptr = code_base; ptr != code_ptr; ++ptr) {
        if (**ptr != '_')
            printf("\t");
        else
            printf("\n");
        printf("%s\n", *ptr);
    }
    printf("\taddi\t$sp, $sp, +%d\n", cur_offset);
    #endif
    
    fprintf(f_asm, "\n\n\n"); 
    fprintf(f_asm, "\taddi\t$sp, $sp, -%d\n", cur_offset);
    char **_ptr;
    for (_ptr = code_base; _ptr != code_ptr; ++_ptr) {
        if (**_ptr != '_')
            fprintf(f_asm, "\t");
        else
            fprintf(f_asm, "\n");
        fprintf(f_asm, "%s\n", *_ptr);
    }
    fprintf(f_asm, "\taddi\t$sp, $sp, %d\n", cur_offset);
}

void printIR() {
    printf("\x1B[31m");
    printf("******** DORA-IR *********\n");
    int i, j;
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
        case OP_OR:
            printf("[%d] = [%d] || [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_AND:
            printf("[%d] = [%d] && [%d]\n", op0->id, op1->id, op2->id);
            break;
        case OP_STR:
            printf("store [%d] to offset %d(%s)\n", op0->id, op0->offset, op0->name);
            break;
        case OP_LDR:
            printf("Load offset %d(%s) to [%d]\n", op0->offset, op0->name, op0->id);
            break;
        case OP_BRCOND:
            printf("Brcond [%d] == 0, Jump to .L%d\n", op0->id, IR[i].label); 
            break;
        case OP_LABEL:
            printf("\n.L%d:\n", IR[i].label);
            break;
        case OP_CMP:
            printf("CMP [%d] = [%d] ", op0->id, op1->id);
            switch (IR[i].cmp_type) {
            case CMP_EQ:
                printf("==");
                break;

            case CMP_NE:
                printf("!=");
                break;

            case CMP_GE:
                printf(">=");
                break;
            
            case CMP_GT:
                printf(">");
                break;

            case CMP_LE:
                printf("<=");
                break;

            case CMP_LT:
                printf("<");
                break;
            }
            printf(" [%d]\n", op2->id);
            break;
        
        case OP_CALL:
            printf("Call %s ", IR[i].name);
            for (j = 0; j < IR[i].operand_num; ++j)
                printf("[%d], ", IR[i].operands[j]->id);
            printf("\n");
            break;
        
        case OP_NOT:
            printf("[%d] = NOT [%d]\n", op0->id, op1->id);
            break;
            
        default:
            printf("Unsupport IR OPCode ... \n");
            exit(-1);
        }
    }
}
