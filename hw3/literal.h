#ifndef __LITERAL_H
#define __LITERAL_H

enum {
  OP_MOVI = 1,
  OP_MOV,
  OP_LD,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_MOD,
  OP_STR,
  OP_LDR
};

struct Symbol {
    char* name;
    int id;
    int offset;
    int is_int;
    int is_double;
    int is_var;
    int ival;
    double dval;
    char c;
    int symbol_id;
    int in_reg;
    int reg;
    int in_sp;
    int sp_offset;
    int type;
};


typedef struct Symbol Symbol;

struct Instruction {
  int opc, operand_num;
  Symbol* operands[5]; 
};

typedef struct Instruction Instruction;

#define get_temp_reg() get_reg(NULL)

#define MAX_TABLE_SIZE 5000
#define REG_MAX 15
enum {
  TYPE_BOOL = 1,
  TYPE_INT,
  TYPE_CHAR,
  TYPE_VOID,
  TYPE_FLOAT
};

struct SymbolEntry {
   char *name;
   int scope;
   int offset;
   int id;
   int variant;
   int type;
   int total_args;
   int total_locals;
   int mode;
}  table[MAX_TABLE_SIZE];
typedef struct SymbolEntry SymbolEntry;

struct Register {
  int in_use;
  int time;
  int is_temp;
  Symbol* target;
};
typedef struct Register Register;

void push_symbol(char *name, int scope, int type) ;
int lookup_symbol(char *name, int scope) ;
void set_symbol_type(int number, int type) ;

void printIR();
void gen_ir_mov(Symbol *, Symbol *);
void gen_ir_movi(Symbol *, int);
void gen_ir_add(Symbol *, Symbol *, Symbol *);
void gen_ir_sub(Symbol *, Symbol *, Symbol *);
void gen_ir_mul(Symbol *, Symbol *, Symbol *);
void gen_ir_div(Symbol *, Symbol *, Symbol *);
void gen_ir_mod(Symbol *, Symbol *, Symbol *);
void gen_ir_str(Symbol *, int);
void gen_ir_ldr(Symbol *, int);

void gen_mc_inst();
#endif 
