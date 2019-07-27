#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <stdbool.h>

struct Sum;

struct Factor
{
	bool is_number;
	union {
		double number;
		struct Sum *bracketed;
	};
};

struct Product
{
	struct Product *left;
	bool div;
	struct Factor *right;
};

struct Sum
{
	struct Sum *left;
	bool sub;
	struct Product *right;
};

struct Factor *new_number_factor(double number);
struct Factor *new_bracketed_factor(struct Sum *bracketed);
void print_factor(const struct Factor *factor);
double evaluate_factor(const struct Factor *factor);
void delete_factor(struct Factor *factor);

struct Product *new_product(struct Product *left, bool div, struct Factor *right);
void print_product(const struct Product *product);
double evaluate_product(const struct Product *product);
void delete_product(struct Product *product);

struct Sum *new_sum(struct Sum *left, bool sub, struct Product *right);
void print_sum(const struct Sum *sum);
double evaluate_sum(const struct Sum *sum);
void delete_sum(struct Sum *sum);

#endif
