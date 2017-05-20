#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20140101

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "hw2.y"
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
#line 27 "hw2.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
    int intVal;
    double dval;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 54 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define NUM_INT 257
#define IDENT 258
#define NUM_FLOAT 259
#define CONST_STR 260
#define CONST_CHAR 261
#define TRUE 262
#define FALSE 263
#define VOID 264
#define INTEGER 265
#define FLOAT 266
#define BOOL 267
#define CHARACTER 268
#define CONST 269
#define ADD2 270
#define SUB2 271
#define LT 272
#define LE 273
#define GT 274
#define GE 275
#define EQ 276
#define NE 277
#define LOGAND 278
#define LOGOR 279
#define LOGNOT 280
#define BITAND 281
#define INTCON 282
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    0,    0,    1,    1,    1,    5,    5,    5,
    5,    6,    6,    6,    6,    6,    6,    8,    8,   10,
   10,    3,   11,   11,   11,   11,   11,   12,   12,   12,
   13,   13,   14,   14,   14,   14,    4,   15,   15,   15,
   15,   15,   15,   15,   15,   15,   15,   15,   15,    2,
    2,    2,    2,   16,   16,   16,   16,   17,   17,   18,
   18,    7,    7,   20,   20,   21,   21,   22,   22,   22,
   22,   22,   22,   22,   23,   23,   23,   24,   24,   24,
   24,   25,   25,   26,   26,   26,   27,   27,   27,   27,
   27,   27,   27,   27,   27,   27,   19,   19,   28,   28,
   28,    9,   29,   29,
};
static const short yylen[] = {                            2,
    2,    2,    1,    1,    1,    1,    1,    3,    3,    3,
    3,    5,    3,    3,    3,    1,    1,    5,    1,    3,
    1,    2,    5,    5,    5,    5,    5,    3,    1,    0,
    2,    2,    1,    1,    1,    1,    4,    5,    5,    5,
    5,    5,    5,    3,    3,    3,    3,    3,    3,    5,
    4,    4,    3,    2,    2,    1,    1,    2,    1,    4,
    5,    3,    1,    3,    1,    2,    1,    3,    3,    3,
    3,    3,    3,    1,    3,    3,    1,    3,    3,    3,
    1,    2,    1,    2,    2,    1,    3,    2,    1,    1,
    1,    1,    1,    1,    1,    4,    4,    3,    3,    1,
    0,    2,    4,    3,
};
static const short yydefred[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    3,    4,    5,
    6,    7,    0,    0,    0,    0,   17,    0,    0,    0,
    0,    0,    0,    0,   36,   35,   33,   34,    0,    1,
    2,   22,    0,    0,    0,    0,    0,    0,    8,    0,
    0,    0,    9,    0,   10,    0,   11,    0,    0,    0,
    0,    0,    0,    0,   53,   56,   57,    0,    0,   59,
    0,   29,    0,   90,    0,   91,   92,   93,   94,   95,
    0,    0,    0,    0,    0,   65,    0,    0,    0,   81,
   83,    0,    0,    0,    0,    0,   14,    0,    0,    0,
    0,    0,   37,    0,    0,    0,    0,    0,   52,   54,
   55,    0,   51,   58,    0,   23,    0,   32,    0,    0,
    0,    0,   82,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   84,   85,   27,  104,
    0,    0,    0,    0,   26,   24,   25,   46,   47,   45,
   44,   48,   49,    0,    0,    0,    0,    0,   50,   28,
    0,    0,   87,    0,   64,    0,    0,    0,    0,    0,
    0,    0,    0,   78,   79,   80,  103,    0,    0,   18,
    0,   60,   98,    0,    0,    0,   96,    0,   40,   41,
   39,   38,   42,   43,   61,   97,    0,
};
static const short yydgoto[] = {                          7,
    8,    9,   10,   11,   12,   16,   74,   17,   18,  134,
   13,   61,   62,   63,   49,   58,   59,   60,   97,   75,
   76,   77,   78,   79,   80,   81,   82,  152,   38,
};
static const short yysindex[] = {                       -56,
 -200, -196, -194, -193, -177,  104,  -56,    0,    0,    0,
    0,    0,  -36,   74,  -11,   73,    0,   63,   12,  100,
   46,  105,   66,  112,    0,    0,    0,    0, -127,    0,
    0,    0,  146,  104,    6,  104, -106,   88,    0,  -75,
   77,  104,    0,  104,    0,  104,    0,  154,  131,  -20,
  -35,  -35,  -35,  -35,    0,    0,    0,  159, -116,    0,
   54,    0,  -32,    0,   -1,    0,    0,    0,    0,    0,
  125,    6,  133,  -25,   -6,    0,  126,   -7,  182,    0,
    0, -227,  111,  150,   28,   -8,    0,    6,  184,  364,
  366,  116,    0,   15,    6,    6,   11,   44,    0,    0,
    0, -111,    0,    0,  104,    0,  196,    0,    6,  205,
  126,   -9,    0,    6,    6,  125,  125,  125,  125,  125,
  125,  125,  125,  125,  125,  125,    0,    0,    0,    0,
  228,    6,  -25,  -31,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  261,  -58,  -90,    6,    6,    0,    0,
  -25,  375,    0,   -6,    0,   -7,   -7,   -7,   -7,   -7,
   -7,  182,  182,    0,    0,    0,    0,  -25,    6,    0,
  174,    0,    0,  -57,  -81,    6,    0,  -25,    0,    0,
    0,    0,    0,    0,    0,    0,  -25,
};
static const short yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  132,    0,    0,  137,  132,    0,
  132,    0,  132,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  377,    0,  377,    0,  119,    0,    0,
    0,  377,    0,  377,    0,  377,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -37,    0,    0,    0,    0,    0,
    0,    0,    0,  140,   95,    0,   -4,   33,    4,    0,
    0,  -17,    0,    0,    0,  142,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  132,    0,    0,
    0,    0,    0,    0,    0,    0,  379,    0,  397,  -26,
   81,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  -13,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  398,    0,    0,  102,    0,   41,   52,   60,   69,   79,
   89,   16,   25,    0,    0,    0,    0,  143,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  -10,    0,    0,
    0,    0,    0,    0,    0,    0,  409,
};
static const short yygindex[] = {                         0,
  316,  333,    0,   21,   58,  164,  334,  309,  287,    0,
    0,  161,  275,  383,    0,    0,  339,  -24,  344,  318,
  325,  380,  328,   70,  106,  381,    0,    0,    0,
};
#define YYTABLESIZE 510
static const short yytable[] = {                         89,
  172,  185,  173,   89,   89,   89,   89,   89,  103,   89,
   88,  186,  169,  149,   88,   88,   88,   88,   88,   86,
   88,   89,   32,   86,   86,   86,   86,   86,   36,   86,
   21,  153,   88,   20,  104,  122,   67,  123,  109,   67,
   95,   86,  127,  128,   77,   72,   77,   77,   77,   35,
   73,   42,  132,   56,   67,   89,   75,   14,   75,   75,
   75,   15,   77,   19,   21,   76,   88,   76,   76,   76,
   96,  147,   35,   74,   75,   86,   74,  104,  100,   37,
   23,   73,   37,   76,   73,   44,   33,   89,   67,   96,
   57,   74,   72,  170,  106,   72,   77,  105,   88,   73,
   69,  148,   37,   69,   35,   46,   35,   86,   75,   70,
   72,   21,   70,   34,   20,  101,   40,   76,   69,   71,
   67,   66,   71,   41,   66,   74,   35,   70,   77,   68,
   48,   39,   68,   73,   37,   63,   37,   71,   63,   66,
   75,   50,   62,   40,   72,   62,   50,   68,   40,   76,
   84,  129,   69,   63,  105,   40,   37,   74,   43,  102,
   62,   70,  102,   45,   72,   73,   20,   22,   24,   73,
   47,   71,   72,   66,   94,   16,   72,  102,   85,  102,
   19,   68,   86,   15,   69,   13,   12,   63,  114,   93,
   16,  162,  163,   70,   62,   19,   83,  114,   15,   88,
   13,   12,   89,   71,   90,   66,   91,    1,    2,    3,
    4,    5,    6,   68,   92,   20,   22,   24,  126,   63,
  114,  114,   98,  124,  135,  107,   62,  105,  125,  164,
  165,  166,   89,   89,   89,   89,   89,   89,   89,   89,
   89,   89,  130,   88,   88,   88,   88,   88,   88,   88,
   88,   88,   88,  114,   86,   86,   86,   86,   86,   86,
   86,   86,   64,   65,   66,   67,   68,   69,   70,  114,
   55,  115,  144,   67,   67,   77,   77,   77,   77,   77,
   77,   77,   77,   99,  131,   71,   37,   75,   75,   75,
   75,   75,   75,   75,   75,  148,   76,   76,   76,   76,
   76,   76,   76,   76,   74,   74,   74,   74,   74,   74,
   74,   74,   73,   73,   73,   73,   73,   73,   73,   73,
  167,  171,   30,   72,   72,   72,   72,   72,   72,   72,
   72,   69,   69,   69,   69,   69,   69,   69,   69,   31,
   70,   70,   70,   70,   70,   70,   70,   70,   87,  108,
   71,   71,   71,   71,   71,   71,   71,   71,   66,   66,
   68,   68,   68,   68,   68,   68,   68,   68,   25,   26,
   27,   28,  138,   63,  139,  140,  141,  142,  143,  150,
   62,   64,   65,   66,   67,   68,   69,   70,   29,   64,
   65,   66,   67,   68,   69,   70,  102,  116,  117,  118,
  119,  120,  121,   50,  136,  112,  137,  105,  110,  105,
   51,   52,   53,   54,    6,  177,   50,   30,  176,   31,
   30,  133,   31,   51,   52,   53,   54,    6,  145,  146,
  179,  154,  180,  181,  182,  183,  184,  101,  100,  155,
  101,  100,  151,  156,  157,  158,  159,  160,  161,   99,
  111,    0,   99,  113,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  168,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  174,  175,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  178,    0,    0,    0,    0,    0,    0,  187,
};
static const short yycheck[] = {                         37,
   59,   59,   93,   41,   42,   43,   44,   45,  125,   47,
   37,   93,   44,  125,   41,   42,   43,   44,   45,   37,
   47,   59,   59,   41,   42,   43,   44,   45,   40,   47,
   44,   41,   59,   44,   59,   43,   41,   45,   40,   44,
   61,   59,  270,  271,   41,   40,   43,   44,   45,   61,
   45,   40,   61,   33,   59,   93,   41,  258,   43,   44,
   45,  258,   59,  258,  258,   41,   93,   43,   44,   45,
   91,   61,   61,   41,   59,   93,   44,  102,   58,   91,
  258,   41,   91,   59,   44,   40,  123,  125,   93,   91,
   33,   59,   41,  125,   41,   44,   93,   44,  125,   59,
   41,   91,   91,   44,   61,   40,   61,  125,   93,   41,
   59,  125,   44,   40,  125,   58,   44,   93,   59,   41,
  125,   41,   44,   61,   44,   93,   61,   59,  125,   41,
  258,   59,   44,   93,   91,   41,   91,   59,   44,   59,
  125,  258,   41,   44,   93,   44,  258,   59,   44,  125,
  257,   41,   93,   59,   44,   44,   91,  125,   59,   41,
   59,   93,   44,   59,   40,  125,    3,    4,    5,   45,
   59,   93,   40,   93,   44,   44,  125,   59,   91,   61,
   44,   93,  258,   44,  125,   44,   44,   93,  279,   59,
   59,  122,  123,  125,   93,   59,   36,  279,   59,  123,
   59,   59,   42,  125,   44,  125,   46,  264,  265,  266,
  267,  268,  269,  125,   61,   52,   53,   54,   37,  125,
  279,  279,  258,   42,   41,  258,  125,   44,   47,  124,
  125,  126,  270,  271,  272,  273,  274,  275,  276,  277,
  278,  279,   93,  270,  271,  272,  273,  274,  275,  276,
  277,  278,  279,  279,  272,  273,  274,  275,  276,  277,
  278,  279,  257,  258,  259,  260,  261,  262,  263,  279,
  125,  278,  258,  278,  279,  272,  273,  274,  275,  276,
  277,  278,  279,  125,  257,  280,   91,  272,  273,  274,
  275,  276,  277,  278,  279,   91,  272,  273,  274,  275,
  276,  277,  278,  279,  272,  273,  274,  275,  276,  277,
  278,  279,  272,  273,  274,  275,  276,  277,  278,  279,
   93,   61,    7,  272,  273,  274,  275,  276,  277,  278,
  279,  272,  273,  274,  275,  276,  277,  278,  279,    7,
  272,  273,  274,  275,  276,  277,  278,  279,   40,   63,
  272,  273,  274,  275,  276,  277,  278,  279,  278,  279,
  272,  273,  274,  275,  276,  277,  278,  279,  265,  266,
  267,  268,  257,  279,  259,  260,  261,  262,  263,  105,
  279,  257,  258,  259,  260,  261,  262,  263,    6,  257,
  258,  259,  260,  261,  262,  263,   58,  272,  273,  274,
  275,  276,  277,  258,   41,   72,   41,   44,   65,   44,
  265,  266,  267,  268,  269,   41,  258,   41,   44,   41,
   44,   88,   44,  265,  266,  267,  268,  269,   95,   96,
  257,  114,  259,  260,  261,  262,  263,   41,   41,  115,
   44,   44,  109,  116,  117,  118,  119,  120,  121,   41,
   71,   -1,   44,   73,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  132,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
  147,  148,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  169,   -1,   -1,   -1,   -1,   -1,   -1,  176,
};
#define YYFINAL 7
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 282
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? (YYMAXTOKEN + 1) : (a))
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,"'%'",0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,
0,"';'",0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",
0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,"NUM_INT","IDENT","NUM_FLOAT","CONST_STR","CONST_CHAR",
"TRUE","FALSE","VOID","INTEGER","FLOAT","BOOL","CHARACTER","CONST","ADD2",
"SUB2","LT","LE","GT","GE","EQ","NE","LOGAND","LOGOR","LOGNOT","BITAND",
"INTCON","illegal-symbol",
};
static const char *yyrule[] = {
"$accept : context",
"context : context globaldeclare",
"context : context funcdefine",
"context : globaldeclare",
"context : funcdefine",
"globaldeclare : functiondeclare",
"globaldeclare : constdeclare",
"globaldeclare : declare",
"declare : INTEGER init ';'",
"declare : FLOAT init ';'",
"declare : BOOL init ';'",
"declare : CHARACTER init ';'",
"init : init ',' IDENT '=' expr",
"init : init ',' IDENT",
"init : init ',' arrayinit",
"init : IDENT '=' expr",
"init : IDENT",
"init : arrayinit",
"arrayinit : array '=' '{' arrayelements '}'",
"arrayinit : array",
"arrayelements : arrayelements ',' expr",
"arrayelements : expr",
"functiondeclare : functiontype ';'",
"functiontype : VOID IDENT '(' parameters ')'",
"functiontype : BOOL IDENT '(' parameters ')'",
"functiontype : CHARACTER IDENT '(' parameters ')'",
"functiontype : FLOAT IDENT '(' parameters ')'",
"functiontype : INTEGER IDENT '(' parameters ')'",
"parameters : parameters ',' para",
"parameters : para",
"parameters :",
"para : nonvoidtypes IDENT",
"para : nonvoidtypes array",
"nonvoidtypes : BOOL",
"nonvoidtypes : CHARACTER",
"nonvoidtypes : FLOAT",
"nonvoidtypes : INTEGER",
"constdeclare : CONST nonvoidtypes constinit ';'",
"constinit : constinit ',' IDENT '=' CONST_CHAR",
"constinit : constinit ',' IDENT '=' CONST_STR",
"constinit : constinit ',' IDENT '=' NUM_INT",
"constinit : constinit ',' IDENT '=' NUM_FLOAT",
"constinit : constinit ',' IDENT '=' TRUE",
"constinit : constinit ',' IDENT '=' FALSE",
"constinit : IDENT '=' CONST_CHAR",
"constinit : IDENT '=' CONST_STR",
"constinit : IDENT '=' NUM_INT",
"constinit : IDENT '=' NUM_FLOAT",
"constinit : IDENT '=' TRUE",
"constinit : IDENT '=' FALSE",
"funcdefine : functiontype '{' localdeclare statements '}'",
"funcdefine : functiontype '{' statements '}'",
"funcdefine : functiontype '{' localdeclare '}'",
"funcdefine : functiontype '{' '}'",
"localdeclare : localdeclare constdeclare",
"localdeclare : localdeclare declare",
"localdeclare : constdeclare",
"localdeclare : declare",
"statements : statements simplestatement",
"statements : simplestatement",
"simplestatement : IDENT '=' expr ';'",
"simplestatement : IDENT arrayoper '=' expr ';'",
"expr : expr LOGOR and",
"expr : and",
"and : and LOGAND not",
"and : not",
"not : LOGNOT cmp",
"not : cmp",
"cmp : cmp NE addsub",
"cmp : cmp GT addsub",
"cmp : cmp GE addsub",
"cmp : cmp EQ addsub",
"cmp : cmp LE addsub",
"cmp : cmp LT addsub",
"cmp : addsub",
"addsub : addsub '+' muldiv",
"addsub : addsub '-' muldiv",
"addsub : muldiv",
"muldiv : muldiv '*' unary",
"muldiv : muldiv '/' unary",
"muldiv : muldiv '%' unary",
"muldiv : unary",
"unary : '-' selfop",
"unary : selfop",
"selfop : factor ADD2",
"selfop : factor SUB2",
"selfop : factor",
"factor : '(' expr ')'",
"factor : IDENT arrayoper",
"factor : IDENT",
"factor : NUM_INT",
"factor : NUM_FLOAT",
"factor : CONST_STR",
"factor : CONST_CHAR",
"factor : TRUE",
"factor : FALSE",
"factor : IDENT '(' funcparams ')'",
"arrayoper : arrayoper '[' expr ']'",
"arrayoper : '[' expr ']'",
"funcparams : funcparams ',' expr",
"funcparams : expr",
"funcparams :",
"array : IDENT arrayparm",
"arrayparm : arrayparm '[' NUM_INT ']'",
"arrayparm : '[' NUM_INT ']'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 182 "hw2.y"

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
#line 511 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 2:
#line 40 "hw2.y"
	{ dbg("Declare function body .. \n"); }
break;
case 4:
#line 42 "hw2.y"
	{ dbg("Declare function body ... \n"); }
break;
case 6:
#line 46 "hw2.y"
	{ dbg("global Constant declare ... \n"); }
break;
case 7:
#line 47 "hw2.y"
	{ 
                    dbg("global function declare ...\n"); 
                    if (has_invoke_function) {
                        dbg("Declaration invoke function error ...\n");
                        yyerror(NULL);  
                    }
                }
break;
case 8:
#line 56 "hw2.y"
	{ dbg("Integer declaration\n"); }
break;
case 9:
#line 57 "hw2.y"
	{ dbg("Float declaration\n"); }
break;
case 10:
#line 58 "hw2.y"
	{ dbg("Bool declaration\n"); }
break;
case 11:
#line 59 "hw2.y"
	{ dbg("Char declaration\n"); }
break;
case 23:
#line 78 "hw2.y"
	{ dbg("declare void function\n"); }
break;
case 24:
#line 79 "hw2.y"
	{ dbg("declare bool function\n"); }
break;
case 25:
#line 80 "hw2.y"
	{ dbg("declare char function\n"); }
break;
case 26:
#line 81 "hw2.y"
	{ dbg("declare double funciton\n"); }
break;
case 27:
#line 82 "hw2.y"
	{ dbg("declare interger function\n"); }
break;
case 55:
#line 114 "hw2.y"
	{ DET_FUNC; }
break;
case 57:
#line 116 "hw2.y"
	{ DET_FUNC; }
break;
case 58:
#line 118 "hw2.y"
	{ has_invoke_function = 0; }
break;
case 59:
#line 119 "hw2.y"
	{ has_invoke_function = 0; }
break;
case 60:
#line 121 "hw2.y"
	{ dbg("Statement .. \n"); }
break;
case 61:
#line 122 "hw2.y"
	{ dbg("Array Statement .. \n");}
break;
case 62:
#line 125 "hw2.y"
	{ dbg("Logic OR\n"); }
break;
case 64:
#line 128 "hw2.y"
	{ dbg("Logic AND \n"); }
break;
case 66:
#line 131 "hw2.y"
	{ dbg("Logic !\n"); }
break;
case 68:
#line 132 "hw2.y"
	{ dbg("Compare !=\n"); }
break;
case 69:
#line 133 "hw2.y"
	{ dbg("Compare >\n"); }
break;
case 70:
#line 134 "hw2.y"
	{ dbg("Compare >=\n"); }
break;
case 71:
#line 135 "hw2.y"
	{ dbg("Compare ==\n"); }
break;
case 72:
#line 136 "hw2.y"
	{ dbg("Compare <=\n"); }
break;
case 73:
#line 137 "hw2.y"
	{ dbg("Compare <\b"); }
break;
case 75:
#line 140 "hw2.y"
	{ dbg("ADD\n"); }
break;
case 76:
#line 141 "hw2.y"
	{ dbg("SUB\b"); }
break;
case 78:
#line 144 "hw2.y"
	{ dbg("MUL\n"); }
break;
case 79:
#line 145 "hw2.y"
	{ dbg("DIV\n"); }
break;
case 80:
#line 146 "hw2.y"
	{ dbg("MOD\n"); }
break;
case 82:
#line 149 "hw2.y"
	{ dbg("-(unary)\n"); }
break;
case 84:
#line 150 "hw2.y"
	{ dbg("ADDDDDDDD\n"); }
break;
case 85:
#line 151 "hw2.y"
	{ dbg("SUBBBBBBB\n"); }
break;
case 87:
#line 155 "hw2.y"
	{ dbg("Factor-(expr)\n"); }
break;
case 89:
#line 157 "hw2.y"
	{ dbg("Factor-ID\n"); }
break;
case 90:
#line 158 "hw2.y"
	{ dbg("Factor-Number\n"); }
break;
case 91:
#line 159 "hw2.y"
	{ dbg("Factor-Float\n"); }
break;
case 92:
#line 160 "hw2.y"
	{ dbg("Constant String\n"); }
break;
case 93:
#line 161 "hw2.y"
	{ dbg("Constant Character\n"); }
break;
case 94:
#line 162 "hw2.y"
	{ dbg("True factor\n"); }
break;
case 95:
#line 163 "hw2.y"
	{ dbg("False factor\n"); }
break;
case 96:
#line 164 "hw2.y"
	{ 
             has_invoke_function = 1; 
             dbg("Invoke function ...\n"); 
         }
break;
case 97:
#line 169 "hw2.y"
	{ dbg("Get [][][][]\n"); }
break;
case 98:
#line 170 "hw2.y"
	{ dbg("Get []\n"); }
break;
case 102:
#line 177 "hw2.y"
	{ dbg("declaration-array\n"); }
break;
#line 914 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
