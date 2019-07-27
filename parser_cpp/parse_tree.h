#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <memory>
#include <variant>

class Sum;

class Factor
{
public:
	Factor(double number);
	Factor(std::unique_ptr<Sum> &&bracketed);
	~Factor();
	void print() const;
	double evaluate() const;
private:
	std::variant<double, std::unique_ptr<Sum>> factor;
};

class Product
{
public:
	Product(std::unique_ptr<Product> &&left, bool div, std::unique_ptr<Factor> &&right);
	~Product();
	void print() const;
	double evaluate() const;
private:
	std::unique_ptr<Product> left;
	bool div;
	std::unique_ptr<Factor> right;
};

class Sum
{
public:
	Sum(std::unique_ptr<Sum> &&left, bool sub, std::unique_ptr<Product> &&right);
	~Sum();
	void print() const;
	double evaluate() const;
private:
	std::unique_ptr<Sum> left;
	bool sub;
	std::unique_ptr<Product> right;
};

#endif
