%{
// Prologue section is placed after the "code top" section.
%}

%code requires {
// "code requires" section is placed at the beginning of parser.h.
#include "parse_tree.h" // This is needed by parser.h.
typedef void *yyscan_t; // This is needed by parser.h.
}

%code provides {
// "code provides" section is placed at the end of parser.h.
}

%code top {
// "code top" section is placed at the beginning of parser.c.
}

%code {
// "code" section is placed at the beginning of parser.c after including parser.h.
#include "lexer.h" // This is to provide Function "yylex".
#include <stdio.h>
void yyerror(struct Sum **output, yyscan_t scanner, const char *msg) {
    fprintf(stderr, "Parser: %s\n", msg);
}
}

%union {
    double value;
    struct Factor *factor;
    struct Product *product;
    struct Sum *sum;
}

%output  "parser.c"
%defines "parser.h"

%define api.pure

%lex-param   { yyscan_t scan_info }
%parse-param { struct Sum **sum }
%parse-param { yyscan_t scan_info }

%token TOKEN_ADD            "+"
%token TOKEN_SUB            "-"
%token TOKEN_MUL            "*"
%token TOKEN_DIV            "/"
%token TOKEN_LBR            "("
%token TOKEN_RBR            ")"
%token <value> TOKEN_NUMBER "number"

%type <sum> expression
%type <sum> sum
%type <product> product
%type <factor> factor

%destructor { delete_sum($$);     } sum
%destructor { delete_product($$); } product
%destructor { delete_factor($$);  } factor

%%

expression
    : sum { *sum = $1; }
    ;

sum
    : sum "+" product { $$ = new_sum($1, false, $3); }
    | sum "-" product { $$ = new_sum($1, true, $3); }
    | "+" product     { $$ = new_sum(NULL, false, $2); }
    | "-" product     { $$ = new_sum(NULL, true, $2); }
    | product         { $$ = new_sum(NULL, false, $1); }
    ;

product
    : product "*" factor { $$ = new_product($1, false, $3); }
    | product "/" factor { $$ = new_product($1, true, $3); }
    | factor             { $$ = new_product(NULL, false, $1); }
    ;

factor
    : "number"    { $$ = new_number_factor($1); }
    | "(" sum ")" { $$ = new_bracketed_factor($2); }
    ;

%%
