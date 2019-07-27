#include "parsing_driver.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage: %s expression\n", argv[0]);
		return -1;
	}
	struct Sum *expression = parse(argv[1]);
	if (expression == NULL)
		return -1;
	print_sum(expression);
	printf("\n");
	printf("%g\n", evaluate_sum(expression));
	delete_sum(expression);
	return 0;
}
