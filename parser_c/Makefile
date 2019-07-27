CC = gcc
CFLAGS = -g -pedantic -std=c17

SRC = lexer.c parser.c parse_tree.c parsing_driver.c

test: $(SRC) $(SRC:%.c=%.h) main.c
	$(CC) $(CFLAGS) $(filter %.c,$^) -o $@

lexer.c lexer.h: lexer.l
	flex lexer.l

parser.c parser.h: parser.y
	bison parser.y

clean:
	$(RM) lexer.c lexer.h parser.c parser.h test
