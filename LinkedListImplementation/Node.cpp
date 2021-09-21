/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file holds all function definitions pertaining to        |
|               the class Node.                                               |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Node.hpp"
#include "Data.hpp"

// getters
template <typename DATATYPE>
DATATYPE Node<DATATYPE>::getData()
{
    return this->data;
}

template <typename DATATYPE>
Node<DATATYPE>* Node<DATATYPE>::getNext()
{
    return next;
}

// setters
template <typename DATATYPE>
void Node<DATATYPE>::setData(DATATYPE d)
{
    data = d;
}

template <typename DATATYPE>
void Node<DATATYPE>::setNext(Node* n)
{
    next = n;
}

template class Node<Data>;