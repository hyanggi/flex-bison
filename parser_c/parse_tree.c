#include "parse_tree.h"
#include <stdio.h>
#include <stdlib.h>

struct Factor *new_number_factor(double number)
{
	struct Factor *factor = (struct Factor *)malloc(sizeof(struct Factor));
	factor->is_number = true;
	factor->number = number;
	return factor;
}

struct Factor *new_bracketed_factor(struct Sum *bracketed)
{
	struct Factor *factor = (struct Factor *)malloc(sizeof(struct Factor));
	factor->is_number = false;
	factor->bracketed = bracketed;
	return factor;
}

void print_factor(const struct Factor *factor)
{
	if (factor->is_number)
		printf("%g", factor->number);
	else {
		printf("(");
		print_sum(factor->bracketed);
		printf(")");
	}
}

double evaluate_factor(const struct Factor *factor)
{
	if (factor->is_number)
		return factor->number;
	else
		return evaluate_sum(factor->bracketed);
}

void delete_factor(struct Factor *factor)
{
	if (!factor->is_number)
		delete_sum(factor->bracketed);
	free(factor);
}

struct Product *new_product(struct Product *left, bool div, struct Factor *right)
{
	struct Product *product = (struct Product *)malloc(sizeof(struct Product));
	product->left = left;
	product->div = div;
	product->right = right;
	return product;
}

void print_product(const struct Product *product)
{
	if (product->left != NULL) {
		print_product(product->left);
		if (! product->div)
			printf(" * ");
		else
			printf(" / ");
	}
	else if (product->div)
		printf("1 / ");
	print_factor(product->right);
}

double evaluate_product(const struct Product *product)
{
	double pre_product = 1.0;
	if (product->left != NULL)
		pre_product = evaluate_product(product->left);
	if (product->div)
		return pre_product / evaluate_factor(product->right);
	else
		return pre_product * evaluate_factor(product->right);
}

void delete_product(struct Product *product)
{
	if (product->left != NULL)
		delete_product(product->left);
	delete_factor(product->right);
	free(product);
}

struct Sum *new_sum(struct Sum *left, bool sub, struct Product *right)
{
	struct Sum *sum = (struct Sum *)malloc(sizeof(struct Sum));
	sum->left = left;
	sum->sub = sub;
	sum->right = right;
	return sum;
}

void print_sum(const struct Sum *sum)
{
	if (sum->left != NULL) {
		print_sum(sum->left);
		if (! sum->sub)
			printf(" + ");
		else
			printf(" - ");
	}
	else if (sum->sub)
		printf("- ");
	print_product(sum->right);
}

double evaluate_sum(const struct Sum *sum)
{
	double pre_sum = 0.0;
	if (sum->left != NULL)
		pre_sum = evaluate_sum(sum->left);
	if (sum->sub)
		return pre_sum - evaluate_product(sum->right);
	else
		return pre_sum + evaluate_product(sum->right);
}

void delete_sum(struct Sum *sum)
{
	if (sum->left != NULL)
		delete_sum(sum->left);
	delete_product(sum->right);
	free(sum);
}
