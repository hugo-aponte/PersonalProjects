all: prog

prog: main.o InventoryRecord.o InventoryRecord.h pa4.h RedBlackNode.h RedBlackTree.h
	g++ -Wall -std=c++11 -g main.o InventoryRecord.o -o prog
	
main o: main.cpp pa4.h InventoryRecord.h RedBlackNode.h RedBlackTree.h 	
	g++ -Wall -std=c++11 -c main.cpp
	
InventoryRecord.o: InventoryRecord.cpp pa4.h InventoryRecord.h RedBlackNode.h RedBlackTree.h
	g++ -Wall -std=c++11 -c InventoryRecord.cpp
		
clean: 
	rm -rf *o prog
