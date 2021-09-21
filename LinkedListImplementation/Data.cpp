/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file holds all function definitions pertaining to        |
|               the class Data.                                               |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "Data.hpp"

// getters
string Data::getCommand()
{
    return command;
}
string Data::getDescription()
{
    return description;
}

//setters
void Data::setCommand(string c)
{
    command = c;
}
void Data::setDescription(string d)
{
    description = d;
}