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
*               This individual files holds the function definitions corresponding to      * 
*               pa3.h. These functions will perform the testing required to create         * 
*                each AVL tree and print them                                      		   *
********************************************************************************************/

#include "pa3.h"

// creates AVLTree using bothcancerdata2018.csv file
// prints AVLTree
// destroys AVLTree
void testBoth()
{
    std::fstream iFile;
    iFile.open("bothcancerdata2018.csv", std::ios::in); // reading from both file
    AVLTree<CancerData>* test = new AVLTree<CancerData>();
    readFile(test, iFile); // inserting values
    iFile.close();
    test->printInOrder(test->getRoot(), "both"); // listing (1-50)
    test->getRoot()->getData().resetRank();
    test->~AVLTree(); // destroying tree
}

// reads from the file sent in through parameter
// inserts into AVLTree line by line
template <class T>
void readFile(AVLTree<T>* test, std::fstream& iFile)
{
    std::string c = "", rS = "", line = "";
    float r = 0;
    while(getline(iFile, line))
    {
        std::stringstream ss(line);
        getline(ss, c, ',');
        getline(ss, rS, ',');
        r = std::stof(rS);
        CancerData data(c, r);
        test->setRoot(test->insert(test->getRoot(), data));
    }

}

// creates AVLTree using mencancerdata2018.csv file
// prints AVLTree
// destroys AVLTree
void testMen()
{
    std::fstream iFile;
    iFile.open("mencancerdata2018.csv", std::ios::in); // reading from men file
    AVLTree<CancerData>* test = new AVLTree<CancerData>();
    readFile(test, iFile); // inserting values into AVL
    iFile.close();
    test->printInOrder(test->getRoot(), "men"); // listing 1-50
    test->getRoot()->getData().resetRank();
    test->~AVLTree(); // destroying tree
}

// creates AVLTree using womencancerdata2018-1.csv file
// prints AVLTree
// destroys AVLTree
void testWomen()
{
    std::fstream iFile;
    iFile.open("womencancerdata2018-1.csv", std::ios::in); // reading from women file
    AVLTree<CancerData>* test = new AVLTree<CancerData>();
    readFile(test, iFile); // inserting values into AVL
    iFile.close();
    test->printInOrder(test->getRoot(), "women"); // listing 1-50
    test->getRoot()->getData().resetRank();
    test->~AVLTree(); // destroying tree
}

// creates AVLTree to insert from all three .csv files
// after each complete file is read, parameter is used to tell which node to find, 1st or 50th
// after finding the 1st or 50th, AVLTree is cleared for use with next file
// AVLTree destroyed
void testMaxMin(std::string m)
{
    std::fstream iFile;
    AVLTree <CancerData>* test = new AVLTree<CancerData>(); 
    AVLNode <CancerData>* node;
    
    iFile.open("bothcancerdata2018.csv", std::ios::in); // opening both file
    readFile(test, iFile); // inserting both file values into AVL tree
    iFile.close();
    iFile.open("mencancerdata2018.csv", std::ios::in); // opening men file
    
  
    if(m == "max") // if this function was intended to test for the max (1st) cancer rate, call test->findMax()
    {
        node = test->findMax();
        std::cout << "both: 1) ";
    }
    else if(m == "min") // else if this function was intended to test for the min (50th) cancer rate, call test->findMin()
    {
        node = test->findMin();
        std::cout << "both: 50) ";  
    }

    node->getData().printData(); // print

    // clearing AVL Tree
    test->clear(test->getRoot());
    test->setRoot(nullptr);
    readFile(test, iFile);  // reading men file's values
    iFile.close(); 
    iFile.open("womencancerdata2018-1.csv", std::ios::in);
    
    if(m == "max") // if this function was intended to test for the max (1st) cancer rate, call test->findMax()
    {
        node = test->findMax();
        std::cout << "men: 1) ";
    }
    else if(m == "min") // else if this function was intended to test for the min (50th) cancer rate, call test->findMin()
    {
        node = test->findMin();
        std::cout << "men: 50) ";  
    }
    node->getData().printData(); // print

    //clearing AVL Tree
    test->clear(test->getRoot());
    test->setRoot(nullptr);
    readFile(test, iFile); // reading women file's values
    iFile.close();

    if(m == "max") // if this function was intended to test for the max (1st) cancer rate, call test->findMax()
    {
        node = test->findMax();
        std::cout << "women: 1) ";
    }
    else if(m == "min") // else if this function was intended to test for the min (50th) cancer rate, call test->findMin()
    {
        node = test->findMin();
        std::cout << "women: 50) ";  
    }
    node->getData().printData(); // print
    test->~AVLTree(); // destroying tree
}

