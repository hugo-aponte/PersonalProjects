/*******************************************************************************************
* Programmer: Hugo Aponte																   *
*                    Fall, 2020;              											   *
*                           PA3															   *
* Date: October 9th, 2020																   *					
* Description: This program reads in cancer data from various files: both men and women,   *
*               men alone, and women alone. The goal is to create three AVL trees that     *
*               store country cancer rates for the corresponding file. This AVL tree       *
*               should be following the AVL properties. We will also use the tree to       * 
*               find the max and min cancer rates for each file.                           *
*                                                                                          *
*               This individual file holds the function prototypes and definitions         *
*               necessary for the AVLTree to build an AVLNode. Thus, this files creates    *
*               the templated class AVLNode which holds CancerData class specific data     *
********************************************************************************************/

#ifndef AVLNODE_H
#define AVLNODE_H

#include "pa3.h"


template <class T>
class AVLNode
{
private:
    T data;
    AVLNode<T>* left;
    AVLNode<T>* right;
    int height;
public:
    AVLNode(T data);
    ~AVLNode();

    void setData(T data);
    void setChild(AVLNode<T>* c, char direction); // will check with direction left or right
    void setHeight(int h);

    T getData();
    AVLNode<T>* getChild(char direction); // will check with direction left or right
    int getHeight(AVLNode<T>* r);

    AVLNode<T>* rightRotation(AVLNode<T>* a);
    AVLNode<T>* leftRotation(AVLNode<T>* a);
    int maxHeight(int h1, int h2);
    
};

// constructors
template <class T>
AVLNode<T>::AVLNode(T data)
{
    this->data.setCountry(data.getCountry());
    this->data.setCancerRate(data.getCancerRate());
    left = nullptr;
    right = nullptr;
    height = 1; 
}

 // destructor
template <class T>
AVLNode<T>::~AVLNode()
{
    data.setCountry("");
    data.setCancerRate(0);
    this->left = nullptr;
    this->right = nullptr;
    height = 0;
}

// setters
template <class T>
void AVLNode<T>::setData(T data)
{
    this->data = data;
}
template <class T>
void AVLNode<T>::setChild(AVLNode* c, char direction) // will check with direction left or right
{
    switch(direction)
    {
        case 'l':
            this->left = c;
            break;
        case 'r': 
            this->right = c;
            break;
    }
}
template <class T>
void AVLNode<T>::setHeight(int h)
{
    this->height = h;
}

//getters
template <class T>
T AVLNode<T>::getData()
{
    return this->data;
}
template <class T>
AVLNode<T>* AVLNode<T>::getChild(char direction) // will check with direction left or right
{
    if(direction == 'l')
    return this->left;

    return this->right;
}
template <class T>
int AVLNode<T>::getHeight(AVLNode<T>* r)
{
    if(r == nullptr)
    return 0;

    return this->height;
}

// extras
// performs right rotation for AVLTree
template <class T>
AVLNode<T>* AVLNode<T>::rightRotation(AVLNode<T>* a)
{
    AVLNode<T>* b = a->left; 
    AVLNode<T> *c = b->right;

    b->right = a; // part 1 of rotation
    a->left = c; // part 2 of rotation

    // reconfigure heights of pivot node and pivotee
    a->setHeight(maxHeight(a->left->getHeight(a->left), a->right->getHeight(a->right)) + 1);
    b->setHeight(maxHeight(b->left->getHeight(b->left), b->right->getHeight(b->right)) + 1);

    return b;
}
// performs left rotation for AVLTree
template <class T>
AVLNode<T>* AVLNode<T>::leftRotation(AVLNode<T>* a)
{
    AVLNode<T>* b = a->right;
    AVLNode<T>* c = b->left;

    b->left = a; // part 1 of rotation
    a->right = c; // part 2 of rotation

    // reconfigure heights of pivot node and pivotee
    a->setHeight(maxHeight(a->left->getHeight(a->left), a->right->getHeight(a->right)) + 1);
    b->setHeight(maxHeight(b->left->getHeight(b->left), b->right->getHeight(b->right)) + 1);

    return b;
}
// returns the max height after comparing left and right subtree heights 
template <class T>
int AVLNode<T>::maxHeight(int h1, int h2)
{
    if(h1 > h2)
    return h1;

    return h2;
}


#endif