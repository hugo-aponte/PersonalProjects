#include "FallingHazard.h"
FallingHazard::FallingHazard(float y, float f, float s, float r)
{
	posY = y;
	floor = f;
	side = s;
	posX = side;
	velocityX = -6;
	velocityY = 0;
	gravity = 0.1;
	reset = r;
}
float FallingHazard::updateY()
{
	if ((velocityY += gravity) + posY >= floor) velocityY *= -1;	//Accerate and check bounce if hits floor
	return posY += velocityY;										//move and return
}