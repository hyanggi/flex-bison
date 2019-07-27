%{

#include "lexer.internal.h"

// Change the definition of the "yylex" function, which is originally "int ourLexer::yylex()" (see comments below).
#undef YY_DECL
#define YY_DECL yy::parser::symbol_type Lexer::get_next_token()

// This is necessary to override the default "yyterminate" returning integer 0.
#define yyterminate() return yy::parser::make_TOKEN_END();
// Default: #define yyterminate() return YY_NULL
// Default: #define YY_NULL 0

// "YY_USER_ACTION" is executed after each token is matched and before its rule is executed.
#define YY_USER_ACTION //std::cout << yytext << " " << yyleng << std::endl;

%}

/* options specifying file names */
%option outfile="lexer.cpp"

/* debugging options */
%option warn nodefault

/* options affecting scanner behavior */
%option never-interactive noyywrap

/* code-level and API options */
%option nounistd c++ yyclass="ourLexer"
/* The "yyclass" option is to tell Flex that we have derived "ourLexer" as a subclass of "yyFlexLexer".
   It has two effects:
   1. It defines the macro YY_DECL as "int ourLexer::yylex()", overriding the default "int yyFlexLexer::yylex()".
   2. It defines the function "int yyFlexLexer::yylex()" as a function that emits a runtime error.
   Because we changed the definition of YY_DECL again (see comments above), the name "ourLexer" actually has no use here.
*/


number      [0-9]+(\.[0-9]+)?
ws          [ \r\n\t]+

%%

{ws}            { continue; }
"+"             { return yy::parser::make_TOKEN_ADD(); }
"-"             { return yy::parser::make_TOKEN_SUB(); }
"*"             { return yy::parser::make_TOKEN_MUL(); }
"/"             { return yy::parser::make_TOKEN_DIV(); }
"("             { return yy::parser::make_TOKEN_LBR(); }
")"             { return yy::parser::make_TOKEN_RBR(); }
{number}        { return yy::parser::make_TOKEN_NUMBER(std::atof(yytext)); }
.               {
                  std::fprintf(stderr, "Lexer: unexpected character %s\n", yytext);
                  throw yy::parser::syntax_error("unexpected character " + std::string(yytext, yyleng));
                }

%%
