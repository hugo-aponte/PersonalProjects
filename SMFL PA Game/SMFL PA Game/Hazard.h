#pragma once
#include "Dino.h"
#include <random>
class Hazard {			//Standard obstical such as comets and cacti
protected:
	float posX;
	float posY;
	float velocityX;
	float velocityY;
	float floor;
	float side;
	float reset;		//How far away the object should reset to after cleared
public:
	Hazard();
	Hazard(float y, float f, float s, float r);
	float updateX();	//Update and return the X position
	float updateY();	//Update and return the Y position
	float getX();		
	float getY();
	void setX(float x);		//Used to set the starting point for the hazards
	void setVX(float x);	//Used to manipulate the side velocity of the hazard
};