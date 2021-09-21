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
*               This individual file holds the function prototypes and definitions for     *
*               the public member functions declared by the class AVLTree. This class      *
*               is templated to accomodate for complex data (holding countries and cancer  *
*               rates).                                                           		   *
********************************************************************************************/

#ifndef AVLTREE_H
#define AVLTREE_H

#include "pa3.h"

template <class T>
class AVLTree
{
private:
    AVLNode<T>* root;
public:
    AVLTree(AVLNode<T>* other) : root(other.root){} // cpy constructor defined here
    AVLTree() : root(nullptr){} // constructor defined here
    ~AVLTree();

    // setter
    void setRoot(AVLNode<T>* r);
    // getter
    AVLNode<T>* getRoot();
    int getHeight(AVLNode<T>* node);

    // other required functions
    bool isEmpty();
    AVLNode<T>* insert(AVLNode<T>* r, T data); // must abide by AVL balancing properties
    AVLNode<T>* remove(AVLNode<T>* r, T data); // must abide by AVL balancing properties
    void clear(AVLNode<T>* node);   // removes all elements
    AVLNode<T>* findMin();
    AVLNode<T>* findMax();
    void printInOrder(AVLNode<T>* r, std::string file);
    int getBalance(AVLNode<T>* r);



};
// destructor
template <class T>
AVLTree<T>::~AVLTree()
{
    clear(getRoot());
    setRoot(nullptr);
}

// setter
template <class T>
void AVLTree<T>::setRoot(AVLNode<T>* r)
{
    root = r;
}

// getter
template <class T>
AVLNode<T>* AVLTree<T>::getRoot()
{
    return root;
}
template <class T>
int AVLTree<T>::getHeight(AVLNode<T>* node)
{
    if(node)
    return node->getHeight(node);

    return 0;
}

// other required functions
template <class T>
bool AVLTree<T>::isEmpty()
{
    if(root)
        return false;

    return true;
}
// recursive insert function for AVLTree
// checks if subtrees are balanced, and reassigns positions if they're not
// self-balancing
template <class T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* r, T data)
{
    int balance = 0;
    if(root == nullptr)
    {
        setRoot(new AVLNode<T>(data));
        return getRoot();
    } else if (r == nullptr)
    {
        r = new AVLNode<T>(data);
    }else if(r->getData().getCancerRate() <= data.getCancerRate() && data.getCountry() != r->getData().getCountry()) // if stored data is less than or equal to new data, insert on right subtree
        r->setChild(insert(r->getChild('r'), data), 'r');
    else if(r->getData().getCancerRate() > data.getCancerRate())  // if stored data is greater than new data, insert on left subtree
        r->setChild(insert(r->getChild('l'), data), 'l');

    // configuring height to new node (the reason getHeight takes a parameter of getChild() which is already calling it is to assure it's not nullptr)
    r->setHeight(r->maxHeight(r->getChild('l')->getHeight(r->getChild('l')), r->getChild('r')->getHeight(r->getChild('r'))) + 1);

    balance = getBalance(r); // finding balance factor

    // left left
    if(balance > 1 && data.getCancerRate() < r->getChild('l')->getData().getCancerRate())
        return r->rightRotation(r);
    // left right
    if(balance > 1 && data.getCancerRate() > r->getChild('l')->getData().getCancerRate())
    {
        r->setChild(r->leftRotation(r->getChild('l')), 'l');
        return r->rightRotation(r);
    }
    // right right
    if(balance < -1 && data.getCancerRate() > r->getChild('r')->getData().getCancerRate())
        return r->leftRotation(r);
    // right left
    if(balance < -1 && data.getCancerRate() < r->getChild('r')->getData().getCancerRate())
    {
        r->setChild(r->rightRotation(r->getChild('r')), 'r');
        return r->leftRotation(r);
    }

    return r;

}
// removes a node from the AVLTree
// self-balances if necessary
template <class T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* r, T data)
{
    int balance = 0;
    if(r == nullptr)
        return r;

    if(r->getData().getCancerRate() > data.getCancerRate())
        r->setChild(remove(r->getChild('l'), data), 'l');
    else if(r->getData().getCancerRate() < data.getCancerRate())
        r->setChild(remove(r->getChild('r'), data), 'r');
    else
    {
        AVLNode<T>* t;
        if(r->getChild('l') == nullptr || r->getChild('r') == nullptr)
        {
            // conditional to check whether there is one or no child node
            if(r->getChild('l') == nullptr)
            t = r->getChild('r');
            else if(r->getChild('r') == nullptr)
            t = r->getChild('l');
            else
            t = nullptr;

            // case if there are no child nodes
            if(t == nullptr)
            {
                t = r;
                r = nullptr;
            }
            else
            {
                *r = *t;
                delete t;
            }
        } else {
            AVLNode<T>* t = findMin(r->getChild('r'));
            r->data = t->data;
            r->setChild(remove(r->getChild('r'), t->data), 'r');

        }
    }

    if(r == nullptr)
    return r;

    r->setHeight(r->maxHeight(r->getChild('l')->getHeight(r->getChild('l')), r->getChild('r')->getHeight(r->getChild('r'))) + 1);
    balance = getBalance(r);

    // left left
    if(balance > 1 && getBalance(r->getChild('l')) >= 0)
        return r->rightRotation(r);
    // left right
    if(balance < 1 && getBalance(r->getChild('l')) < 0)
    {
        r->setChild(r->leftRotation(r->getChild('l')), 'l');
        return r->rightRotation(r);
    }
    // right right
    if(balance < -1 && getBalance(r->getChild('r')) <= 0)
        return r->leftRotation(r);
    // right left
    if(balance < -1 && getBalance(r->getChild('r')) > 0)
    {
        r->setChild(r->rightRotation(r->getChild('r')), 'r');
        return r->leftRotation(r);
    }
    return r;
}
// recursive clear function to delete every node in AVLTree
template <class T>
void AVLTree<T>::clear(AVLNode<T>* node)   // removes all elements
{
    if(node != nullptr)
    {
        clear(node->getChild('l'));
        clear(node->getChild('r'));
        delete node;
    }

}
// finds the minimum value by traversing left subtree
// returns node with min
template <class T>
AVLNode<T>* AVLTree<T>::findMin()
{
    AVLNode<T>* current = root;
    while(current->getChild('l') != nullptr)
        current = current->getChild('l');

    return current; // the left most item should be the item with the minimum value

}
// finds the maximum value by traversing right subtree
// returns node with max 
template <class T>
AVLNode<T>* AVLTree<T>::findMax()
{
    AVLNode<T>* current = root;
    while(current->getChild('r') != nullptr)
        current = current->getChild('r');

    return current; // the right most item should be the item with the maximum value
}
// prints in OPPOSITE ORDER
// instead of recursively traversing left subtree first, it traverses the right subtree first
// this helps list the items required by this assignment in the correct order (1-50 largest to greatest)
template <class T>
void AVLTree<T>::printInOrder(AVLNode<T>* r, std::string file)
{
    if(r == nullptr)
        return;

    printInOrder(r->getChild('r'), file);
    r->getData().printData(file);
    printInOrder(r->getChild('l'), file);

}
// returns the height difference between subtrees
template <class T>
int AVLTree<T>::getBalance(AVLNode<T>* r)
{
    if(r == nullptr)
    return 0;

// avoiding seg fault errors by checking for nullptr

    return r->getChild('l')->getHeight(r->getChild('l')) - r->getChild('r')->getHeight(r->getChild('r'));
}



#endif