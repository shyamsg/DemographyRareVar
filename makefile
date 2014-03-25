
CXXFLAGS=--std=c++11
LDFLAGS=-O3

all: tester
code/newickTreeNode.o: code/newickTreeNode.h code/newickTreeNode.cpp
	g++ ${CXXFLAGS} -o code/newickTreeNode.o -c code/newickTreeNode.cpp
code/ARG.o: code/ARG.h code/ARG.cpp code/newickTreeNode.h
	g++ ${CXXFLAGS} -o code/ARG.o -c code/ARG.cpp
code/main.o: code/ARG.h code/newickTreeNode.h code/main.cpp
	g++ ${CXXFLAGS} -o code/main.o -c code/main.cpp

tester: code/newickTreeNode.o code/ARG.o code/main.o
	g++ ${LDFLAGS} -o tester code/main.o code/ARG.o code/newickTreeNode.o

clean:
	rm -f code/*.o tester
