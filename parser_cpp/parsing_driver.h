#ifndef PARSING_DRIVER_H
#define PARSING_DRIVER_H

#include "lexer.h"

class Driver
{
public:
	Driver(std::istream &is);
	~Driver();
	int parse();
	void print();
	double evaluate();

private:
	std::unique_ptr<Sum> expression;
	Lexer lexer;
	yy::parser parser;
};

#endif
