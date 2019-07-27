#ifndef LEXER_H
#define LEXER_H

#define yyFlexLexer yyFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer

// FlexLexer.h cannot be included more than once with the same definition of the macro "yyFlexLexer".
// In lexer.cpp, it is already included before the code from the definition section of lexer.l.
// So in the definition section of lexer.l, we should not include it and only need to include lexer.internal.h.

// In all other circumstances, FlexLexer.h is required before lexer.internal.h because the latter depends on it.
// This is the purpose of this file.

#include "lexer.internal.h"

#endif
