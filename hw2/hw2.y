%{
    #include <stdio.h>
    #include <stdlib.h>
    #ifdef DEBUG
      #define dbg(ARGS) \
      do { \
        printf("[DEBUG] "); \
        printf(ARGS); \
      } while(0);
    #else 
      #define dbg(ARGS) 
    #endif
%}


%union {
    int intVal;
    double dval;
}

%token NUM_INT IDENT NUM_FLOAT CONST_STR CONST_CHAR TRUE FALSE
%token VOID INTEGER FLOAT BOOL CHARACTER CONST
%token ADD2 SUB2 LT LE GT GE EQ NE LOGAND LOGOR LOGNOT BITAND
%token <intVal> INTCON

%%

context : context declare
        | context constdeclare
        | constdeclare
        | declare
        ;

declare : INTEGER init ';' { dbg("Integer declaration\n"); } 
        | FLOAT init ';' { dbg("Float declaration\n"); } 
        | BOOL init ';' { dbg("Bool declaration\n"); }
        | CHARACTER init ';' { dbg("Char declaration\n"); }
        ;

init : init ',' IDENT '=' expr 
     | init ',' IDENT
     | init ',' array
     | IDENT '=' expr
     | IDENT
     | array
     ;

constdeclare : CONST INTEGER constinit ';'
             | CONST FLOAT constinit ';'
             | CONST CHARACTER constinit ';'
             | CONST BOOL constinit ';'
             ;

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

expr : expr LOGOR not { dbg("Logic OR\n"); }
     | expr LOGAND not { dbg("Logic AND\n"); }
     | not
     ;
not : LOGNOT cmp | cmp { dbg("Logic !\n"); }
cmp : cmp NE addsub { dbg("Compare !=\n"); }
    | cmp GT addsub { dbg("Compare >\n"); }
    | cmp GE addsub { dbg("Compare >=\n"); }
    | cmp EQ addsub { dbg("Compare ==\n"); }
    | cmp LE addsub { dbg("Compare <=\n"); }
    | cmp LT addsub { dbg("Compare <\b"); }
    | addsub
    ;
addsub : addsub '+' muldiv { dbg("ADD\n"); }
       | addsub '-' muldiv { dbg("SUB\b"); }
       | muldiv
       ;
muldiv : muldiv '*' unary  { dbg("MUL\n"); }
       | muldiv '/' unary  { dbg("DIV\n"); }
       | muldiv '%' unary  { dbg("MOD\n"); }
       | unary
       ;
unary : '-' selfop | selfop { dbg("-(unary)\n"); }
selfop : arrayidx ADD2 { dbg("ADDDDDDDD\n"); }
       | arrayidx SUB2 { dbg("SUBBBBBBB\n"); }
       | arrayidx
       ;
arrayidx : '[' expr ']' | factor { dbg("ARRAY or Factor\n"); }

factor : '(' expr ')' { dbg("Factor-(expr)\n"); }  
       | IDENT { dbg("Factor-ID\n"); }
       | NUM_INT  { dbg("Factor-Number\n"); } 
       | NUM_FLOAT { dbg("Factor-Float\n"); } 
       | TRUE
       | FALSE
       | array
       ;

array : IDENT arrayparm { dbg("Factor-array\n"); } 
      ;

arrayparm : arrayparm '[' NUM_INT ']'
          | '[' NUM_INT ']'
          ;
%%

int main() {
    yyparse();
    return 0;
}

extern char *yytext, *strptr;
extern int num_lines, num_chars;
extern int show_source;
extern int show_token;
extern char *strptr;

#define END \
    do { \
        fprintf(stderr, "%c", *strptr);  \
        strptr++; \
    } while (*strptr != '\n' && *strptr != '\0'); \

int yyerror(char *s) {
    fprintf(stderr, "*** Error at line %d: ", num_lines);
    END;
    fprintf(stderr, "\n");
    fprintf(stderr, "Unmatched token: %s\n", yytext);
    fprintf(stderr, "*** syntax error\n");
    exit(-1);
}
