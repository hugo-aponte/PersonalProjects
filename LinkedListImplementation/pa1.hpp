/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
|																			  |
|	Hugo Aponte																  |
|	CptS 223;               											 	  |
|	PA8																		  |
|	9/14/20																      |
|                                                                             |
| Description: 	This file stores all function declarations used by main       |
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifndef PA1_HPP
#define PA1_HPP
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <istream>
#include "Data.hpp"
#include "List.hpp"
#include "Node.hpp"

using namespace std;

struct profile
{
    string name;
    int points;
};

int mainMenu();
void gameRules();
void loadListFromFile(List<Node<Data>>* list, fstream& iFile);
void playGame(List<Node<Data>>* list, int* points);
void promptName(string* name);
void promptNumQs(int* numQs);
void loadProfilesFromFile(profile profiles[], fstream& iFile);
int checkNumEntries(fstream& iFile);
void updateProfilesDoc(fstream& iFile, profile profiles[], string name, int points, int profileEntries);
int loadProfile(profile profiles[], string name, int profileEntries);
void promptNewCommand(string* newCommand);
void promptDelCommand(string* newCommand);
void promptNewDescription(string newCommand, char newDescription[]);
void updateCommandsDoc(fstream& iFile, List<Node<Data>>* list, string newCommand, char newDescription[]);




#endif
