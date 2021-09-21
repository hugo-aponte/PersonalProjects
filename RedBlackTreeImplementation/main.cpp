/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |	
|	CptS 223;                 											 	  |
|	PA4																		  |
|	10/30/20																  |
|                                                                             |
| Description: The purpose of this program is to read records from the file   |
|               InventoryRecord.csv into a Red Black Tree that properly       |
|               follows the conditions of a Red Black Tree. A menu will       |
|               be printed for a user to select 1 of 5 options: add,          |
|               remove, update, print, and exit. Although this is the         |
|               intention, for the grader's sake, the menu is set to run      |
|               all options UNLESS THE USER SETS TEST = FALSE! In this case,  |
|               the user will have full control over the menu until they      |
|               select the exit option.                      				  |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#include "pa4.h"


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: readFile                                        *
* Description: Reads from InventoryRecord.csv and inserts   *
*               records into a Red Black Tree               *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <class T>
void readFile(RedBlackTree<T>* tree, std::fstream& iFile)
{
    std::string line, type, IDstr, numItemStr;
    while(getline(iFile, line))
    {
        std::stringstream ss(line);
        getline(ss, IDstr, ',');
        getline(ss, type, ',');
        getline(ss, numItemStr, ',');
        InventoryRecord data{std::stoi(IDstr), type, std::stoi(numItemStr)};
        RedBlackNode<T>* dataN = new RedBlackNode<T>(data, nullptr, nullptr, nullptr, RED);
        tree->insert(dataN);
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: promptItem                                      *
* Description: Prompts user for data variables              *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void promptItem(int &ID, std::string &type, int &numItems)
{   
    std::cout << "Enter ID: ";
    std::cin >> ID;
    std::cout << "Enter Type: ";
    std::cin >> type;
    std::cout << "Enter Number of Items: ";
    std::cin >> numItems;

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: menu(int)                                       *
* Description: Prints menu and prompts user for an option   *
*               selection                                   *
* Returns: void                                             *
* Preconditions:  main() local variable test = false        *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void menu(int &option)
{
    bool output = true;
    std::cout << "Choose an option from the menu: \n"
              << "1. Add new item to inventory\n"
              << "2. Remove an item from inventory\n"
              << "3. Update an item in inventory\n"
              << "4. Display the inventory\n"
              << "5. Exit\n\n"
              << "Enter: ";
    do
    {

        if(output)
            std::cin >> option;
        else
        {
            std::cout << "Try again: ";
            std::cin >> option;            
        }
        output = false;
    
    } while (option < 1 || option > 5);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: menu()                                          *
* Description: displays menu with no required user selection*                        *
* Returns: void                                             *
* Preconditions: main() local variable test = true          *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void menu()
{
    std::cout << "Choose an option from the menu: \n"
              << "1. Add new item to inventory\n"
              << "2. Remove an item from inventory\n"
              << "3. Update an item in inventory\n"
              << "4. Display the inventory\n"
              << "5. Exit\n"
              << "DEBUGGING... PRESS ENTER TO CONTINUE...\n";
              std::cin.get();
              system("clear");

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: addItem                                         *
* Description: inserts a user prompted item into Red Black  *
*               Tree                                        *
* Returns: void                                             *
* Preconditions: Tree is already built                      *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <class T>
void addItem(RedBlackTree<T>* tree)
{
    std::cout << "Adding item to Tree..." << std::endl;
    int ID, numItems;
    std::string type;
    promptItem(ID, type, numItems);
    InventoryRecord data{ID, type, numItems};
    RedBlackNode<InventoryRecord>* node = new RedBlackNode<InventoryRecord>(data, nullptr, nullptr, nullptr, RED);
    tree->insert(node);
    std::cout << "\n\n";
    tree->printInOrder(tree->getRoot());
    std::cout << "PRESS ENTER TO CONTINUE..." << std::endl;
    std::cin.ignore();
    std::cin.get();

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: removeItem                                      *
* Description: removes a user prompted item from Red Black  *
*               Tree                                        *
* Returns: void                                             *
* Preconditions: tree is already built                      *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <class T>
void removeItem(RedBlackTree<T>* tree)
{
    std::cout << "Removing item from Tree..." << std::endl;
    int searchID;

    std::cout << "Enter Search ID: ";
    std::cin >> searchID;
    InventoryRecord data{searchID, "", 0};
    RedBlackNode<InventoryRecord>* node = tree->search(data);

    if(node->getData().getID() != searchID)
    {
        std::cout << "Could not find ID in the Tree!\n";
        return;
    }else
    {
        tree->remove(node);
    }
    
    std::cout << "\n\n";
    tree->printInOrder(tree->getRoot());
    std::cout << "PRESS ENTER TO CONTINUE..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: updateItem                                      *
* Description: Updates an existing item from a Red Black    *
*               Tree. If it does not exist, no item is      *
*               updated.                                    *
* Returns: void                                             *
* Preconditions: Tree is already built                      *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <class T>
void updateItem(RedBlackTree<T>* tree)
{
    int searchID = 0, ID, numItems;
    std::string type = "";

    std::cout << "Updating Item! Enter Search ID: ";
    std::cin >> searchID;

    InventoryRecord oldData{searchID, "", 0}; // the ID is the only parameter that matters for search 

    std::cout << "Prompting for New Data!\n";
    promptItem(ID, type, numItems);
    InventoryRecord newData{ID, type, numItems};

    tree->updateItem(oldData, newData);
    tree->printInOrder(tree->getRoot()); 
    std::cout << "\nPRESS ENTER TO CONTINUE..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}



// main prog
int main()
{

    std::fstream iFile;
    iFile.open("InventoryRecord.csv", std::ios::in);
    RedBlackTree<InventoryRecord>* tree = new RedBlackTree<InventoryRecord>();
    int option = 0;
    bool test = true; // this'll allow the program to add, remove, update, display, and exit on its own
    // user should make this false to test them on their own 

    // read from InventoryRecord.csv
    readFile(tree, iFile);


    while(option != 5)
    {
        if(test) 
        {
            if(option == 0)
            {
                std::cout << "Test boolean = true... Program will run every option in menu!\n(User can make boolean = false to choose options manually from the menu) \n\n";
                menu();
            }

            option++; // this will go through the menu options 
        }
        else
        {
            std::cout << "Test boolean = false...\n\n\n";
            menu(option); // if test is false, user can choose options
        }
        system("clear");

        switch(option)
        {
            case 1:
                addItem(tree);
                break;
            case 2: 
                removeItem(tree);
                break;
            case 3:
                updateItem(tree);
                break;
            case 4:
                tree->printInOrder(tree->getRoot());
                break;
            case 5:
                std::cout << "Exiting program!\n";
                break;
        }
    }
}