%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "literal.h"
    
    #ifdef DEBUG
      #define dbg(ARGS) \
      do { \
        printf("\033[1;33m [DEBUG] "); \
        printf(ARGS); \
        printf("\033[m"); \
      } while(0);
    #else 
      #define dbg(ARGS) 
    #endif
    
    #define DET_FUNC \
        do { \
            if (has_invoke_function) { \
                dbg("Declaration invoke function error ...\n"); \
                yyerror(NULL);   \
            } \
        } while(0);
    
    #ifdef DEBUG
      #define print(ARGS,...) \
      do { \
        printf("\x1B[32m [PRINT] "); \
        printf(ARGS, __VA_ARGS__); \
        printf("\033[m"); \
      } while(0);
    #else 
      #define print(ARGS,...) 
    #endif

    struct Symbol * alloc_symbol();
    struct Instruction IR[5000];
    
    char *code_buf[5000];
    char **code_base = code_buf;
    char **code_ptr = code_buf;
    int mc_num = 0;

    int ir_num = 0;

    int has_invoke_function = 0;
    int func_count = 0;
    int cur_id = 0;
    int symbol_num = 0;
    int cur_scope = 0;
    int cur_offset = 0;
    int declare_num = 0;
        
    int cur_label = 3;
    int label_top = 0;
    int label_stack[5000];

    FILE *f_asm = NULL; 
%}


%union {
    int ival;
    double dval;
    char c;
    char *str;
    struct Symbol* symbol;
}

%start context

%token IF ELSE FOR WHILE SWITCH CASE DO DEFAULT RETURN BREAK CONTINUE
%token NUM_FLOAT CONST_STR CONST_CHAR TRUE FALSE
%token VOID INTEGER FLOAT BOOL CHARACTER CONST
%token ADD2 SUB2 LT LE GT GE EQ NE LOGAND LOGOR LOGNOT BITAND
%token <ival> NUM_INT
%token <str> IDENT 
%type <symbol> factor selfop unary muldiv addsub cmp not and expr declare init
%%

context : context globaldeclare
        | context funcdefine { dbg("Declare function body .. \n"); func_count++;}
        | globaldeclare
        | funcdefine { dbg("Declare function body ... \n"); func_count++; }
        ;

globaldeclare : functiondeclare 
              | constdeclare { dbg("global Constant declare ... \n"); }
              | declare { 
                    dbg("global function declare ...\n"); 
                    if (has_invoke_function) {
                        dbg("Declaration invoke function error ...\n");
                        yyerror(NULL);  
                    }
                }
              ;

declare : INTEGER init ';' { 
            print("Integer declaration : %d\n", declare_num);
            set_symbol_type(declare_num, TYPE_INT);
            declare_num = 0;
          } 
        | FLOAT init ';' { dbg("Float declaration\n"); } 
        | BOOL init ';' { dbg("Bool declaration\n"); }
        | CHARACTER init ';' { dbg("Char declaration\n"); }
        ;

init : init ',' IDENT '=' expr {
           $5->name = $3;
           $$ = $5;
           push_symbol($$->name, cur_scope,0);
           gen_ir_str($$, cur_offset - 4);
           declare_num++;
       }
     | init ',' IDENT { 
         $$ = alloc_symbol(); $$->name = $3; 
         push_symbol($$->name, cur_scope, 0);
         gen_ir_str($$, cur_offset - 4);
         declare_num++;
       }
     | init ',' arrayinit
     | IDENT '=' expr {
           $3->name = $1;
           $$ = $3;
           push_symbol($$->name, cur_scope, 0);
           gen_ir_str($$, cur_offset - 4);
           declare_num++;
       }
     | IDENT { 
         $$ = alloc_symbol(); $$->name = $1; 
         push_symbol($$->name, cur_scope, 0);
         gen_ir_str($$, cur_offset - 4);
         declare_num++;
       }
     | arrayinit { $$= NULL; }
     ;

arrayinit : array '=' '{' arrayelements '}'
          | array
          ;
arrayelements : arrayelements ',' expr
              | expr
              |
              ;

functiondeclare : functiontype ';'
functiontype : VOID IDENT '(' parameters ')' { dbg("declare void function\n"); }
             | BOOL IDENT '(' parameters ')' { dbg("declare bool function\n"); }
             | CHARACTER IDENT '(' parameters ')' { dbg("declare char function\n"); }
             | FLOAT IDENT '(' parameters ')' { dbg("declare double funciton\n"); }
             | INTEGER IDENT '(' parameters ')' { dbg("declare interger function\n"); } 
             ;
parameters : parameters ',' para
           | para
           | 
           ;
para : nonvoidtypes IDENT
     | nonvoidtypes array
     ;
nonvoidtypes : BOOL | CHARACTER | FLOAT | INTEGER

constdeclare : CONST nonvoidtypes constinit ';'
constinit : constinit ',' IDENT '=' CONST_CHAR
          | constinit ',' IDENT '=' CONST_STR
          | constinit ',' IDENT '=' NUM_INT
          | constinit ',' IDENT '=' NUM_FLOAT
          | constinit ',' IDENT '=' TRUE
          | constinit ',' IDENT '=' FALSE
          | IDENT '=' CONST_CHAR
          | IDENT '=' CONST_STR
          | IDENT '=' NUM_INT
          | IDENT '=' NUM_FLOAT
          | IDENT '=' TRUE
          | IDENT '=' FALSE
          ;
funcdefine : functiontype scope {
                int i;
                for (i = 0; i < 5000; ++i)
                    code_buf[i] = (char *)malloc(100);
                gen_mc_inst();
             }
scope : { cur_scope++; } scopetype { int pop_num = pop_symbol(cur_scope--); }
scopetype :  '{' localdeclare statements '}'
      |  '{' statements '}'
      |  '{' localdeclare '}'
      |  '{' '}'
      ;
localdeclare : localdeclare constdeclare
             | localdeclare declare { DET_FUNC; } 
             | constdeclare
             | declare { DET_FUNC; }
             ; 
statements : statements simplestatement { has_invoke_function = 0; }
           | statements ifelsestatement
           | statements forstatement
           | statements whilestatement
           | statements switchstatement
           | statements rbcstatement
           | simplestatement { has_invoke_function = 0; }
           | ifelsestatement
           | switchstatement
           | whilestatement
           | forstatement
           | rbcstatement 
           ;
simplestatement : IDENT '=' expr ';' { 
                    dbg("Statement .. \n");
                    int offset = lookup_symbol($1, cur_scope);  
                    if (offset < 0) {
                        print("Undefined symbol %s .. \n", $1);
                        yyerror(NULL);
                    }
                    $3->name = $1;
                    gen_ir_str($3, offset);
                  }
                | IDENT arrayoper '=' expr ';' { dbg("Array Statement .. \n");}
                ;
ifelsestatement : IF '(' expr ')' { /* Set jump to else */  
                    print("[label] if(expr) scope = %d jump to .L%d\n", cur_scope, cur_label);
                    label_stack[++label_top] = cur_label; // Push Label
                    gen_ir_brcond(cur_label);
                    cur_label++;
                  } scope { /* Gen jump */ 
                    print("if stmt scope = %d\n", cur_scope);
                    gen_ir_label(label_stack[label_top]);
                    print("[label] .L%d\n", label_stack[label_top]);
                    label_top--; // pop label 
                  } elsestmt {
                    dbg("If-else Statement ... \n"); 
                    print("else stmp scope = %d\n", cur_scope);
                  }
                ;
elsestmt : ELSE scope
         |
         ;
whilestatement : WHILE {  } '(' expr ')' scope { dbg("While statement ... \n"); }
               | DO scope WHILE '(' expr ')' ';' { dbg("Do-While statement \n"); } 
forstatement : FOR '(' forparam ';' {print("Set Label ... %c",'\n' );} forparam ';' forparam ')' scope { dbg("For statement \n"); }
forparam : | expr

switchstatement : SWITCH '(' IDENT ')' '{' casecontent default '}' { dbg("Switch Statement \n"); }
casecontent : casecontent CASE caseconst ':' casestatement
            | CASE caseconst ':' casestatement
            ;
caseconst : NUM_INT | CONST_CHAR
default : | DEFAULT ':' casestatement
casestatement : | statements
rbcstatement : RETURN expr ';' { dbg("return expr \n"); }
             | BREAK ';' { dbg("Break \n"); }
             | CONTINUE ';' { dbg("Continue \n"); }

expr : expr LOGOR and { dbg("Logic OR\n"); }
     | and
     ;
and : and LOGAND not { dbg("Logic AND \n"); }
    | not
    ;
not : LOGNOT cmp { dbg("Logic !\n"); } | cmp 
cmp : cmp NE addsub { 
        dbg("Compare !=\n"); 
        $$ = alloc_symbol();
        gen_ir_cmp($$, $1, $3, CMP_NE);
        print("[%d] = [%d] != [%d]\n", $$->id, $1->id, $3->id);
      }
    | cmp GT addsub { 
        dbg("Compare >\n"); 
        $$ = alloc_symbol();
        gen_ir_cmp($$, $1, $3, CMP_GT);
        print("[%d] = [%d] > [%d]\n", $$->id, $1->id, $3->id);
      }
    | cmp GE addsub { 
        dbg("Compare >=\n"); 
        $$ = alloc_symbol();
        gen_ir_cmp($$, $1, $3, CMP_GE);
        print("[%d] = [%d] >= [%d]\n", $$->id, $1->id, $3->id);
      }
    | cmp EQ addsub { 
        dbg("Compare ==\n"); 
        $$ = alloc_symbol();
        gen_ir_cmp($$, $1, $3, CMP_EQ);
        print("[%d] = [%d] == [%d]\n", $$->id, $1->id, $3->id);
      }
    | cmp LE addsub { 
        dbg("Compare <=\n"); 
        $$ = alloc_symbol();
        gen_ir_cmp($$, $1, $3, CMP_LE);
        print("[%d] = [%d] <= [%d]\n", $$->id, $1->id, $3->id);
      }
    | cmp LT addsub { 
        dbg("Compare < \n"); 
        $$ = alloc_symbol();
        gen_ir_cmp($$, $1, $3, CMP_LT);
        print("[%d] = [%d] < [%d]\n", $$->id, $1->id, $3->id);
      }
    | addsub
    ;
addsub : addsub '+' muldiv { 
            dbg("ADD\n");
            $$ = alloc_symbol();
            gen_ir_add($$, $1, $3);
            print("[%d] = [%d] + [%d]\n", $$->id, $1->id, $3->id);
         }
       | addsub '-' muldiv { 
            dbg("SUB\b"); 
            $$ = alloc_symbol();
            gen_ir_sub($$, $1, $3);
            print("[%d] = [%d] * [%d]\n", $$->id ,$1->id, $3->id); 
         }
       | muldiv
       ;
muldiv : muldiv '*' unary  { 
            dbg("MUL\n");
            $$ = alloc_symbol();
            gen_ir_mul($$, $1, $3);
            print("[%d] = [%d] * [%d]\n", $$->id, $1->id,  $3->id);
         }
       | muldiv '/' unary  { 
            dbg("DIV\n"); 
            $$ = alloc_symbol();
            gen_ir_div($$, $1, $3);
            print("[%d] = [%d] / [%d]\n", $$->id, $1->id,  $3->id);
         }
       | muldiv '%' unary  { 
           dbg("MOD\n"); 
           $$ = alloc_symbol();
           gen_ir_mod($$, $1, $3);
           print("[%d] = [%d] * [%d]\n", $$->id, $1->id,  $3->id);
         }
       | unary
       ;
unary : '-' selfop { 
            dbg("-(unary)\n");
            Symbol *op0 = alloc_symbol();
            Symbol *op1 = alloc_symbol();
            op1->ival = 0;
            op1->is_int = 1;
            gen_ir_movi(op1, 0);
            Symbol *op2 = $2;
            gen_ir_sub(op0, op1, op2);
            $$ = op0;
        } 
      | selfop 
selfop : factor ADD2 { dbg("ADDDDDDDD\n"); }
       | factor SUB2 { dbg("SUBBBBBBB\n"); }
       | factor
       ;

factor : '(' expr ')' { $$ = $2; dbg("Factor-(expr)\n"); }  
       | IDENT arrayoper { $$ = NULL; }
       | IDENT {
            int offset = lookup_symbol($1, cur_scope);  
            if (offset < 0) {
                print("Undefined symbol %s .. \n", $1);
                yyerror(NULL);
            }
            $$ = alloc_symbol();
            $$->name = $1;
            gen_ir_ldr($$, offset);
            print("Load offset %d(%s) to [%d]\n", $$->offset, $$->name, $$->id);
            dbg("Factor-ID\n"); 
         }
       | NUM_INT  {
           $$ = alloc_symbol();
           $$->is_int = 1;
           $$->ival = $1;
           dbg("Factor-Number\n");
           gen_ir_movi($$, $1);
           print("[%d] = %d\n", $$->id, $1);
         } 
       | NUM_FLOAT { dbg("Factor-Float\n"); } 
       | CONST_STR { dbg("Constant String\n"); }
       | CONST_CHAR { dbg("Constant Character\n"); }
       | TRUE { dbg("True factor\n"); }
       | FALSE { dbg("False factor\n"); }
       | IDENT '(' funcparams ')' { 
             has_invoke_function = 1; 
             dbg("Invoke function ...\n"); 
         }
       ;
arrayoper : arrayoper '[' expr ']' { dbg("Get [][][][]\n"); }
          | '[' expr ']' { dbg("Get []\n"); }
          ;
funcparams : funcparams ',' expr
           | expr
           |
           ;

array : IDENT arrayparm { dbg("declaration-array\n"); } 
arrayparm : arrayparm '[' NUM_INT ']'
          | '[' NUM_INT ']'
          ;
%%

int main() {
    f_asm = fopen("assembly", "w");

    yyparse();
    if (!func_count)
        yyerror(NULL);
    printf("No syntax error!\n");
    printIR();
    return 0;
}

extern char *yytext, *strptr;
extern int num_lines, num_chars, old_lines;
extern int show_source;
extern int show_token;
extern int first_token;
extern char *strptr;

#define END \
    do { \
        if (strptr == NULL) \
            break;\
        fprintf(stderr, "%c", *strptr);  \
        strptr++; \
    } while (*strptr != '\n' && *strptr != '\0'); \

int yyerror(char *s) {
    fprintf(stderr, "*** Error at line %d: ", num_lines + 1);
    END; fprintf(stderr, "\n");
    fprintf(stderr, "\n");
    fprintf(stderr, "Unmatched token: %s\n", yytext);
    fprintf(stderr, "*** syntax error\n");
    exit(-1);
}
