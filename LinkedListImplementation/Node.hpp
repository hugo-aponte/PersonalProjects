/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file holds the Node class, its private members, and      |
|               its public members/functions. Node stores a Data object       |
|               and next pointer used by the List class                       |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef NODE_HPP
#define NODE_HPP
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

template <class DATATYPE>
class Node
{
    private:
        DATATYPE data;
        Node* next;    
    public: 
    Node()
    {
        next = nullptr;
    }
    Node(DATATYPE data)
    {
        this->data = data; 
        next = nullptr;
    }
    ~Node()
    {}
    
    // getters
    DATATYPE getData();
    Node* getNext();

    // setters
    void setData(DATATYPE d);
    void setNext(Node* n);


};

#endif