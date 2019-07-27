#include "parsing_driver.h"

Driver::Driver(std::istream &is): expression(nullptr), lexer(&is), parser(expression, lexer)
{
}

Driver::~Driver()
{
}

int Driver::parse()
{
	return parser.parse();
}

void Driver::print()
{
	if (expression != nullptr)
		expression->print();
}

double Driver::evaluate()
{
	if (expression != nullptr)
		return expression->evaluate();
	else
		return 0.0;
}
