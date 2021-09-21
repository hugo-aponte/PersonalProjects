/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file holds the List class, its private members, and      |
|                its public members/functions. List uses Node and Data to     |
|                populate a linked list                                       |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

template <class NODETYPE>
class List
{
private:
    NODETYPE* head_ptr;
public:
    List()
    {
        head_ptr = nullptr;
    }

    // setter:
    void setHead(NODETYPE* h);
    // getter:
    NODETYPE* getHead();

    void test();
    void insertCommand(string command, string description);
    int displayCommand(int runCount, int* userSelection, int* correctAnswer); // runCount will be subtracted from the randomizing call in display to represent the decreasing amount of commands as the user is tested on them
        // pointer for userSelection will be sent back to the main play() function 
        // pointer for correct answer will be compared back in play() function
    void testPrint(); 
    void remove(string command);
    void display3Descriptions(int correctPos, int runCount, int* correctAnswer);
    bool compareUserAnswer(int* userSelection, int* correctAnswer);
    bool isEmpty();
    bool findCommand(string command);

};

#endif