CPPVERSION:=$(shell expr `g++ -dumpversion | cut -f1-2 -d.` \>= 4.4)
ifeq (${CPPVERSION}, 1)
	CPP=g++
else
	CPP=g++47
endif

CXXFLAGS=-std=c++11
LDFLAGS=-O3
LIBS=-I /home/shyamg/packages/tclap-1.2.1/include/

all: tester
code/newickTreeNode.o: code/newickTreeNode.h code/newickTreeNode.cpp
	${CPP} ${CXXFLAGS} ${LIBS} -o code/newickTreeNode.o -c code/newickTreeNode.cpp
code/ARG.o: code/ARG.h code/ARG.cpp code/newickTreeNode.h
	${CPP} ${CXXFLAGS} ${LIBS} -o code/ARG.o -c code/ARG.cpp
code/main.o: code/ARG.h code/newickTreeNode.h code/main.cpp
	${CPP} ${CXXFLAGS} ${LIBS} -o code/main.o -c code/main.cpp

tester: code/newickTreeNode.o code/ARG.o code/main.o
	${CPP} ${LDFLAGS} -o tester code/main.o code/ARG.o code/newickTreeNode.o

clean:
	rm -f code/*.o tester
