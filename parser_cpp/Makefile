CXX = g++
CXXFLAGS = -g -Wall -pedantic -std=c++17

SRC = lexer.cpp parser.cpp parse_tree.cpp parsing_driver.cpp

test: $(SRC) $(SRC:%.cpp=%.h) lexer.internal.h main.cpp
	$(CXX) $(CXXFLAGS) $(filter %.cpp,$^) -o $@

lexer.cpp: lexer.l
	flex lexer.l

parser.cpp parser.h: parser.y
	bison parser.y

clean:
	$(RM) test lexer.cpp parser.cpp parser.h location.hh position.hh stack.hh
