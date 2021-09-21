#include "Hazard.h"
Hazard::Hazard()
{
	posY = 0;
	floor = 800;
	side = 1200;
	posX = 0;
	velocityX = -5;
	velocityY = 0;
	reset = 1000;
}
Hazard::Hazard(float y, float f, float s, float r)
{
	posY = y;
	floor = f;
	side = s;
	posX = side;
	velocityX = -5;
	velocityY = 0;
	reset = r;
}
float Hazard::updateX()
{
	if (posX < -150) posX = side + reset + (rand() % 5) * 150;
	return posX += velocityX;
}
float Hazard::updateY()
{
	//if ((velocityY += gravity) + posY >= floor) velocityY *= -1;
	return posY += velocityY;
}
float Hazard::getX()
{
	return posX;
}
float Hazard::getY()
{
	return posY;
}
void Hazard::setX(float x)
{
	posX = x;
}
void Hazard::setVX(float x)
{
	velocityX = x;
}
