/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |	
|	CptS 223;                 											 	  |
|	PA4																		  |
|	10/30/20																  |
|                                                                             |
| Description: The purpose of this file is to define the InventoryRecord      |
|               class's public member function.                               |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#include "InventoryRecord.h"

// getters
int InventoryRecord::getID()
{
    return ID;
}
std::string InventoryRecord::getType()
{
    return type;
}
int InventoryRecord::getNumItems()
{
    return numItems;
}

// setters
void InventoryRecord::setID(int id)
{
    ID = id;
}
void InventoryRecord::setType(std::string type)
{
    this->type = type;
}
void InventoryRecord::setNumItems(int n)
{
    numItems = n;
}

//extras
void InventoryRecord::print()
{
    std::cout << ID << ", " << type << ", " << numItems << std::endl;
}

// facilitates data comparison 
bool operator<(InventoryRecord data1, InventoryRecord data2)
{
    if(data1.getID() < data2.getID())
    return true;     

    return false;       
}

InventoryRecord::InventoryRecord()
{
    ID = 0; 
    type = "";
    numItems = 0;
}

InventoryRecord::InventoryRecord(int ID, std::string type, int numItems)
{
    this->ID = ID; 
    this->type = type;
    this->numItems = numItems;
}