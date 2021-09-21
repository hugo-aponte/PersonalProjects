/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |	
|	CptS 223;                 											 	  |
|	PA4																		  |
|	10/30/20																  |
|                                                                             |
| Description: The purpose of this file is to declare the RedBlackTree        |
|               class. This class declares the private variable root          |
|               and the public functions that manipulate said variable.       |
|               This class interacts with the RedBlackNode and                |
|               InventoryRecord classes to create a secure RedBlackTree       |
|               that follows all RedBlackTree properties.                     |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H
#include "pa4.h"

template <class T>
class RedBlackTree
{
    private:
        RedBlackNode<T>* root;
    public:
        RedBlackTree() : root(nullptr){}
        RedBlackTree(RedBlackNode<T>* r) : root(r){}
        RedBlackTree(T data){
            root = nullptr;
            root->getData().setID(data.getID());
            root->getData().setType(data.getType());
            root->getData().setNumItems(data.getNumItems());
        }
        ~RedBlackTree(){clear(root); root = nullptr;}

        //getter
        RedBlackNode<T>* getRoot(){return root;}
        
        //setter
        void setRoot(RedBlackNode<T>* r){root = r;}

        //others
        bool isEmpty()
        {
            if(root)
            return false;

            return true;
        }
        
        // updates an item in the tree 
        // if the oldData does not match any nodes, function returns
        // if the oldData's ID matches the newData's ID, the data of the nodes are swapped
        // if the oldData's ID does not match newData's ID, the node carrying the old data is removed and the node carrying the new data is inserted 
        void updateItem(T oldData, T newData)
        {
            RedBlackNode<T>* node = search(oldData);
            RedBlackNode<T>* newNode = new RedBlackNode<T>(newData, nullptr, nullptr, nullptr, RED);
            if(node->getData().getID() == oldData.getID())
            {
                if(node->getData().getID() == newNode->getData().getID())
                swapData(node, newNode);
                else
                {
                    remove(node);
                    insert(newNode);
                }
                
            }
            else
            {
                std::cout << "Could not find ID in the Tree!\n\n";
                return;
            }

        }

        // Inserts a node into red black tree nonrecursively
        void insert(RedBlackNode<T>* node)
        {
            if(root == nullptr)
            {
                node->setColor(BLACK);
                root = node;
            }
            else // check if value exists in the tree
            { 
                RedBlackNode<T>* check = search(node->getData()); // if search does not find a node equivalent to the parameter node, it returns the node;s position to be inserted
                if(check->getData().getID() == node->getData().getID())
                return;
                
                node->setParent(check);

                if(node->getData().getID() < check->getData().getID())
                    check->setLeft(node);
                else
                    check->setRight(node);

                fixDR(node);
            }
        }

        // searches for node in tree that matches parameter data
        RedBlackNode<T>* search(T data)
        {
            RedBlackNode<T>* current = root;
            while(current != nullptr)
            {
                if(data.getID() < current->getData().getID()){ 
                    
                    if (current->getLeft(current) == nullptr)
                    break;
                    else 
                    current = current->getLeft(current); 

                } else if (data.getID() == current->getData().getID())  
                    break; 
                else {
                    if (current->getRight(current) == nullptr) 
                    break;
                    else
                    current = current->getRight(current); 
                } 
            } 
            return current;
        }

        // fixes double red violation 
        void fixDR(RedBlackNode<T> *node) 
        {
            RedBlackNode<T> *parent = node->getParent(node), *grandparent = parent->getParent(parent), *uncle = node->getUncle();
                
            if (node == root) {  // if node == root, color black
                node->setColor(BLACK); 
                return; 
            } 
            
            if (parent->getColor() != BLACK) { 
                if (uncle != nullptr && uncle->getColor() == RED) { // red uncle case  
                    parent->setColor(BLACK); 
                    uncle->setColor(BLACK); 
                    grandparent->setColor(RED); 
                    fixDR(grandparent); 
                } else { 
                    if (parent->isLeft()) {  // left left and left right cases
                        if (node->isLeft())  
                            swapColors(parent, grandparent); 
                        else { 
                            rotateLeft(parent);  
                            swapColors(node, grandparent); 
                        }  
                        rotateRight(grandparent); 
                    } else { 
                    if (node->isLeft()) { // right right and right left cases 
                        rotateRight(parent); 
                        swapColors(node, grandparent); 
                    } else 
                        swapColors(parent, grandparent);                      
                        
                    rotateLeft(grandparent); 
                    } 
                } 
            } 
        } 

        // removes a node from the tree
        // three cases: leaf, one child, two children
        void remove(RedBlackNode<T>* node)
        {
            RedBlackNode<T>* newNode = getReplace(node);   // newNode refers to the node replacing parameter node, returned from replace()
            RedBlackNode<T>* parent = node->getParent(node);

            bool bothBlack = (newNode == nullptr || newNode->getColor() == BLACK) && (node->getColor() == BLACK);

            if(newNode == nullptr)
            {   // this makes node a leaf
                if(node == root)
                {
                    root = nullptr;
                } else {
                    if(bothBlack) // both nodes are black and parameter node is leaf, have to fix double black issue at leaf
                    {   
                        fixDB(node);
                    }
                    else
                    { // newNode or parameter node is red
                        if(node->getSibling() != nullptr) // make sibling red
                        node->getSibling()->setColor(RED);
                    }
                
                // deleting node
                if(node->isLeft())
                    parent->setLeft(nullptr);
                else
                    parent->setRight(nullptr);
                
                }
                delete node;
                return;
            }
            
            if(node->getLeft(node) == nullptr || node->getRight(node) == nullptr) // node has one child
            {
                if(node == root)
                {
                    node->setData(newNode->getData());
                    node->setLeft(nullptr);
                    node->setRight(nullptr);
                    delete newNode;
                } else // take off node from tree and move newNode up
                {
                    if(node->isLeft())
                        parent->setLeft(newNode);
                    else
                        parent->setRight(newNode);
                    
                    delete node;

                    newNode->setParent(parent);
                    if(bothBlack)
                        fixDB(newNode);
                    else
                        newNode->setColor(BLACK);
                }
                return;
            }
            swapData(newNode, node);
            remove(newNode);
        }

        // swaps data between two nodes
        void swapData(RedBlackNode<T>* n1, RedBlackNode<T>* n2)
        {
            T temp = n1->getData();
            n1->setData(n2->getData());
            n2->setData(temp);
        }

        // finds the node meant to replace a node in remove function
        // three cases: two children, one child, leaf
        RedBlackNode<T>* getReplace(RedBlackNode<T>* node)
        {
            // if two children
            if(node->getLeft(node) != nullptr && node->getRight(node) != nullptr)
                return getSuccessor(node->getRight(node));

            // if leaf
            if(node->getLeft(node) == nullptr && node->getRight(node) == nullptr)
                return nullptr;

            // if one child
            if(node->getLeft(node) != nullptr)
                return node->getLeft(node);
            else
                return node->getRight(node);
        
        }

        // finds the successor of a node to be removed
        RedBlackNode<T>* getSuccessor(RedBlackNode<T>* node)
        {
            RedBlackNode<T>* current = node;
            while(current->getLeft(node) != nullptr)
                current = current->getLeft(node);
            
            return current;
        }

        // fixes double black violation
        void fixDB(RedBlackNode<T>* node)
        {
            if(node == root)
            return;

            RedBlackNode<T>* sibling = node->getSibling();
            RedBlackNode<T>* parent = node->getParent(node);
            if(sibling == nullptr) // no sibling, fix parent
                fixDB(parent);
            else
            {
                if(sibling->getColor() == RED)
                {
                    parent->setColor(RED);
                    sibling->setColor(BLACK);
                    if(sibling->isLeft())
                        rotateRight(parent);
                    else
                        rotateLeft(parent);

                    fixDB(node);
                } else
                { // sibling is black
                    if(sibling->hasRedChild()) // one red child
                    {
                        if(sibling->getLeft(sibling) != nullptr && sibling->getLeft(sibling)->getColor() == RED)
                        {
                            if(sibling->isLeft()) // left left case
                            {
                                sibling->getLeft(sibling)->setColor(sibling->getColor());
                                sibling->setColor(parent->getColor());
                                rotateRight(parent);
                            } else                  // right left case
                            {
                                sibling->getLeft(sibling)->setColor(parent->getColor());
                                rotateRight(sibling);
                                rotateLeft(parent);
                            }
                            
                        } else
                        {
                            if(sibling->isLeft()) // left right case
                            {
                                sibling->getRight(sibling)->setColor(parent->getColor());
                                rotateLeft(sibling);
                                rotateRight(parent);
                            } else              // right right case
                            {
                                sibling->getRight(sibling)->setColor(sibling->getColor());
                                sibling->setColor(parent->getColor());
                                rotateLeft(parent);
                            }
                        }
                        parent->setColor(BLACK);   
                    } else  // there are 2 black children
                    {
                        sibling->setColor(RED);
                        if(parent->getColor() == BLACK)
                            fixDB(parent);
                        else
                            parent->setColor(BLACK);       
                    }
                }
            }
        }

        // completely clears a red black tree
        void clear(RedBlackNode<T>* node)
        {
            if(node != nullptr)
            {
                clear(node->getLeft(node));
                clear(node->getRight(node));
                delete node;
            }
        }

        // prints the tree in order
        void printInOrder(RedBlackNode<T>* n)
        {
            if(n == nullptr) return;
            printInOrder(n->getLeft(n));
            n->getData().print();
            printInOrder(n->getRight(n));
        }

        // right rotation that follows red black tree properties
        void rotateRight(RedBlackNode<T>* node)
        {
            RedBlackNode<T>* newParent = node->getLeft(node); // the new parent is set to be node's left child 
         
            if (node == root)  // update root
                root = newParent; 
        
            node->moveNodeDown(newParent); // calling RedBlackNode.h moveNodeDown function to move a node down
        
            
            node->setLeft(newParent->getRight(newParent)); // linking node's left child to the new parent's right child 
             
            if (newParent->getRight(newParent) != nullptr) // checking for nullptr, linking node to right child's parent
            newParent->getRight(newParent)->setParent(node); 
    
            newParent->setRight(node); // linking new parent with node

        }

        // left rotation that follows red black tree properties
        void rotateLeft(RedBlackNode<T>* node)
        {
            RedBlackNode<T>* newParent = node->getRight(node); // the new parent is set to be node's right child  
        
 
            if (node == root) // update root 
                root = newParent; 
        
            node->moveNodeDown(newParent); // calling RedBlackNode.h moveNodeDown function to move a node down 
         
            node->setRight(newParent->getLeft(newParent));  // linking node's right child to new parent's left child

            if (newParent->getLeft(newParent) != nullptr)   // checking for nullptr, linking node to parent
            newParent->getLeft(newParent)->setParent(node); 
         
            newParent->setLeft(node);  // linking new parent with node
            
        }

        // swaps colors between nodes
        void swapColors(RedBlackNode<T>* n1, RedBlackNode<T>* n2)
        {
            Color temp = n1->getColor();
            n1->setColor(n2->getColor());
            n2->setColor(temp);
        }
};





#endif