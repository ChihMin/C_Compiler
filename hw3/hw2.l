DB  (([0-9]+\.[0-9]*)|(\.[0-9]+)|([0-9]+\.))
OP  ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"<"|"<="|">"|">="|"=="|"!="|"="|"&&"|"||"|"!"|"&")
PU  ("["|"]"|"("|")"|"{"|"}"|":"|";"|","|".")
SS  (([\t\ ])|("/*"(.)*"*/"))
CH  ((\\\')|(\\\")|(\\\?)|(\\\\)|(\\t)|(\\n)|([^\'\\\n]))

%{

#include <stdio.h>
#include <string.h>
#include "y.tab.h"
#include "literal.h"
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
"for"   {PL; PT(KEY); return FOR; }
"while"   {PL; PT(KEY); return WHILE; }
"do"   {PL; PT(KEY); return DO; }
"if"   {PL; PT(KEY); return IF; }
"else"   {PL; PT(KEY); return ELSE; }
"switch"   {PL; PT(KEY); return SWITCH; }
"return"   {PL; PT(KEY); return RETURN;}
"break"   {PL; PT(KEY); return BREAK;}
"continue"   {PL; PT(KEY); return CONTINUE;}
"const"   {PL; PT(KEY); return CONST; }
"true"   {PL; PT(KEY); return TRUE; }
"false"   {PL; PT(KEY); return FALSE; }
"struct"   {PL; PT(KEY); }
"case"   {PL; PT(KEY); return CASE; }
"default"   {PL; PT(KEY); return DEFAULT; }

"clearerr"	{PL; PT(KEY); return IDENT;}
"fclose"	{PL; PT(KEY);return IDENT;}
"fdopen"	{PL; PT(KEY);return IDENT;}
"feof"	{PL; PT(KEY);return IDENT;}
"ferror"	{PL; PT(KEY);return IDENT;}
"fflush"	{PL; PT(KEY);return IDENT;}
"fgetc"	{PL; PT(KEY);return IDENT;}
"fgetpos"	{PL; PT(KEY);return IDENT;}
"fgets"	{PL; PT(KEY);return IDENT;}
"fileno"	{PL; PT(KEY);return IDENT;}
"fopen"	{PL; PT(KEY);return IDENT;}
"fprintf"	{PL; PT(KEY);return IDENT;}
"fpurge"	{PL; PT(KEY);return IDENT;}
"fputc"	{PL; PT(KEY);return IDENT;}
"fputs"	{PL; PT(KEY);return IDENT;}
"fread"	{PL; PT(KEY);return IDENT;}
"freopen"	{PL; PT(KEY);return IDENT;}
"fscanf"	{PL; PT(KEY);return IDENT;}
"fseek"	{PL; PT(KEY);return IDENT;}
"fsetpos"	{PL; PT(KEY);return IDENT;}
"ftell"	{PL; PT(KEY);return IDENT;}
"fwrite"	{PL; PT(KEY);return IDENT;}
"getc"	{PL; PT(KEY);return IDENT;}
"getchar"	{PL; PT(KEY);return IDENT;}
"gets"	{PL; PT(KEY);return IDENT;}
"getw"	{PL; PT(KEY);return IDENT;}
"mktemp"	{PL; PT(KEY);return IDENT;}
"perror"	{PL; PT(KEY);return IDENT;}
"printf"	{PL; PT(KEY);return IDENT;}
"putc"	{PL; PT(KEY);return IDENT;}
"putchar"	{PL; PT(KEY);return IDENT;}
"puts"	{PL; PT(KEY);return IDENT;}
"putw"	{PL; PT(KEY);return IDENT;}
"remove"	{PL; PT(KEY);return IDENT;}
"rewind"	{PL; PT(KEY);return IDENT;}
"scanf"	{PL; PT(KEY);return IDENT;}
"setbuf"	{PL; PT(KEY);return IDENT;}
"setbuffer"	{PL; PT(KEY);return IDENT;}
"setlinebuf"	{PL; PT(KEY);return IDENT;}
"setvbuf"	{PL; PT(KEY);return IDENT;}
"sprintf"	{PL; PT(KEY);return IDENT;}
"sscanf"	{PL; PT(KEY);return IDENT;}
"strerror"	{PL; PT(KEY);return IDENT;}
"sys_errlist"	{PL; PT(KEY);return IDENT;}
"sys_nerr"	{PL; PT(KEY);return IDENT;}
"tempnam"	{PL; PT(KEY);return IDENT;}
"tmpfile"	{PL; PT(KEY);return IDENT;}
"tmpnam"	{PL; PT(KEY);return IDENT;}
"ungetc"	{PL; PT(KEY);return IDENT;}
"vfprintf"	{PL; PT(KEY);return IDENT;}
"vfscanf"	{PL; PT(KEY);return IDENT;}
"vprintf"	{PL; PT(KEY);return IDENT;}
"vscanf"	{PL; PT(KEY);return IDENT;}
"vsprintf"	{PL; PT(KEY);return IDENT;}
"vsscanf"	{PL; PT(KEY);return IDENT;}

"delay" {PL; PT(ID); return DELAY;}; 
"digitalWrite" {PL; PT(ID); return WRITE;};
"HIGH" {PL; PT(ID); return HIGH; };
"LOW" {PL; PT(ID); return LOW; };

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

[a-zA-Z_][0-9a-zA-Z_]*  {
    PL; PT(ID); 
    yylval.str = (char *)malloc(strlen(yytext) + 5);
    strcpy(yylval.str, yytext);
    return IDENT;
}

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
([1-9][0-9]*)|(0) {
    PL; PT(INT); 
    yylval.ival = atoi(yytext); 
    return NUM_INT;
}
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
\r { }
. { PL; ERROR;}
%%

