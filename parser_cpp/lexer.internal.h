#ifndef LEXER_INTERNAL_H
#define LEXER_INTERNAL_H

#include "parser.h"
// parser.h is needed for "yy::parser::symbol_type" in this file.

class Lexer: public yyFlexLexer {
public:
	Lexer(std::istream *in = nullptr, std::ostream *out = nullptr): yyFlexLexer(in, out) {}
	virtual ~Lexer() {}
	virtual yy::parser::symbol_type get_next_token();
};

#endif
