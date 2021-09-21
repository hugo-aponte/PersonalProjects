/*******************************************************************************************
* Programmer: Hugo Aponte																   *
* Class: CptS 223, Fall, 2020;              											   *
* Programming Assignment: PA3															   *
* Date: October 9th, 2020																   *					
* Description: This program reads in cancer data from various files: both men and women,   *
*               men alone, and women alone. The goal is to create three AVL trees that     *
*               store country cancer rates for the corresponding file. This AVL tree       *
*               should be following the AVL properties. We will also use the tree to       * 
*               find the max and min cancer rates for each file.                           *
*                                                                                          *
*               This individual file holds the function prototypes used by main to         *
*               create multiple AVLTrees corresponding to specific .csv files              *
********************************************************************************************/

#ifndef PA3_H
#define PA3_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iomanip>
#include <sstream>
#include "CancerData.h"
#include "AVLNode.h"
#include "AVLTree.h"


void testBoth();
void testWomen();
void testMen();
void testMaxMin(std::string m);


template <class T>
void readFile(AVLTree<T>* test, std::fstream& iFile);


#endif