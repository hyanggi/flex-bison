#include "parse_tree.h"
#include <cstdio>

// Note that in C++:
// Even if a variable is an rvalue reference, the expression consisting of its name is an lvalue expression.
// Therefore to make it an rvalue reference we still need std::move.

Factor::Factor(double number): factor(number)
{}

Factor::Factor(std::unique_ptr<Sum> &&bracketed): factor(std::move(bracketed))
{}

Factor::~Factor()
{}

void Factor::print() const
{
	if (std::holds_alternative<double>(factor))
		std::printf("%g", std::get<double>(factor));
	else {
		std::printf("(");
		std::get<std::unique_ptr<Sum>>(factor)->print();
		std::printf(")");
	}
}

double Factor::evaluate() const
{
	if (std::holds_alternative<double>(factor))
		return std::get<double>(factor);
	else
		return std::get<std::unique_ptr<Sum>>(factor)->evaluate();
}

Product::Product(std::unique_ptr<Product> &&left, bool div, std::unique_ptr<Factor> &&right): left(std::move(left)), div(div), right(std::move(right))
{}

Product::~Product()
{}

void Product::print() const
{
	if (left != nullptr) {
		left->print();
		if (!div)
			std::printf(" * ");
		else
			std::printf(" / ");
	}
	else if (div)
		std::printf("1 / ");
	right->print();
}

double Product::evaluate() const
{
	double pre_product = 1.0;
	if (left != nullptr)
		pre_product = left->evaluate();
	if (div)
		return pre_product / right->evaluate();
	else
		return pre_product * right->evaluate();
}

Sum::Sum(std::unique_ptr<Sum> &&left, bool sub, std::unique_ptr<Product> &&right): left(std::move(left)), sub(sub), right(std::move(right))
{}

Sum::~Sum()
{}

void Sum::print() const
{
	if (left != nullptr) {
		left->print();
		if (!sub)
			std::printf(" + ");
		else
			std::printf(" - ");
	}
	else if (sub)
		std::printf("- ");
	right->print();
}

double Sum::evaluate() const
{
	double pre_sum = 0.0;
	if (left != nullptr)
		pre_sum = left->evaluate();
	if (sub)
		return pre_sum - right->evaluate();
	else
		return pre_sum + right->evaluate();
}
