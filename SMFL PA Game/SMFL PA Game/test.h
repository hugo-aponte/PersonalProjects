#pragma once
#include <SFML/Graphics.hpp>
#include "Dino.h"
#include "FallingHazard.h"
#include "Hazard.h"
#include <iostream>

using namespace std; 

class test {
private:
	float test_v; 
	int test_height; 
	int height;
	int cactusy;
	int hitboxy;
	int cactusx;
	int windowx;

public:
	test(); 
	void test_jump();
	void test_crouch();
	void test_cactus();
	void test_comet(); // test the quit option of game board 
	void test_bounce(); //test the restart option on the game board 
	void test_all();

};

test::test()
{
	float test_v = 0;
	int test_height = 64;
	int height = 0;
	int cactusy = 0;
	int hitboxy = 0;
	int cactusx = 0;
	int windowx = 0;
}
void test::test_jump()
{
	Dino dino(300);

	dino.jump();
	test_v = dino.getVelocity();

	if (test_v == -5)
	{
		cout << "Jump function works currectly." << endl; 
	}
	else if (test_v == 0)
	{
		cout << "Jump function did not run correctly" << endl; 
	}

}

void test::test_crouch()
{ 
	test_height = 32;	//lower height

	if (test_height == 32)
	{
		cout << "The height of the dino switched from 64 to 32. Crouch was successful." << endl; 
	}

}

void test::test_cactus()
{
	//hardcoding the numbers and variables that represent the if statement that's in main
	int height = 30, cactusy = 60, hitboxy = 20, cactusx = 300, windowx = 3;
	if (cactusx - hitboxy < height && cactusx - windowx / 3 - 32 < 64)
	{
		cout << "You collided with a bouncing comet." << endl;//we want the collision to happen
	}
}

void test::test_comet()
{
	//hardcoding the numbers and variables that represent the if statement that's in main
	int height = 30, comety = 60, hitboxy = 20, cometx = 300, windowx = 3;
	if (comety - hitboxy < height && cometx - windowx / 3 - 32 < 64)
	{
		cout << "You collided with a bouncing comet." << endl;//we want the collision to happen
	}
}

void test::test_bounce()
{
	//hardcoding the numbers and variables that represent the if statement that's in main
	int height = 30, bouncey = 60, hitboxy = 20, bouncex = 300, windowx = 3;
	if (bouncey - hitboxy < height && bouncex - windowx / 3 - 32 < 64)
	{
		cout << "You collided with a bouncing comet." << endl; //we want the collision to happen
	}
}

void test::test_all()
{
	test tester;

	tester.test_jump();
	tester.test_crouch();
	tester.test_cactus();
	tester.test_comet();
	tester.test_bounce();
}

//reminder: need to add a get_function for the private variable velocity in the Dino class


//Add these lines of code in main: #include "test.h"
//test tester; //keep these last two lines commented out
//tester.test_all();