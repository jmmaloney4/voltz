%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;

void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
	double num;
    const char* str;
    token tok;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token <num> NUM
%token <str> STRING
%token <str> IDENTIFIER
%token <str> LINE_COMMENT BLOCK_COMMENT LINE_DOC_COMMENT BLOCK_DOC_COMMENT
%token <tok> NEWLINE TAB SPACE
%token <tok> OPEN_PAREN CLOSE_PAREN OPEN_BRACE CLOSE_BRACE OPEN_BRACKET CLOSE_BRACKET
%token <tok> SEMICOLON COLON DOUBLE_COLON
%token <tok> MODULE IMPORT AS
%token <tok> CLASS PROTOCOL
%token <tok> FUNC MTHD

%%

program: {stmt} | stmt

eol: NEWLINE SEMICOLON

whitespace: {SPACE} | {TAB} | {NEWLINE} | {whitespace} ;

type: ( IDENTIFIER | type ) DOUBLE_COLON (IDENTIFIER | type)

stmt: mod_def_stmt | mod_stmt | import_stmt

mod_def_stmt: MODULE whitespace IDENIFIER whitespace eol ;

mod_stmt: MODULE whitespace OPEN_BRACE {stmt} CLOSE_BRACE eol ;

import_stmt: IMPORT whitespace type eol ;

%%

int main(int, char**) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("demo.vz", "r");
	// make sure it is valid:
	if (!myfile) {
		cout << "I can't open demo.vz!" << endl;
		return -1;
	}
	// set flex to read from it instead of defaulting to STDIN:
	yyin = myfile;

	// parse through the input until there is no more:
	do {
		yyparse();
	} while (!feof(yyin));

}

void yyerror(const char *s) {
	cout << "EEK, parse error!  Message: " << s << endl;
	// might as well halt now:
	exit(-1);
}
