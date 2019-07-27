%{
// Prologue section is placed after the "code top" section.
%}

%code requires {
// "code requires" section is placed at the beginning of parser.h.
#include "parse_tree.h" // This is needed by parser.h.
class Lexer; // This is needed by parser.h.
}

%code provides {
// "code provides" section is placed at the end of parser.h.
}

%code top {
// "code top" section is placed at the beginning of parser.cpp.
}

%code {
// "code" section is placed at the beginning of parser.cpp after including parser.h.
#include "lexer.h" // This is to provide the Lexer class used in the following function.
static yy::parser::symbol_type yylex(Lexer &lexer) { // This is Bison's interface to the lexer.
    return lexer.get_next_token(); // Call our lexer.
}
}

%require "3.2"
%language "c++"

%output  "parser.cpp"
%defines "parser.h"

%define api.value.type variant
%define api.token.constructor
%define parse.assert
%define api.value.automove

%lex-param { Lexer &lexer }
%parse-param { std::unique_ptr<Sum> &sum }
%parse-param { Lexer &lexer }

%token TOKEN_END 0 "end of file"
%token TOKEN_ADD             "+"
%token TOKEN_SUB             "-"
%token TOKEN_MUL             "*"
%token TOKEN_DIV             "/"
%token TOKEN_LBR             "("
%token TOKEN_RBR             ")"
%token <double> TOKEN_NUMBER "number"

%type <std::unique_ptr<Sum>> expression
%type <std::unique_ptr<Sum>> sum
%type <std::unique_ptr<Product>> product
%type <std::unique_ptr<Factor>> factor

%%

expression
    : sum { sum = $1; }
    ;

sum
    : sum "+" product { $$ = std::make_unique<Sum>($1, false, $3); }
    | sum "-" product { $$ = std::make_unique<Sum>($1, true, $3); }
    | "+" product     { $$ = std::make_unique<Sum>(nullptr, false, $2); }
    | "-" product     { $$ = std::make_unique<Sum>(nullptr, true, $2); }
    | product         { $$ = std::make_unique<Sum>(nullptr, false, $1); }
    ;

product
    : product "*" factor { $$ = std::make_unique<Product>($1, false, $3); }
    | product "/" factor { $$ = std::make_unique<Product>($1, true, $3); }
    | factor             { $$ = std::make_unique<Product>(nullptr, false, $1); }
    ;

factor
    : "number"    { $$ = std::make_unique<Factor>($1); }
    | "(" sum ")" { $$ = std::make_unique<Factor>($2); }
    ;

%%

void yy::parser::error(const std::string &message) {
    std::cerr << "Parser: " << message << std::endl;
}
