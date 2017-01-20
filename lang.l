%{
//**************************************
// lang.l
//
// Scanner definition file for CST 320 project
//
// Author: Garrett Fleischer
// garrett.fleischer@oit.edu
//
// Date:
//

#include "tokens.h"

#define DO_RETURN(a) return (a)
//#define DO_RETURN(a) return Return(a)
int Return(int val);
%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. */
int_num     [0-9]+
comment     "//".*$
ws          [ \t\n\r]

%%

    // token definitions go here
{int_num}   DO_RETURN(NUM);
"end"       DO_RETURN(END);
";"         DO_RETURN(';');
"("         DO_RETURN('(');
")"         DO_RETURN(')');
"["         DO_RETURN('[');
"]"         DO_RETURN(']');
"+"         DO_RETURN('+');
"-"         DO_RETURN('-');
"*"         DO_RETURN('*');
"/"         DO_RETURN('/');

    /* Others */
{ws}        {}
{comment}   {}
.           DO_RETURN(JUNK_TOKEN);


%%

// This function allows us to do extra processing on each token
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}

