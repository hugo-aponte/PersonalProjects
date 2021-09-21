/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |	
|	CptS 223;                 											 	  |
|	PA4																		  |
|	10/30/20																  |
|                                                                             |
| Description: The purpose of this file is to declare the InventoryRecord     |
|               class. This class declares the private variables ID,          |
|               type, and numItems and the public functions that manipulate   |
|               said variables.                                				  |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#ifndef INVENTORYRECORD_H
#define INVENTORYRECORD_H
#include "pa4.h"


 class InventoryRecord
 {
    private:
        int ID;
        std::string type;
        int numItems;

    public:
        explicit InventoryRecord(int ID, std::string type, int numItems);
        InventoryRecord();
        ~InventoryRecord(){}

        // getters
        int getID();
        std::string getType();
        int getNumItems();

        // setters
        void setID(int id);
        void setType(std::string type);
        void setNumItems(int n);

        // extras
        void print();

 };

bool operator<(InventoryRecord data1, InventoryRecord data2);


#endif