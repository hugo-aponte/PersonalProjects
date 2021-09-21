/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file holds all function definitions pertaining to        |
|               the class List.                                               |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "List.hpp"
#include "Data.hpp"
#include "Node.hpp"

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: insertCommand()                                 *
* Description: creates a new node with data members command *
*               and description                             *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <class NODETYPE>
void List<NODETYPE>::insertCommand(string command, string description)
{
    Data* data = new Data(command, description);
    Node<Data>* newNode = new Node<Data>(*data);
    newNode->setNext(getHead());
    setHead(newNode);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: testPrint()                                     *
* Description: test function to ensure list is populated    *
*               (function not involved in game)             *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
void List<NODETYPE>::testPrint()
{
    Node<Data>* current = getHead();

    while(current != nullptr)
    {
        cout << current->getData().getCommand() << endl;
        current = current->getNext();
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: displayCommand()                                *
* Description: displays a command for the user to select    *
*               a matching description                      *
* Returns: points relative to a correct/incorrect answer    *                                             
* Preconditions: playGame() function must be called         *
* Postconditions: remove() deletes command from the list    *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
int List<NODETYPE>::displayCommand(int runCount, int* userSelection, int* correctAnswer)
{
    int r = rand() % (30-runCount) + 1; 
    Node<Data>* current = getHead();
    for(int i=0; i<r && current!=nullptr; i++)
    {
        current = current->getNext();
    }
    cout << "Command: " << current->getData().getCommand()<< "\n" << endl;
    cout << "Descriptions: " << endl; 
    display3Descriptions(r, runCount, correctAnswer);

    if(compareUserAnswer(userSelection, correctAnswer))
    {
        cout << "Correct!\n";
        return 1;
    }
    else
    {
        cout << "Incorrect!\n";
        return -1;
    }
    
    remove(current->getData().getCommand());
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: remove()                                        *
* Description: removes node from the list                   *
* Returns: void                                             *
* Preconditions: playGame() or delete command menu option   *
*               must be run/selected                        *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
void List<NODETYPE>::remove(string command) 
{
    Node<Data>* current = getHead();

    if (this->isEmpty()) 
    {
        cout << "There are no commands in the list";
        return;
    }

    Node<Data>* previous = nullptr;
    while(current != nullptr && current->getData().getCommand() != command)
    {
        previous = current;
        current = current->getNext();
    }

    if (previous != nullptr) 
    {
        previous->setNext(current->getNext());
    }
    else
    {
        setHead(current->getNext());
    }
    

    delete current;
    
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: isEmpty()                                       *
* Description: checks if list is empty                      *
* Returns: true or false                                    *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
bool List<NODETYPE>::isEmpty()
{
    if(getHead() == nullptr)
    return true;
    
    return false;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: display3Descriptions()                          *
* Description: displays 2 random descriptions along         *
                with a correct one. Their placement in      *
                console display is also randomized          *
* Returns: void                                             *
* Preconditions: command should already be displayed        *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
void List<NODETYPE>::display3Descriptions(int correctPos, int runCount, int* correctAnswer)
{
    Node<Data>* current = getHead();
    int randomWrongPos1 = rand() % (30 - runCount) + 1, randomWrongPos2 = 0;
    int randomDisplay = rand() % 3;
    

    do // so that we dont get the same wrong description
    {
        randomWrongPos2 = rand() % (30 - runCount) + 1;
    } while (randomWrongPos1 == randomWrongPos2);

    switch(randomDisplay) // there are three options to choose in order to randomly distinguish between wrong and correct displayed descriptions
    {
        case 0:
        // displays a wrong description first
            for(int i = 0; i < randomWrongPos1; i++)
            {
                current = current->getNext();
            }
            cout << "1. " << current->getData().getDescription() << "\n";
            current = getHead();
        // displays a wrong description second
            for(int i = 0; i < randomWrongPos2; i++)
            {
                current = current->getNext();
            }
            cout << "2. " << current->getData().getDescription() << "\n";
            current = getHead();
        // displays a correct description third
            for(int i = 0; i < correctPos; i++)
            {
                current = current->getNext();
            }
            cout << "3. " << current->getData().getDescription() << endl;
            *correctAnswer = 3;
        break;
        case 1:
        // displays a wrong description first
            for(int i = 0; i < randomWrongPos1; i++)
            {
                current = current->getNext();
            }
            cout << "1. " << current->getData().getDescription() << "\n";
            current = getHead();
        // displays a correct description second
            for(int i = 0; i < correctPos; i++)
            {
                current = current->getNext();
            }
            cout << "2. " << current->getData().getDescription() << "\n";
            current = getHead();
        // displays a wrong description third
            for(int i = 0; i < randomWrongPos2; i++)
            {
                current = current->getNext();
            }
            cout << "3. " << current->getData().getDescription() << endl;
            *correctAnswer = 2;
        break;
        case 2:
                // displays a correct description first
            for(int i = 0; i < correctPos; i++)
            {
                current = current->getNext();
            }
            cout << "1. " << current->getData().getDescription() << "\n";
            current = getHead();
        // displays a wrong description second
            for(int i = 0; i < randomWrongPos1; i++)
            {
                current = current->getNext();
            }
            cout << "2. " << current->getData().getDescription() << "\n";
            current = getHead();
        // displays a wrong description third
            for(int i = 0; i < randomWrongPos2; i++)
            {
                current = current->getNext();
            }
            cout << "3. " << current->getData().getDescription() << endl;
            *correctAnswer = 1;
        break;
    }
    
    

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: compareUserAnswer()                             *
* Description: compares user's answer from display3Descriptions*
*               to the correct answer                       * 
* Returns: true or false                                    *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
bool List<NODETYPE>::compareUserAnswer(int* userSelection, int* correctAnswer)
{

    int count = 0;
    char selection[30] = "";
    do
    {
        if(!count)
        cout << "Selection: ";
        else
        cout << "Try Again (1-3): ";
        
        count++;
        cin >> selection;
        *userSelection = atoi((char*)selection);
    }while(*userSelection < 1 || *userSelection > 3);
    cout << "\n\n";
    if(*userSelection == *correctAnswer)
    return true;

    return false;
    
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: findCommand()                                   *
* Description: searches for command in linked list          *
* Returns: true or false                                    *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
template <typename NODETYPE>
bool List<NODETYPE>::findCommand(string command)
{
    Node<Data>* current = getHead();
    while(current!=nullptr && current->getData().getCommand() != command)
    {
        current = current->getNext();
    }
    if(current != nullptr && current->getData().getCommand() == command)
    return true;

    return false;

}

// setter
template <typename NODETYPE>
void List<NODETYPE>::setHead(NODETYPE* h)
{
    head_ptr = h;
}

// getter
template <typename NODETYPE>
NODETYPE* List<NODETYPE>::getHead()
{
    return this->head_ptr;
}


template class List<Node<Data>>;
template class Node<Data>;