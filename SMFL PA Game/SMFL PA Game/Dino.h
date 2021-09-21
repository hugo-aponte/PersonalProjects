#pragma once
#include <math.h>
class Dino {
private:
	float velocity;
	float posY;
	float gravity;
	float floor;
public:
	Dino(float y);
	float fall();
	void setY(float y);
	float getY();
	void jump();
	float getVelocity();
};
float getDirection(float x, float y);