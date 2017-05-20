DB  (([0-9]+\.[0-9]*)|(\.[0-9]+)|([0-9]+\.))
OP  ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"<"|"<="|">"|">="|"=="|"!="|"="|"&&"|"||"|"!"|"&")
PU  ("["|"]"|"("|")"|"{"|"}"|":"|";"|","|".")
SS  (([\t\ ])|("/*"(.)*"*/"))
CH  ((\\\')|(\\\")|(\\\?)|(\\\\)|(\\t)|(\\n)|([^\'\\\n]))

%{

#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#define PL \
    if (first_token) { \
        strptr = yytext; \
        first_token = 0; \
    }

#define PT(type) \
    if (show_token) \
        printf("#%s:%s\n", type, yytext);

#define END \
    old_lines = num_lines++ ;\
    if (show_source) { \
        last_strptr = strptr; \
        printf("%d:", num_lines); \
        do { \
            printf("%c", *strptr);  \
            strptr++; \
        } while (*strptr != '\n' && *strptr != '\0'); \
        if (*strptr == '\n') \
            printf("\n"); \
    } \
    first_token = 1;

#define ERROR \
    ++num_lines; \
    fprintf(stderr, "Error at line %d: %s\n", num_lines, yytext); \
    exit(1); 

/*
    Type Definition
*/

const char KEY[] = "key";
const char ID[] = "id";
const char OP[] = "op";
const char PUNC[] = "punc";
const char INT[] = "integer";
const char DOUBLE[] = "double";
const char CHAR[] = "char";
const char SCI[] = "sci";
const char STRING[] = "string";

int old_lines;
int num_lines = 0, num_chars = 0;
int first_token = 1;
int show_source = 1;
int show_token = 1;
char *strptr, *last_strptr;
char *buf;


%}

%x INVALID
%x SHORT_COMMENT
%x COMMENT

%%

#{SS}*pragma{SS}+source{SS}+off {PL; show_source = 0; }
#{SS}*pragma{SS}+source{SS}+on {PL; show_source = 1; }
#{SS}*pragma{SS}+token{SS}+off {PL; show_token = 0; }
#{SS}*pragma{SS}+token{SS}+on {PL; show_token = 1; }
#{SS}*pragma{SS}+(source|token){SS}+(on|off)[^{SS}(//)\n]+ {PL; /*printf("Invalid pragma ... %s\n ... ", yytext);*/ ERROR; }

"//"    { PL; BEGIN SHORT_COMMENT; }
"/*"    { PL;  BEGIN COMMENT; }
<COMMENT>\n { PL; END; }
<COMMENT>"*/"  { PL; BEGIN 0; }
<SHORT_COMMENT>\n  { PL; BEGIN 0; END;}
<SHORT_COMMENT>. { PL; }
<COMMENT>.  { PL; }

"void"   {PL; PT(KEY); return VOID; }
"int"   {PL; PT(KEY); return INTEGER; }
"double" {PL; PT(KEY); return FLOAT; }
"bool"   {PL; PT(KEY); return BOOL; }
"char"   {PL; PT(KEY); return CHARACTER; }
"null"   {PL; PT(KEY); }
"for"   {PL; PT(KEY); }
"while"   {PL; PT(KEY); }
"do"   {PL; PT(KEY); }
"if"   {PL; PT(KEY); }
"else"   {PL; PT(KEY); }
"switch"   {PL; PT(KEY); }
"return"   {PL; PT(KEY); }
"break"   {PL; PT(KEY); }
"continue"   {PL; PT(KEY); }
"const"   {PL; PT(KEY); return CONST; }
"true"   {PL; PT(KEY); return TRUE; }
"false"   {PL; PT(KEY); return FALSE; }
"struct"   {PL; PT(KEY); }
"case"   {PL; PT(KEY); }
"default"   {PL; PT(KEY); }

"clearerr"	{PL; PT(KEY);}
"fclose"	{PL; PT(KEY);}
"fdopen"	{PL; PT(KEY);}
"feof"	{PL; PT(KEY);}
"ferror"	{PL; PT(KEY);}
"fflush"	{PL; PT(KEY);}
"fgetc"	{PL; PT(KEY);}
"fgetpos"	{PL; PT(KEY);}
"fgets"	{PL; PT(KEY);}
"fileno"	{PL; PT(KEY);}
"fopen"	{PL; PT(KEY);}
"fprintf"	{PL; PT(KEY);}
"fpurge"	{PL; PT(KEY);}
"fputc"	{PL; PT(KEY);}
"fputs"	{PL; PT(KEY);}
"fread"	{PL; PT(KEY);}
"freopen"	{PL; PT(KEY);}
"fscanf"	{PL; PT(KEY);}
"fseek"	{PL; PT(KEY);}
"fsetpos"	{PL; PT(KEY);}
"ftell"	{PL; PT(KEY);}
"fwrite"	{PL; PT(KEY);}
"getc"	{PL; PT(KEY);}
"getchar"	{PL; PT(KEY);}
"gets"	{PL; PT(KEY);}
"getw"	{PL; PT(KEY);}
"mktemp"	{PL; PT(KEY);}
"perror"	{PL; PT(KEY);}
"printf"	{PL; PT(KEY);}
"putc"	{PL; PT(KEY);}
"putchar"	{PL; PT(KEY);}
"puts"	{PL; PT(KEY);}
"putw"	{PL; PT(KEY);}
"remove"	{PL; PT(KEY);}
"rewind"	{PL; PT(KEY);}
"scanf"	{PL; PT(KEY);}
"setbuf"	{PL; PT(KEY);}
"setbuffer"	{PL; PT(KEY);}
"setlinebuf"	{PL; PT(KEY);}
"setvbuf"	{PL; PT(KEY);}
"sprintf"	{PL; PT(KEY);}
"sscanf"	{PL; PT(KEY);}
"strerror"	{PL; PT(KEY);}
"sys_errlist"	{PL; PT(KEY);}
"sys_nerr"	{PL; PT(KEY);}
"tempnam"	{PL; PT(KEY);}
"tmpfile"	{PL; PT(KEY);}
"tmpnam"	{PL; PT(KEY);}
"ungetc"	{PL; PT(KEY);}
"vfprintf"	{PL; PT(KEY);}
"vfscanf"	{PL; PT(KEY);}
"vprintf"	{PL; PT(KEY);}
"vscanf"	{PL; PT(KEY);}
"vsprintf"	{PL; PT(KEY);}
"vsscanf"	{PL; PT(KEY);}


"+" { PL; PT(OP); return '+'; }
"-" { PL; PT(OP); return '-'; }
"*" { PL; PT(OP); return '*'; }
"/" { PL; PT(OP); return '/'; }
"%" { PL; PT(OP); return '%'; }
"=" { PL; PT(OP); return  '='; }
"++" { PL; PT(OP); return ADD2; }
"--" { PL; PT(OP); return SUB2; }
"<" { PL; PT(OP); return  LT; }
"<=" { PL; PT(OP); return  LE; }
">" { PL; PT(OP); return  GT; }
">=" { PL; PT(OP); return  GE; }
"==" { PL; PT(OP); return  EQ; }
"!=" { PL; PT(OP); return  NE; }
"&&" { PL; PT(OP); return  LOGAND; }
"||" { PL; PT(OP); return  LOGOR; }
"!" { PL; PT(OP); return  LOGNOT; }
"&" { PL; PT(OP); return  BITAND; }

[a-zA-Z_][0-9a-zA-Z_]*    {PL; PT(ID); return IDENT;}

"[" { PL; PT(PUNC); return '['; }
"]" { PL; PT(PUNC); return ']'; }
"(" { PL; PT(PUNC); return '('; }
")" { PL; PT(PUNC); return ')'; }
"{" { PL; PT(PUNC); return '{'; }
"}" { PL; PT(PUNC); return '}'; }
":" { PL; PT(PUNC); return ':'; }
";" { PL; PT(PUNC); return ';'; }
"," { PL; PT(PUNC); return ','; }
"." { PL; PT(PUNC); return '.'; }

(([0-9]*)|{DB})[eE][+-]?[0-9]+  {PL; PT(SCI); return NUM_FLOAT;}
(([0-9]*)|{DB})[eE][+-]?[[:alnum:]_\.]* {PL; /* printf("Invalid science notation ... %s ... \n", yytext); */ ERROR; }
{DB}  {PL; PT(DOUBLE); return NUM_FLOAT;}
[0-9]+\.([[:alnum:]_\.]*) {PL; /* printf("Invalid const float .... %s ... \n", yytext); */ ERROR; }
([1-9][0-9]*)|(0) {PL; PT(INT); return NUM_INT;}
([1-9]+[[:alnum:]_]*)|(0[[:alnum:]_]+)  {PL; /* printf("Invalid constant integer ... %s ... \n", yytext);*/ ERROR; }


(\"{CH}*\")  {
    PL;
    char *s = NULL, *freePtr;
    s = (char *)malloc(strlen(yytext) + 5);
    strcpy(s, yytext);
    freePtr = s++;
    s[strlen(s) - 1] = '\0';
    if (show_token)
        printf("#string:%s\n", s);
    
    if (freePtr)
        free(freePtr);

    return CONST_STR;
}

\'{CH}\'  {PL; PT(CHAR); return CONST_CHAR;}
[\ \t]* {PL; }
\n  {PL;  END;}
. { PL; ERROR;}
%%

