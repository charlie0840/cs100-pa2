# A simple makefile for CSE 100 P2

#use g++ for everything
CC= g++

# include debugging symbols in object files,
# and enable all warnings
CXXFLAGS= -std=c++11 -g -Wall -fpermissive

#include debugging symbols in executable
LDFLAGS= -g

benchtree: benchtree.o countint.o

benchtree.o: RST.hpp BST.hpp BSTNode.hpp BSTIterator.hpp

countint.o: countint.hpp

test_RST.o: RST.hpp BST.hpp BSTNode.hpp BSTIterator.hpp

tester: test_RST.o countint.o
	g++ -std=c++11 -g -Wall -o tester test_RST.o countint.o

all: benchtree tester

clean:
	rm -f benchtree tester *.o
