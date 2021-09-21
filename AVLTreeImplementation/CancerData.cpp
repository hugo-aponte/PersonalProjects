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
*               This individual file holds the function definitions corresponding to       *
*               CancerData.h. These functions are those declared within the CancerData     *
*               class. It will be used for the templated AVLTrees, so the data that        *
*               each tree stores can hold more than one variable.                          * 
*                                		                                                   *
********************************************************************************************/

#include "CancerData.h"
int rank = 1; // global variable

// explicit constructor
CancerData::CancerData(std::string c, float r)
{
    country = c;
    cancerRate = r;
}

// setters
void CancerData::setCountry(std::string c)
{
    country = c;
}

void CancerData::setCancerRate(float r)
{
    cancerRate = r;
}

// getters
std::string CancerData::getCountry()
{
    return country;
}

float CancerData::getCancerRate()
{
    return cancerRate;
}

// prints data with file parameter to define label
// global int rank used to keep track of listing
void CancerData::printData(std::string file)
{
    std::cout << file << ": " << rank++ << ") " << country << std::setprecision(4) << " " << cancerRate << std::endl;
}

// prints data without file parameter
// this function was mainly used for debugging where label and rank are negligible
void CancerData::printData()
{
    std::cout << country << std::setprecision(5) << " " << cancerRate << std::endl;
}

// resets global int rank to list 1-50 in the next file
void CancerData::resetRank()
{
    rank = 1;
}