/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |	
|	CptS 223;                 											 	  |
|	PA4																		  |
|	10/30/20																  |
|                                                                             |
| Description: The purpose of this file is to define and include all          |
|              necessary preprocessor directives used by all other .h         |
|              functions.                                				      |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef PA4_H
#define PA4_H
#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "InventoryRecord.h"
#include "RedBlackNode.h"
#include "RedBlackTree.h"

template <class T>
void readFile(RedBlackNode<T>* tree, std::fstream& iFile);

void menu(int &option); // menu with user selected options 

void menu(); // default test menu

template <class T>
RedBlackNode<T>* promptItem(int &ID, std::string &type, int &numItems);

template <class T>
void addItem(RedBlackTree<T>* tree, RedBlackNode<T>* node);

template <class T>
void removeItem(RedBlackTree<T>* tree);

template <class T>
void updateItem(RedBlackTree<T>* tree);

#endif