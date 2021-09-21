all: prog

prog: main.o CancerData.o pa3.o pa3.h AVLNode.h AVLTree.h CancerData.h
	g++ -Wall -std=c++11 -g main.o CancerData.o pa3.o -o prog
	
main.o: main.cpp pa3.h AVLNode.h AVLTree.h CancerData.h
	g++ -Wall -std=c++11 -c main.cpp
	
CancerData.o: CancerData.cpp pa3.h AVLNode.h AVLTree.h CancerData.h
	g++ -Wall -std=c++11 -c CancerData.cpp

pa3.o: pa3.cpp pa3.h AVLNode.h AVLTree.h CancerData.h
	g++ -Wall -std=c++11 -c pa3.cpp
	
clean: 
	rm -rf *o prog
	
	
