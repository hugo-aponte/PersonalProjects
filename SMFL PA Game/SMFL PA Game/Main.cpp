
/*******************************************************************************************
* (Group 21)																			   *
* Programmers: Evan Kimmerlein, Zach Griswold, Hugo Aponte, Tatumn Laughery				   *
* Class: CptS 122, Spring, 2020;														   *
* Programming Assignment: PA1															   *
* Date: May 1st, 2020																	   *
*																						   *
*	Game: Dino Runner (Like the Google Chrome game when you don't have internet!)		   *
*																						   *
*		Instructions are in the read me file.											   *	
********************************************************************************************/


#include <SFML/Graphics.hpp>
//#include <math.h>
#include "Dino.h"
#include "Hazard.h"
#include "FallingHazard.h"
#include "test.h"
#include <iostream>
#include <chrono> // for score
#include <string> // for score

using namespace sf;
int main() {
	srand(time(NULL));
	int height = 64;
	int tick = 0;
	int difficulty = 100000;

	// for score setup
	int time = 1;
	int distance = 0;
	bool cReset = false;


	float windowX = 1024;//800;
	float windowY = 512;//600;

	// uncomment the next two lines and comment everything else below to use this

	//test tester; 
	//tester.test_all();


	//											~~~TEXTURES, SPRITES AND OBJECT DECLARATION~~~

	// box that holds score
	RectangleShape box(Vector2f(300, 85));
	Texture scoreBG;

	if (!scoreBG.loadFromFile("score.png"))
		std::cout << "Error loading \"score.png\"" << std::endl;

	box.setTexture(&scoreBG);
	box.setPosition(Vector2f(10, 10));		// top left corner]

	sf::Font font; // preloaded font
	if (!font.loadFromFile("SLB.ttf"))
	{
		std::cout << "COULD NOT LOAD FILE..." << std::endl;
	}
	Text text;
	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(Color::Black);
	text.setPosition(Vector2f(35, 30));

	//Setting up Dino texture
	Texture dinoTexture;
	if (!dinoTexture.loadFromFile("dino-normal.png")) std::cout << "Dino Texture failed to load";
	Sprite dinoSprite;
	dinoSprite.setTexture(dinoTexture);
	dinoSprite.setScale(4, 4);
	dinoSprite.setPosition(300, 300);

	//Setting up sky textures and sprites
	Texture skyTexture;
	if (!skyTexture.loadFromFile("sky.png")) std::cout << "Sky image falied to load";
	Sprite skySprite;
	skySprite.setTexture(skyTexture);
	skySprite.setPosition(0, 0);
	skySprite.setScale(Vector2f(8.f, 8.f));

	Sprite skySprite2;
	skySprite2.setTexture(skyTexture);
	skySprite2.setPosition(skyTexture.getSize().x * 8, 0);
	skySprite2.setScale(Vector2f(8.f, 8.f));

	//Setting up forground texture and sprite
	Texture foregroundTexture;
	if (!foregroundTexture.loadFromFile("dino-foreground.png")) std::cout << "Foreground image falied to load";
	Sprite foregroundSprite;
	foregroundSprite.setTexture(foregroundTexture);
	foregroundSprite.setPosition(0, 0);
	foregroundSprite.setScale(Vector2f(8.f, 8.f));

	//Setting up various Dino movement textures and sprites
	Texture dinoRunTexture1;
	dinoRunTexture1.loadFromFile("dino-run1.png");
	Texture dinoRunTexture2;
	dinoRunTexture2.loadFromFile("dino-run2.png");
	Texture dinoCrouch;
	dinoCrouch.loadFromFile("dino-crouch.png");
	Sprite dinoRunSprite;
	dinoRunSprite.setTexture(dinoRunTexture1);
	dinoRunSprite.setScale(4, 4);

	//Setting up cacti textures and sprites
	Texture cactusTexture;
	cactusTexture.loadFromFile("cactus1.png");
	Texture cactus2Texture;
	cactus2Texture.loadFromFile("cactus2.png");
	Sprite cactusSprite;
	cactusSprite.setTexture(cactusTexture);
	cactusSprite.setScale(4, 4);
	Sprite cactus2Sprite;
	cactus2Sprite.setTexture(cactus2Texture);
	cactus2Sprite.setScale(4, 4);

	//Setting up commet texture and sprite
	Texture cometTexture;
	cometTexture.loadFromFile("comet.png");
	Sprite cometSprite;
	cometSprite.setTexture(cometTexture);
	cometSprite.setScale(4, 4);

	Sprite bounceSprite;
	bounceSprite.setTexture(cometTexture);
	bounceSprite.setScale(4, 4);

	Dino hitbox(windowY);	//This is the hitbox and physics object for the player

	Hazard hazard(512, windowY, windowX, 100);		//Pysics and hitbox for the first cacti

	Hazard cactus2(512, windowY, windowX, 100);		//Physics and hitbox for second cacti
	cactus2.setX(2000);			//Offset start

	Hazard comet(462, windowY, windowX, 10000);		//Pysics and hitbox for flying comet
	comet.setX(20000);			//Offset start
	comet.setVX(-8);			//change comet speed

	FallingHazard bounce(200, windowY, windowX, 10000);		//Physics and hitboc for falling comet
	//bounce.setX(18000);
	bounce.setX(8000);			//Offset start
	//bounce.setVX(-6);		

	RectangleShape dino(Vector2f(32.f, 32.f));		//This an unused object that was for initial testing - it is no longer drawn
	dino.setFillColor(Color(125, 250, 125));
	dino.setPosition(windowX / 3, hitbox.getY() - 32);

	//												~~~END OF OBJECT SET UP~~~


	sf::RenderWindow window(sf::VideoMode(windowX, windowY), "Dino Runner");	//Set up window
	Vector2u size = window.getSize();

	window.setFramerateLimit(144);			//Limit FPS/tick speed to 144 ticks per second

	Texture startTex;
	if (!startTex.loadFromFile("start.png")) std::cout << "Start image falied to load";
	Sprite startSprite;
	startSprite.setScale(1, 1);
	startSprite.setPosition(0, 0);
	startSprite.setTexture(startTex);

	Texture endTex;
	if (!endTex.loadFromFile("gameover.png")) std::cout << "Start image falied to load";
	Sprite endSprite;
	endSprite.setScale(1, 1);
	endSprite.setPosition(0, 0);
	endSprite.setTexture(endTex);

	//													   ~~~GAME LOOP~~~
	bool wait = true, wait2 = false;
	int flag = 0;
	while (window.isOpen())
	{
		if (wait)
		{
			window.draw(startSprite); //Draws the starting screen
			window.display();
		}
		sf::Event event;
		while (window.pollEvent(event))//waits for any button to be pressed
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
				wait = false;


		}

		if (!wait && !wait2)
		{
			tick++;							//keep track of tick speed
			window.clear();					//clear previous screen

			// score setup
			if (cReset)
			{
				time = 1;
				cReset = false;
			}
			else
				time += 1; // random increment
			distance = time * 3;



			//Sky movement
			if (skySprite.getPosition().x <= -2 * windowX) {			//If sky object has passed off screen
				skySprite.setPosition(skySprite2.getPosition().x + skyTexture.getSize().x * 8 - 8, 0);	//teleport to edge of second sky object
			}
			else {
				skySprite.setPosition(Vector2f(skySprite.getPosition().x - (tick + difficulty) / difficulty, 0));	//move sky object left
			}
			if (skySprite2.getPosition().x <= -2 * windowX) {			//If seconf sky object has passed off screen
				skySprite2.setPosition(skySprite.getPosition().x + skyTexture.getSize().x * 8 - 8, 0);	//teleport to edge of first sky object
			}
			else {
				skySprite2.setPosition(Vector2f(skySprite2.getPosition().x - (tick + difficulty) / difficulty, 0));	//move sky object left
			}

			window.draw(skySprite);		//Draw sky1
			window.draw(skySprite2);	//Draw sky2


			//Foreground movement (A much better method than used for sky as it only uses 1 sprite)
			if (foregroundSprite.getPosition().x <= -2 * windowX) {	//If off screen
				foregroundSprite.setPosition(0, 0);		//reset to be back on screen
			}
			else {
				foregroundSprite.setPosition(foregroundSprite.getPosition().x - (tick + difficulty) / (difficulty / 5), 0);	//move left
			}
			window.draw(foregroundSprite);			//Draw foreground
			foregroundSprite.setPosition(foregroundSprite.getPosition().x + foregroundTexture.getSize().x * 8, 0);	//Shift foreground right exeactly the width of the image
			window.draw(foregroundSprite);			//Draw foreground again
			foregroundSprite.setPosition(foregroundSprite.getPosition().x - foregroundTexture.getSize().x * 8, 0);	//Shift back

			//Dino Leg Movement

			if ((tick / 19) % 2) {	//rapidly switch on and off
				dinoRunSprite.setTexture(dinoRunTexture1);								//one foot...
			}
			else dinoRunSprite.setTexture(dinoRunTexture2);
			if (hitbox.getY() != windowY) dinoRunSprite.setTexture(dinoTexture);		//other foot...

			//Dino Crouch handling
			if (Keyboard::isKeyPressed(Keyboard::Up)) hitbox.jump();		//Jump
			if (Keyboard::isKeyPressed(Keyboard::Down)) {					//Crouch
				//dino.setSize(Vector2f(32.f, 16.f));
				height = 32;												//lower height
				dinoRunSprite.setTexture(dinoCrouch);						//crouch texture
				dinoRunSprite.setPosition(windowX / 3, hitbox.fall());		//run falling physics
			}
			else {
				//dino.setSize(Vector2f(32.f, 32.f));
				height = 64;												//set height to normal
				dinoRunSprite.setPosition(windowX / 3, hitbox.fall());		//run falling physics
			}

			//Hazard Movement
			cactusSprite.setPosition(hazard.updateX(), hazard.updateY() - 128 - 16);									//move cactus 1
			if (abs(hazard.getY() - hitbox.getY()) < height && abs(hazard.getX() - windowX / 3 - 32) < 64) flag = 1;			//check of collision - IMPORTANT!!!!! GAME OVER FUNCTION HERE
			if (150 < hazard.getX() - cactus2.getX() && hazard.getX() - cactus2.getX() < 400) hazard.setX(-1000);				//Ensure cacti aren't an impossible distance from each other
			if (150 < cactus2.getX() - hazard.getX() && cactus2.getX() - hazard.getX() < 400) cactus2.setX(-1000);
			cactus2Sprite.setPosition(cactus2.updateX(), hazard.updateY() - 128 - 16);									//Move cactus 2
			if (abs(cactus2.getY() - hitbox.getY()) < height && abs(cactus2.getX() - windowX / 3 - 32) < 64) flag = 1;	//check of collision - IMPORTANT!!!!! GAME OVER FUNCTION HERE
			//if (0 < cactus2.getX() - hazard.getX() < 10) hazard.setX(-1000);	//Space out cacti

			cometSprite.setPosition(comet.updateX(), comet.updateY() - 128 - 16);												//Move flying comet
			if (abs(comet.getY() - hitbox.getY()) < height && abs(comet.getX() - windowX / 3 - 32) < 64) flag = 1;		//check of collision - IMPORTANT!!!!! GAME OVER FUNCTION HERE

			bounceSprite.setPosition(bounce.updateX(), bounce.updateY() - 128 - 16);											//Move bouncing comet
			if (abs(bounce.getY() - hitbox.getY()) < height && abs(bounce.getX() - windowX / 3 - 32) < 64) flag = 1;		//check of collision - IMPORTANT!!!!! GAME OVER FUNCTION HERE
			//bounceSprite.setRotation(getDirection(bounce.get));

												//Draw hazards and Platyer
			window.draw(cactusSprite);
			window.draw(cactus2Sprite);
			window.draw(cometSprite);
			window.draw(bounceSprite);
			window.draw(dinoRunSprite);


			std::string d = std::to_string(distance);
			text.setString(d + " m");
			window.draw(box);
			window.draw(text);
			window.display();

			while (flag)
			{
				wait2 = true;
				window.clear();
				window.draw(endSprite);
				window.draw(box);
				window.draw(text);
				window.display();

				while (window.pollEvent(event))
					if (event.type == Event::Closed) window.close();
				if (Keyboard::isKeyPressed(Keyboard::Q))
				{
					if (Event::KeyReleased) window.close();
					return 0;
				}

				if (Keyboard::isKeyPressed(Keyboard::R))
				{
					if (Event::KeyReleased)
					{
						wait2 = false;
						wait = true;
						tick = 0;
						hazard.setX(-1000);
						comet.setX(20000);
						cactus2.setX(2000);
						bounce.setX(8000);
						window.clear();
						flag = 0;
						cReset = true;
					}
				}
			}
		}
	}

	return 0;
}