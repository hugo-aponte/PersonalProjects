/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This PA represents a game that challenges the user to         |
|                identify the correct description relative to a prompted      |
|                command. The program uses a linked list class, node class,   |
|                and data class to store the corresponding commands and       |
|                descriptions from a csv file. The players game is saved      |
|                to another csv file.                                         |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "pa1.hpp"
#include "Data.hpp"
#include "List.hpp"
#include "Node.hpp"

int main()
{
    srand(time(NULL));
    List<Node<Data>>* list = new List<Node<Data>>();
    fstream iFile;

    string name, newCommand = "", delCommand = "";
    char newDescription[200];
    int points = 0, profileEntries = 0;
    bool found = false;

    iFile.open("commands.csv", ios::in);
    loadListFromFile(list, iFile);
    iFile.close();

    iFile.open("profiles.csv", ios::in);
    profileEntries = checkNumEntries(iFile);
    iFile.open("profiles.csv", ios::in);
    
    profile profiles[profileEntries + 1] = {{"\0", 0}}; // +1 makes sure there is additional space to add each profile at the beginning
    
    loadProfilesFromFile(profiles, iFile);
    iFile.close();


    // list->testPrint(); //used to assure list is working

    int option = 0;
    while(option != 6)
    {       
        system("clear");
        option = mainMenu();
        switch(option)
        {
            case 1:
                gameRules();
                break;
            case 2:
                promptName(&name);
                playGame(list, &points);

                break;
            case 3:
                promptName(&name);
                points = loadProfile(profiles, name, profileEntries + 1);
                if(points == -1) // checks whether name was found; loadProfile() will return -1 if not
                {
                    cout << "Invalid name. Select 3 in menu to try again\n";
                }
                else
                {
                    cout << name << "'s points: " << points << endl;
                    playGame(list, &points);
                }
            break;
            case 4:
                
                promptNewCommand(&newCommand);
                promptNewDescription(newCommand, newDescription);
                list->insertCommand(newCommand, newDescription);
            break;
            case 5:
                do
                {
                    if(found)
                    cout << "Invalid command... ";

                    promptDelCommand(&delCommand);
                    found = true;
                } while (!list->findCommand(delCommand));
                list->remove(delCommand);                
                cout << delCommand << " successfully deleted!\n";
                system("read -p 'Press Enter to Continue...' var");
            break;
            case 6:
                iFile.open("profiles.csv", ios::out);
                updateProfilesDoc(iFile, profiles, name, points, profileEntries);
                iFile.close();
                if(newCommand != "" || delCommand != "")
                {
                    iFile.open("commands.csv", ios::out);
                    updateCommandsDoc(iFile, list, newCommand, newDescription);
                    iFile.close();
                }
            break;

        }
    }
 }