%{
    #include <stdio.h>
    #include <stdlib.h>
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
    
    int has_invoke_function = 0;
%}


%union {
    int intVal;
    double dval;
}

%token IF ELSE FOR WHILE SWITCH CASE DO DEFAULT RETURN BREAK CONTINUE
%token NUM_INT IDENT NUM_FLOAT CONST_STR CONST_CHAR TRUE FALSE
%token VOID INTEGER FLOAT BOOL CHARACTER CONST
%token ADD2 SUB2 LT LE GT GE EQ NE LOGAND LOGOR LOGNOT BITAND
%token <intVal> INTCON

%%

context : context globaldeclare
        | context funcdefine { dbg("Declare function body .. \n"); }
        | globaldeclare
        | funcdefine { dbg("Declare function body ... \n"); }
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

declare : INTEGER init ';' { dbg("Integer declaration\n"); } 
        | FLOAT init ';' { dbg("Float declaration\n"); } 
        | BOOL init ';' { dbg("Bool declaration\n"); }
        | CHARACTER init ';' { dbg("Char declaration\n"); }
        ;

init : init ',' IDENT '=' expr 
     | init ',' IDENT
     | init ',' arrayinit
     | IDENT '=' expr
     | IDENT
     | arrayinit
     ;

arrayinit : array '=' '{' arrayelements '}'
          | array
          ;
arrayelements : arrayelements ',' expr
              | expr
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
funcdefine : functiontype scope
scope :  '{' localdeclare statements '}'
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
simplestatement : IDENT '=' expr ';' { dbg("Statement .. \n"); }
                | IDENT arrayoper '=' expr ';' { dbg("Array Statement .. \n");}
                ;
ifelsestatement : IF '(' expr ')' scope { dbg("Only if statement\n"); }
                | IF '(' expr ')' scope ELSE scope { dbg("IF-ELSE Statement\n"); }
                ;
whilestatement : WHILE '(' expr ')' scope { dbg("While statement ... \n"); }
               | DO scope WHILE '(' expr ')' ';' { dbg("Do-While statement \n"); } 
forstatement : FOR '(' forparam ';' forparam ';' forparam ')' scope { dbg("For statement \n"); }
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
unary : '-' selfop { dbg("-(unary)\n"); } | selfop 
selfop : factor ADD2 { dbg("ADDDDDDDD\n"); }
       | factor SUB2 { dbg("SUBBBBBBB\n"); }
       | factor
       ;

factor : '(' expr ')' { dbg("Factor-(expr)\n"); }  
       | IDENT arrayoper
       | IDENT { dbg("Factor-ID\n"); }
       | NUM_INT  { dbg("Factor-Number\n"); } 
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
    yyparse();
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
        fprintf(stderr, "%c", *strptr);  \
        strptr++; \
    } while (*strptr != '\n' && *strptr != '\0'); \

int yyerror(char *s) {
    fprintf(stderr, "*** Error at line %d: ", num_lines + 1);
    END;
    fprintf(stderr, "\n");
    fprintf(stderr, "Unmatched token: %s\n", yytext);
    fprintf(stderr, "*** syntax error\n");
    exit(-1);
}
