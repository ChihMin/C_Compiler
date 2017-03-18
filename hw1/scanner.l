%{

#include <stdio.h>
#include <string.h>
#define PL \
    if (first_token) { \
        strptr = yytext; \
        first_token = 0; \
    }

#define PT(type) \
    if (show_token) \
        printf("#%s:%s\n", type, yytext);

#define END \
    ++num_lines; \
    if (show_source) { \
        printf("%d:", num_lines); \
        do { \
            printf("%c", *strptr);  \
            strptr++; \
        } while (*strptr != '\n' && *strptr != '\0'); \
        if (*strptr == '\n') \
            printf("\n"); \
    } \
    first_token = 1;

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

int num_lines = 0, num_chars = 0;
int first_token = 1;
int show_source = 1;
int show_token = 1;
char *strptr;

%}

%x SOURCE
%x TOKEN
%x SHORT_COMMENT
%x COMMENT

%%

#pragma\ +source\ +off\ * {PL; show_source = 0; }
#pragma\ +source\ +on\ * {PL; show_source = 1; }
#pragma\ +token\ +off\ * {PL; show_token = 0; }
#pragma\ +token\ +on\ * {PL; show_token = 1; }

"//"    { PL; BEGIN SHORT_COMMENT; }
"/*"    { PL;  BEGIN COMMENT; }
<COMMENT>\n { PL; END; }
<COMMENT>"*/"  { PL; BEGIN 0; }
<SHORT_COMMENT>\n  { PL; BEGIN 0; END;}
<SHORT_COMMENT>. { PL; }
<COMMENT>.  { PL; }

"void"   {PL; PT(KEY); }
"int"   {PL; PT(KEY); }
"double" {PL; PT(KEY); }
"bool"   {PL; PT(KEY); }
"char"   {PL; PT(KEY); }
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
"const"   {PL; PT(KEY); }
"true"   {PL; PT(KEY); }
"false"   {PL; PT(KEY); }
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

[a-zA-Z_][0-9a-zA-Z]*    {PL; PT(ID);}

"+"   {PL; PT(OP); }
"-"   {PL; PT(OP); }
"*"   {PL; PT(OP); }
"/"   {PL; PT(OP); }
"%"   {PL; PT(OP); }
"++"   {PL; PT(OP); }
"--"   {PL; PT(OP); }
"<"   {PL; PT(OP); }
"<="   {PL; PT(OP); }
">"   {PL; PT(OP); }
">="   {PL; PT(OP); }
"=="   {PL; PT(OP); }
"!="   {PL; PT(OP); }
"="   {PL; PT(OP); }
"&&"   {PL; PT(OP); }
"||"   {PL; PT(OP); }
"!"   {PL; PT(OP); }
"&"   {PL; PT(OP); }

[\[\]\(\)\{\}:;,.]    {PL;  PT(PUNC);}

[0-9]+(\.[0-9]+)?[eE][+-]?[0-9]+  {PL; PT(SCI); } 
[0-9]+\.[0-9]+  {PL; PT(DOUBLE); }
[0-9]+  {PL; PT(INT);}

\".*\"  {
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
}

\'[a-zA-Z0-9\n\t]\'  {PL; PT(CHAR);}

\n  {PL;  END;}

. { PL; }
%%

int main(int argc, char *argv[]) {
    yylex();
    return 0;
}
