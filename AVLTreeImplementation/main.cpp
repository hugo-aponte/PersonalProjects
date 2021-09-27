/*******************************************************************************************
* Programmer: Hugo Aponte								   *
*                Fall, 2020;              						   *
*		      PA3                             					   *
* Date: October 9th, 2020								   *					
* Description: This program reads in cancer data from various files: both men and women,   *
*               men alone, and women alone. The goal is to create three AVL trees that     *
*               store country cancer rates for the corresponding file. This AVL tree       *
*               should be following the AVL properties. We will also use the tree to       * 
*               find the max and min cancer rates for each file.                  	   *
********************************************************************************************/


#include "pa3.h"


/* 
*       The worst case Big-O of the insert() algorithm is O(logn). This algorithm is dependent on the height of the tree
        and of its self-balancing tendencies. Since it's guaranteed to be balanced because of AVL properties, the worst case
        height of the tree is logn

*       The worst case Big-O of the printInOrder() algorithm is O(n). This algorithm is dependent on the height of 
        the tree as well, and it will visit every node to execute either 1 or 4 operations. Because of this,
        it is dependent on n*4 or n*1 operations depending on the position the recursion is in which reduces to 
        a worst case of O(n)

*       The worst case Big-O of the findMax() algorithm is O(n). This algorithm is dependent on the traversal 
        of the binary tree towards the right most element in the right subtree. For this reason, it will hit every
        node until it reaches the max node. 

*/

int main()
{   
    std::cout << "Listed 1 – 50 (from highest to lowest rate), the global cancer rates for both sexes.\n";
    testBoth();
    std::cout << "\nListed 1 – 50 (from highest to lowest rate), the global cancer rates for men.\n";
    testMen();
    std::cout << "\nListed 1 – 50 (from highest to lowest rate), the global cancer rates for women.\n";
    testWomen();
    std::cout << "\nListed on 3 separate lines the 1st ranked country for the global cancer rates for both sexes, men, and women.\n";
    testMaxMin("max");
    std::cout << "\nListed on 3 separate lines the 50th ranked country for the global cancer rates for both sexes, men, and women. \n";
    testMaxMin("min");
}