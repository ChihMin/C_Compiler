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
extern YYSTYPE yylval;
