#pragma once
#include "Hazard.h"
class FallingHazard : public Hazard {
private:
	float gravity;		//Units of acceleration downwards
public:
	FallingHazard(float y, float f, float s, float r);
	float updateY();	//Used to update and return the Y position of the dino taking account for gravitational acceleration
};