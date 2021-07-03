CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-parameter
CPPFLAGS += -I include

all : bin/c_compiler

common/src/parser.tab.cpp common/src/parser.tab.hpp : common/src/parser.y
	bison -v -d common/src/parser.y -o common/src/parser.tab.cpp

common/src/lexer.yy.cpp : common/src/lexer.flex common/src/parser.tab.hpp
	flex -o common/src/lexer.yy.cpp  common/src/lexer.flex

bin/c_compiler : Python_Translator/py_translator/python_interpreter.o Python_Translator/py_translator/python_interpreter_Translate_Statement_Functions.o Python_Translator/py_translator/IndentationAdder.o  main.o Compiler/compiler.o common/src/parser.tab.o common/src/lexer.yy.o common/src/parser.tab.o
	mkdir -p bin
	g++ $(CPPFLAGS) $^ -o $@


clean :
	rm common/src/*.tab.cpp
	rm common/src/*.yy.cpp
	rm common/src/*.o
	rm bin/*
	rm tmp/*
	rmdir tmp
