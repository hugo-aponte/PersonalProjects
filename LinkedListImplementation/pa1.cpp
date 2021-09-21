/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file stores all function definitions used in main        |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "pa1.hpp"
#include <sstream>
#include <istream>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: mainMenu()                                      *
* Description: displays a menu for the user                 *
* Returns: User selection                                   *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int mainMenu()
{
    int ans = 0, count = 0;

    do
    {
        if(!count)
        {
        cout << "Main Menu\n1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\nSelect: ";
        }
        else
        {
            cout << "Try again (1-6): ";
        }
        count+=1;
        cin >> ans;
        
    }while(ans < 1 || ans > 6);
    
    system("clear");
    return ans;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: gameRules()                                     *
* Description: displays the game's rules to the user        *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void gameRules()
{
    cout << "This is a matching game! You must match the correct linux command to the correct description.\n"
             "We've got 30 commands for you to decipher. Your points will be displayed before each command.\n"
             "After each selection you make, a correct answer will add +1 points, and a wrong answer will add -1 points.\n"
             "Get started now!\n";
             system("read -p 'Press Enter to Continue...' var");
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: loadListFromFile()                              *
* Description: loads commands and corresponding descriptions*
*                from a csv file into a linked list         *
* Returns: void                                             *
* Preconditions: beginning of program; existing csv file    *
*                 with commands and descriptions required   *
* Postconditions: linked list is populated                  *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loadListFromFile(List<Node<Data>>* l, fstream& iFile)
{
    string a, b; 
    while(!iFile.eof())
    {
        getline(iFile, a, ',');
        getline(iFile, b, '\n');
        l->insertCommand(a, b);

    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: updateCommandsDoc()                             *
* Description: updates the commands csv file using the      *
*               linked list                                 *
* Returns: void                                             *
* Preconditions: list has to be populated with existing     *
*               commands from csv file before overwriting   *
*               the same file.                              *
* Postconditions: csv file can have additional or less      *
*                   commands compared to when the list      *
*                   was first populated                     *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void updateCommandsDoc(fstream& iFile, List<Node<Data>>* list, string newCommand, char newDescription[])
{
    Node<Data>* current = list->getHead();
    while(current != nullptr)
    {
        iFile << current->getData().getCommand() << ", " << current->getData().getDescription() << endl;
        current = current->getNext(); 
    }

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: checkNumEntries()                               *
* Description: reads the profile csv and counts the amount  *
*               of lines                                    *
* Returns: number of lines in profiles.csv                  *
* Preconditions: profiles csv has stored previous game      *
*               results and users                           *
* Postconditions: fstream variable must be closed and       *
*                    reopened                               *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int checkNumEntries(fstream& iFile) // the purpose of this is to create a profiles array with adequate length for each general run of the program 
{
    int count = 0;
    string buffer;
    while(!iFile.eof())
    {
        getline(iFile, buffer, ',');
        getline(iFile, buffer, '\n');
        count++;
    }
    iFile.close(); // refreshes so we can read it again in loadProfilesFromFile
    return count;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: loadProfilesFromFile()                          *
* Description: reads profiles from a csv file to            *
*               populate an area (each value submitted at   *   
*               index 0)                                    *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void loadProfilesFromFile(profile profiles[], fstream& iFile)
{
    string name;
    string points_s; //points represented as a string
    int points_i;   // points represented as an integer


    while(!iFile.eof())
    {
        getline(iFile, name, ',');
        getline(iFile, points_s, '\n');
        stringstream geek(points_s);
        geek >> points_i;
        for(int i = 0; i < (int)(sizeof(*profiles)/sizeof(profiles[0])); i ++) // this calculation within the for loop's condition finds the length of the array
        {
            
            if(profiles[i].name == "\0")
            {
                profiles[i].name = name;
                profiles[i].points = points_i;
            }
            else
            {
                int j = i;
                while(profiles[j].name != "\0")
                {
                    j++;
                }
                for(int k = j + 1; k > 0; k--)
                {
                    profiles[k].name =  profiles[k-1].name;
                    profiles[k].points = profiles[k-1].points;
                }
                profiles[0].name = name;
                profiles[0].points = points_i;
            }
            

        }
    }
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: playGame()                                      *
* Description: begins legit game play                       *
* Returns: void                                             *
* Preconditions: list should be populated with commands     *
*               and descriptions                            *
* Postconditions: User must choose exit menu option to save *
*               their name and points                       *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void playGame(List<Node<Data>>* list, int* points)
{
    int numQs = 0, runCount = 0, userSelection = 0, correctAnswer = 0;
    
    promptNumQs(&numQs);
    system("clear");
    for(int i = 0; i < numQs; i++)
    {
        *points += list->displayCommand(runCount, &userSelection, &correctAnswer);
        cout << "Points:" << *points << endl;
        
    }
    cout << "\nExit to save profile.\nWarning: A new game will overwrite your progress.\n\n";
    system("read -p 'Press Enter to Continue...' var");



}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: promptName()                                    *
* Description: prompts user for a name                      *
* Returns: void                                              *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void promptName(string* name)
{
    cout << "What is your name (NO SPACES): "; // asks for no spaces because name is stored in a string rather than a character array
    cin >> *name;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: promptNewCommand()                              *
* Description: prompts user for a desired command to add    *
*               to existing list                            *
* Returns: void                                             *
* Preconditions: list must exist                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void promptNewCommand(string* newCommand)
{
    cout << "What command would you like to add (NO SPACES): "; // asks for no spaces because newCommand is stored in a string rather than a character array
    cin >> *newCommand;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: promptDelCommand                                *
* Description: prompts user for a desired command to delete *
*               from list                                   *
* Returns: void                                             *
* Preconditions: list must exist                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void promptDelCommand(string* delCommand)
{
    cout << "What command would you like to delete (NO SPACES): ";
    cin >> *delCommand;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: promptNewDescription()                          *
* Description: prompts user for a description for new       *
*               command                                     *
* Returns: void                                             *
* Preconditions: command name must have already been        *
*               prompted                                    *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void promptNewDescription(string newCommand, char newDescription[200])
{
    cout << "Enter a description for " << newCommand << " (Enclosed in quotations): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(newDescription, 200);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: loadProfile()                                   *
* Description: checks profiles for existing user's saved    *
*               progress                                    *
* Returns: returns players points if found in profiles[]    *
*           returns -1 if player not found                  *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int loadProfile(profile profiles[], string name, int profileEntries)
{
    for(int i = 0; i < profileEntries; i++)
    {
        if(name == profiles[i].name)
        {
            return profiles[i].points;
        }
    }
    return -1;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: promptNumQs()                                   *
* Description: Asks user for how many commands to be quizzed*
*               on                                          *
* Returns: void                                              *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void promptNumQs(int* numQs)
{
    int count = 0;
    char numQsString[30];
    do
    {
        if(!count)
        {
         cout << "How many matching questions would you like (5-30): ";
        }
        else
        {
            cout << numQsString << " is not valid. Try again (5-30): ";
        }
    
        cin >> numQsString;
        *numQs = atoi((char*)numQsString);
        count++;
    } while(*numQs < 5 || *numQs > 30);
    

}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Function: updateProfilesDoc()                             *
* Description: updates profile csv file                     *
* Returns: void                                             *
* Preconditions:                                            *
* Postconditions:                                           *
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void updateProfilesDoc(fstream& iFile, profile profiles[], string name, int points, int profileEntries)
{
    if (profileEntries > 1) // avoids the for loop if there are no existing profiles, if not, ", 0" would be printed into the csv
    {
        for(int i = profileEntries - 1; i >= 0; i--)
        {
            if(i == 0 && name == "\0") // makes sure someone played before writing in a new entry AND applies a new line for the new entry if name=="\0" is false 
            iFile << profiles[i].name << ", " << profiles[i].points;
            else
            iFile << profiles[i].name << ", " << profiles[i].points << "\n";
        }
    }
    
    if(name != "\0") // makes sure someone played before writing in a new entry (test case: run program and exit without playing game)
    iFile << name << ", " << points;
    

}


template class List<Node<Data>>;

