/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |	
|	CptS 223;                 											 	  |
|	PA4																		  |
|	10/30/20																  |
|                                                                             |
| Description: The purpose of this file is to declare the RedBlackNode        |
|               class. This class declares the private variables data,        |
|               left, right, parent, and color and the public functions       |
*               that manipulate said variables.                               |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef REDBLACKNODE_H
#define REDBLACKNODE_H
#include "pa4.h"

enum Color {RED, BLACK};

template <class T>
class RedBlackNode
{
    private:
        T data;
        RedBlackNode<T>* left;
        RedBlackNode<T>* right;
        RedBlackNode<T>* parent;
        Color color;     // false -> red; true -> black
    public:
        // constructors
        RedBlackNode()
        {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
            color = RED;
        }
        RedBlackNode(T d, RedBlackNode<T>* l, RedBlackNode<T>* r, RedBlackNode<T>* p, Color c)
        {
            data = d;
            left = l;
            right = r;
            parent = p;
            color = c;
        }
        // destructor
        ~RedBlackNode() 
        {
            left = nullptr;
            right = nullptr;
            parent = nullptr;
        }

        //getters
        T getData(){return data;}
        RedBlackNode<T>* getLeft(RedBlackNode<T>* node) {if(node == nullptr) return nullptr; else return left;}
        RedBlackNode<T>* getRight(RedBlackNode<T>* node) {if(node == nullptr) return nullptr; else return right;}
        RedBlackNode<T>* getParent(RedBlackNode<T>* node) {if(node == nullptr) return nullptr; else return parent;}
        Color getColor() {return color;}

        //setters
        // data does not need setter, user can use getter, then direct setters from InventoryRecord.h
        void setLeft(RedBlackNode<T>* l){left = l;}
        void setRight(RedBlackNode<T>* r){right = r;}
        void setParent(RedBlackNode<T>* p){parent = p;}
        void setColor(Color c){color = c;}
        void setData(T d)
        {
            data.setID(d.getID());
            data.setType(d.getType());
            data.setNumItems(d.getNumItems());
        }

        //extra
        // checks if current node is left child of its parent
        bool isLeft(){return this == parent->left;}

        // checks if current node has a red child
        bool hasRedChild()
        {
            bool rC = (left != nullptr && left->color == RED) || (right != nullptr && right->color == RED);
            return rC;
        }

        // returns the uncle of the current node
        RedBlackNode<T>* getUncle()
        {
            if(parent == nullptr || parent->parent == nullptr) // no uncle case
            return nullptr;

            if(parent->isLeft()) // return right uncle
                return parent->parent->right;
            else                    // return left uncle
                return parent->parent->left;            
        }

        // returns the sibling of the current node
        RedBlackNode<T>* getSibling()
        {
            if(this->parent == nullptr) // no parent case
                return nullptr;

            if(isLeft())
                return parent->right;

            return parent->left;
        }

        // moves a node down the tree
        void moveNodeDown(RedBlackNode<T>* node)
        {
            if(this->parent != nullptr)
            {
                if(isLeft())                
                    parent->left = node;
                else
                    parent->right = node;                 
            }
            node->parent = this->parent;
            this->parent = node;
        }
        
};

#endif