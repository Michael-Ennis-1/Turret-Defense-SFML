#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud)
{
	window = hwnd;
	input = in;
	gameState = gs;
	audio = aud;

	// Sets position and texture of turret templates
	Type1TT.setCoords(0, 927);
	Type1TT.setText(1);
	Type2TT.setCoords(200, 927);
	Type2TT.setText(2);
	Type3TT.setCoords(400, 927);
	Type3TT.setText(3);

	// Sets input for classes that use it
	Type1TT.setInput(in);
	Type2TT.setInput(in);
	Type3TT.setInput(in);
	TOverseer.setInput(in);
	menu.setInput(in);
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	// Handles input of all related classes.
	if (start == true && pause == false && end == false)
	{
		TOverseer.handleInput(dt);
		Type1TT.handleInput(dt);
		Type2TT.handleInput(dt);
		Type3TT.handleInput(dt);
	}
	if (start == false && end == false)
	{
		menu.handleInput(dt);
	}

	// This part pauses the game if the user presses space, and continues if the user press P.
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		pause = true;
	}
	if (input->isKeyDown(sf::Keyboard::P))
	{
		pause = false;
	}
}

// Update game objects
void Level::update(float dt)
{
	if (start == true && pause == false && end == false)
	{
		// Checks if the player wants a turret placed, then places one at the required position, depending on what turret type they want.
		// Also checks with the EOverseer to make sure the player has enough gold to purchase a turret.
		if (Type1TT.spawnRequired() == true && EOverseer.getGold() >= 50)
		{
			TOverseer.spawnTurret(input->getMouseX() - 64, input->getMouseY() - 64, 1);
			Type1TT.spawnComplete();
			EOverseer.setGold(EOverseer.getGold() - 50);
		}
		if (Type2TT.spawnRequired() == true && EOverseer.getGold() >= 60)
		{
			TOverseer.spawnTurret(input->getMouseX() - 64, input->getMouseY() - 64, 2);
			Type2TT.spawnComplete();
			EOverseer.setGold(EOverseer.getGold() - 60);
		}
		if (Type3TT.spawnRequired() == true && EOverseer.getGold() >= 70)
		{
			TOverseer.spawnTurret(input->getMouseX() - 64, input->getMouseY() - 64, 3);
			Type3TT.spawnComplete();
			EOverseer.setGold(EOverseer.getGold() - 70);
		}

		// Checks if template turret is colliding with placed turret, so player cannot put two turrets ontop of each other
		for (int i = 0; i < TOverseer.turret.size(); i++)
		{
			if (Collision::checkBoundingBox(&Type1TT, &TOverseer.turret[i]))
			{
				Type1TT.collisionResponse();
				Colliding++;
			}
			if (Collision::checkBoundingBox(&Type2TT, &TOverseer.turret[i]))
			{
				Type2TT.collisionResponse();
				Colliding++;
			}
			if (Collision::checkBoundingBox(&Type3TT, &TOverseer.turret[i]))
			{
				Type3TT.collisionResponse();
				Colliding++;
			}
		}
		if (Colliding == 0)
		{
			Type1TT.resetCollision();
			Type2TT.resetCollision();
			Type3TT.resetCollision();
		}
		// Reseting colliding variable so that if the Template is not touching any other turret, then it can still spawn turrets.
		Colliding = 0;

		// This part runs through all the enemies and bullets and checks if any of them have collided, and only checks those that are not dead.
		for (int e = 0; e < EOverseer.enemy.size(); e++)
		{
			for (int b = 0; b < TOverseer.bullet.size(); b++)
			{
				if (EOverseer.enemy[e].collectStatus() == false)
				{
					if (Collision::checkBoundingBox(&TOverseer.bullet[b], &EOverseer.enemy[e]))
					{
						EOverseer.damage(TOverseer.bullet[b].hitDamage(), e);
						TOverseer.bullet[b].collisionResponse();
					}
				}
			}
		}

		// Runs through every turret and enemy to check their distance, then if any are within range of the turret, they become the new target. Also makes sure that a
		// turret cannot target two different enemies at the same time.
		if (TOverseer.turret.size() > 0 && EOverseer.enemy.size() > 0)
		{
			for (int t = 0; t < TOverseer.turret.size(); t++)
			{
				for (int i = 0; i < EOverseer.enemy.size(); i++)
				{
					if (TOverseer.isTargeting(t) == false)
					{

						// Checks that the enemy that is being targeted is in range.
						x = EOverseer.enemy[i].getPosition().x - TOverseer.turret[t].getPosition().x;
						y = EOverseer.enemy[i].getPosition().y - TOverseer.turret[t].getPosition().y;

						x = x * x;
						y = y * y;

						distance = x + y;
						distance = sqrt(distance);

						if (distance < TOverseer.returnRange(t) && EOverseer.enemy[i].collectStatus() == false)
						{

							TOverseer.setAim(true, t);

							// Checks if turret is ready to fire, then sets up bullets and tells the turret class that it has fired so animations can begin.
							if (TOverseer.isFiring(t) == true)
							{
								TOverseer.setTarget(EOverseer.enemy[i].getPosition().x + 32, EOverseer.enemy[i].getPosition().y + 32, t);
								TOverseer.spawnBullet(TOverseer.turret[t].getPosition().x - 16, TOverseer.turret[t].getPosition().y - 16, TOverseer.checkDamage(t));
								TOverseer.setBulletTarget(EOverseer.enemy[i].getPosition().x + 22, EOverseer.enemy[i].getPosition().y + 22, TOverseer.bullet.size() - 1);
								TOverseer.doneFiring(t);
							}
						}
					}
				}

				// Resets whether or not a turret is aiming at something
				TOverseer.setAim(false, t);
			}
		}


		// Updates the Managers/Templates.
		Type1TT.update(dt);
		Type2TT.update(dt);
		Type3TT.update(dt);
		EOverseer.update(dt);
		TOverseer.update(dt);
	}

	// Lets the game know when the player touches the start button, that it can begin playing the game.
	if (menu.returnStart() == true)
	{
		start = true;
	}

	if (start == false && end == false)
	{
		menu.update(dt);
	}

	// Checks with the EOverseer, which handles HP and Enemies as well as other player shown variables, that the game has ended and how it has ended.
	if (EOverseer.hasGameEnded() == true)
	{
		end = true;
		start = false;
		if (EOverseer.gameWon() == true)
		{
			menu.gameEnd(true);
		}
		if (EOverseer.gameWon() == false)
		{
			menu.gameEnd(false);
		}
	}
}

// Render level
void Level::render()
{
	beginDraw();

	if (start == true && pause == false && end == false)
	{

		// Start of Managers rendering their objects and map, if the game is still playing.
		map.render(window);
		EOverseer.render(window);
		TOverseer.render(window);
		window->draw(Type1TT);
		window->draw(Type2TT);
		window->draw(Type3TT);
	}
	if (start == false)
	{
		// Renders the menu of the game hasn't started, and renders the EOverseer for scores and HP and other variables if it has ended.
		menu.render(window);
		if (end == true)
		{
			EOverseer.render(window);
		}
	}

	// Sets the game to pause if required, otherwise sets it to play.
	if (pause == true)
	{
		menu.setPause(true);
		menu.render(window);
	}
	else
	{
		menu.setPause(false);
	}


	endDraw();
}

