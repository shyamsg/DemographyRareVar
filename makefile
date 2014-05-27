CPPVERSION:=$(shell	expr `g++ -dumpversion | cut -f1-2 -d.` \>= 4.4)
OS:=$(shell	uname)
ifeq	(${CPPVERSION}, 1)
	CPP=g++
else
	CPP=g++47
endif
ifeq	(${OS}, Darwin)
	LIBS=-I /Users/shyamg/packages/tclap-1.2.1/include/
else
	LIBS=-I /home/shyamg/packages/tclap-1.2.1/include/
endif

CXXFLAGS=-std=c++11 -g -D__DEBUG__
LDFLAGS=-O3

all:	tester
code/newickTreeNode.o:	code/newickTreeNode.h code/newickTreeNode.cpp
	${CPP}	${CXXFLAGS} ${LIBS} -o code/newickTreeNode.o -c code/newickTreeNode.cpp
code/ARG.o:	code/ARG.h code/ARG.cpp code/newickTreeNode.h
	${CPP}	${CXXFLAGS} ${LIBS} -o code/ARG.o -c code/ARG.cpp
code/siteStat.o:	code/siteStat.h code/siteStat.cpp
	${CPP}	${CXXFLAGS} ${LIBS} -o code/siteStat.o -c code/siteStat.cpp
code/argHelper.o:	code/argHelper.h code/argHelper.cpp
	${CPP}	${CXXFLAGS} ${LIBS} -o code/argHelper.o -c code/argHelper.cpp
code/argStatMiner.o:	code/argStatMiner.h code/argStatMiner.cpp code/ARG.h code/siteStat.h code/argHelper.h
	${CPP}	${CXXFLAGS} ${LIBS} -o code/argStatMiner.o -c code/argStatMiner.cpp
code/main.o:	code/ARG.h code/newickTreeNode.h code/argHelper.h code/siteStat.h code/argStatMiner.h code/main.cpp
	${CPP}	${CXXFLAGS} ${LIBS} -o code/main.o -c code/main.cpp

tester:	code/newickTreeNode.o code/ARG.o code/siteStat.o code/argHelper.o code/argStatMiner.o code/main.o
	${CPP}	${LDFLAGS} -o tester code/main.o code/ARG.o code/newickTreeNode.o code/argHelper.o code/siteStat.o code/argStatMiner.o

clean:
	rm	-f code/*.o tester
