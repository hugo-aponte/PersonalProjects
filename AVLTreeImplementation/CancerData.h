/*******************************************************************************************
* Programmer: Hugo Aponte																   *
* Class: CptS 223, Fall, 2020;              											   *
* Programming Assignment: PA3															   *
* Date: October 9th, 2020																   *					
* Description: This program reads in cancer data from various files: both men and women,   *
*               men alone, and women alone. The goal is to create three AVL trees that     *
*               store country cancer rates for the corresponding file. This AVL tree       *
*               should be following the AVL properties. We will also use the tree to       * 
*               find the max and min cancer rates for each file.                  		   *
*                                                                                          *
*               This individual file holds the function prototypes and class definition    *
*               of CancerData. It will allow the AVLTree class to hold data members        *
*               corresponding to specific Cancer Data (country and corresponding cancer    *
*               rates)                                                                     *
********************************************************************************************/

#ifndef CANCERDATA_H
#define CANCERDATA_H

#include "pa3.h"

class CancerData
{
private:
    std::string country; // name of certain country
    float cancerRate; // cancerRate associated with country
public:
    explicit CancerData(std::string c, float r);
    CancerData(){country = ""; cancerRate = 0;}
    ~CancerData(){};

    void setCountry(std::string c);
    void setCancerRate(float r);
    std::string getCountry();
    float getCancerRate();
    void printData(std::string file);
    void printData(); // function overloaded for testMaxMin() function
    void resetRank();
    // consider making an operator= function
};

#endif