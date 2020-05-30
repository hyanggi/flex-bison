#include "parsing_driver.h"
#include "parser.h"
#include "lexer.h"

#include <stdio.h>

struct Sum *parse(const char *str)
{
	yyscan_t scan_info;
	if (yylex_init(&scan_info) != 0) { // Flex reentrant API
		fprintf(stderr, "yylex_init failed.\n");
		return NULL;
	}
	YY_BUFFER_STATE in_buffer = yy_scan_string(str, scan_info); // Flex multi-input-buffer API (reentrant version)

	struct Sum *expression;
	if (yyparse(&expression, scan_info) != 0) { // Bison API
		fprintf(stderr, "yyparse failed.\n");
		expression = NULL;
	}

	yy_delete_buffer(in_buffer, scan_info); // Flex multi-input-buffer API (reentrant version)
	if (yylex_destroy(scan_info) != 0) // Flex reentrant API
		fprintf(stderr, "yylex_destroy failed.\n");

	return expression;
}
