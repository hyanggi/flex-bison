#include "parsing_driver.h"
#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, "Usage %s expression\n", argv[0]);
		return -1;
	}
	std::istringstream is(argv[1]);
	Driver driver(is);
	if (driver.parse() != 0)
		return -1;
	driver.print();
	std::cout << std::endl;
	std::cout << driver.evaluate() << std::endl;
	return 0;
}
