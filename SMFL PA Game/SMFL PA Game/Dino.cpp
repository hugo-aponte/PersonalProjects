#include "Dino.h"
Dino::Dino(float y)
{
	velocity = 0;
	posY = y;
	gravity = .1;
	floor = y;
}

float Dino::getVelocity()
{
	return velocity;
}

float Dino::fall()
{
	if (posY + velocity <= floor) {
		velocity += gravity;
		posY += velocity;
	}
	else {
		posY = floor;
	}
	return posY - 32*4;
}
void Dino::setY(float y)
{
	posY = y;
}
float Dino::getY()
{
	return posY;
}
void Dino::jump()
{
	if(posY == floor) velocity = -5;
}
float getDirection(float x, float y)
{
	int X = x / sqrt(x * x + y * y);
	int Y = y / sqrt(x * x + y * y);
	return atanf(Y/X);
}