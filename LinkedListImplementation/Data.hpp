/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file holds the Data class, its private members, its      |
|               public members/functions. Data holds the commands and         |
|               descriptions that populate the nodes of the linked list.      |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef DATA_HPP
#define DATA_HPP
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Data
{
    private:
        string command;
        string description;
    public:

        Data()
        {
            this->command = '\0';
            this->description = '\0';
        }
        Data(string a, string b)
        {
            this->command = a;
            this->description = b;
        }

        // getters
        string getCommand();
        string getDescription();

        // setters
        void setCommand(string c);
        void setDescription(string d);
    

};

#endif