#include "TurretOverseer.h"

TurretOverseer::TurretOverseer()                            // Loads textures.
{
	basicTexture.loadFromFile("gfx/Turret1CE2.png");
	secondTexture.loadFromFile("gfx/Turret2.png");
	thirdTexture.loadFromFile("gfx/Turret3.png");
	bulletTexture.loadFromFile("gfx/BasicBullet.png");
}


void TurretOverseer::update(float dt)
{

	// Updates turrets
	for (int i = 0; i < turret.size(); i++)
	{
		turret[i].update(dt);
	}

	// Updates bullets
	for (int i = 0; i < bullet.size(); i++)
	{
		if (bullet[i].aliveCheck() == true)
		{
			bullet[i].update(dt);
		}
	}

	// Checks all turrets to see if the mouse is over any of them. Uses origin coords so that if the turret turns, you can still click on it,
	for (int t = 0; t < turret.size(); t++)
	{
		if (input->getMouseX() > turret[t].returnOx() && input->getMouseX() < turret[t].returnOx() + 128 && input->getMouseY() > turret[t].returnOy() && input->getMouseY() < turret[t].returnOy() + 128)
		{
			mouseColliding = true;

			// Sets position of range circle to directly in the centre of the turret
			if (turret[t].returnTurretType() == 1)
			{
				infoBox.rangeCircle.setPosition(turret[t].returnOx() - 236, turret[t].returnOy() - 236);
			}
			if (turret[t].returnTurretType() == 2)
			{
				infoBox.rangeCircle.setPosition(turret[t].returnOx() - 436, turret[t].returnOy() - 436);
			}
			if (turret[t].returnTurretType() == 3)
			{
				infoBox.rangeCircle.setPosition(turret[t].returnOx() - 136, turret[t].returnOy() - 136);
			}


			// Takes in information about the turret that the player is hovering over, so the handleInput function can deal with this part.
			tType = turret[t].returnTurretType();
			t = turret.size();
		}
		else
		{
			mouseColliding = false;
		}
	}



	// Updates infoBox
	if (infoBox.aliveStatus() == true)
	{
		infoBox.update(dt);
	}
}
void TurretOverseer::handleInput(float dt)
{

	// Checks if left mouse down and mouse is touching turret.
	if (input->isLeftMouseDown() && mouseColliding == true)
	{
		clicked = true;
		infoBox.box.setPosition(input->getMouseX(), input->getMouseY());
		infoBox.setType(tType);
		infoBox.setAlive(true);
	}

	// Checks if clicked, then dissapears the infobox if player presses right mouse button.
	if (input->isRightMouseDown() && clicked == true)
	{
		clicked = false;
		infoBox.setAlive(false);
	}
}

void TurretOverseer::render(sf::RenderWindow* window)        // Renders all of the turrets and bullets that are currently in play, and infoBox/rangeCircle.
{
	for (int i = 0; i < bullet.size(); i++)
	{
		if (bullet[i].aliveCheck() == true)
		{
			window->draw(bullet[i]);
		}
	}

	for (int i = 0; i < turret.size(); i++)
	{
		window->draw(turret[i]);
	}

	if (infoBox.aliveStatus() == true)
	{
		window->draw(infoBox.box);
		window->draw(infoBox.text);
		window->draw(infoBox.text2);
		window->draw(infoBox.text3);
		window->draw(infoBox.rangeCircle);
	}
}

void TurretOverseer::spawnTurret(int x, int y, int t)        // Spawns new turrets at x and y, also keeps a hold of origin of the turrets, since they turn and
{                                                            // change their origin coords often. Also decides on type of turret to spawn.
	if (t == 1)
	{
		turret.push_back(BaseTurret());
		turret[turret.size() - 1].setPosition(x, y);
		turret[turret.size() - 1].setTexture(&basicTexture);
		turret[turret.size() - 1].setTurretType(1);
		turret[turret.size() - 1].setOG(x, y);
	}
	if (t == 2)
	{
		turret.push_back(BaseTurret());
		turret[turret.size() - 1].setPosition(x, y);
		turret[turret.size() - 1].setTexture(&secondTexture);
		turret[turret.size() - 1].setTurretType(2);
		turret[turret.size() - 1].setOG(x, y);
	}
	if (t == 3)
	{
		turret.push_back(BaseTurret());
		turret[turret.size() - 1].setPosition(x, y);
		turret[turret.size() - 1].setTexture(&thirdTexture);
		turret[turret.size() - 1].setTurretType(3);
		turret[turret.size() - 1].setOG(x, y);
	}

}

void TurretOverseer::setTarget(int x, int y, int t)          // Sets the target for the turret to aim towards.
{
	diffx = turret[t].getPosition().x - x;
	diffy = turret[t].getPosition().y - y;
	angle = atan2(diffy, diffx) * (180 / 3.141592);
	turret[t].setRotation(angle - 90);

	auto offset = centre - turret[t].getOrigin();
	turret[t].setOrigin(centre);
	turret[t].move(offset);
}

void TurretOverseer::setAim(bool aim, int t)                 // Sets boolean targeting variable for the input turret.
{
	if (aim == true)
	{
		turret[t].Targeting();
	}
	else
	{
		turret[t].NotTargeting();
	}
}

void TurretOverseer::doneFiring(int t)                       // Sets the turrets firing variable to false, after a shot has been taken.
{
	turret[t].takenShot();
}

bool TurretOverseer::isTargeting(int t)                      // Returns whether the turret is currently aiming at anything or not.
{
	if (turret[t].amItargeting() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool TurretOverseer::isFiring(int t)                         // Returns if the turret is ready to fire.
{
	if (turret[t].amIfiring() == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}

float TurretOverseer::checkDamage(int t)                     // Checks damage of bullets that the turret fires.
{
	return turret[t].bulletDamage();
}

float TurretOverseer::returnRange(int t)                     // Returns range of the turret.
{
	return turret[t].returnRange();
}

void TurretOverseer::spawnBullet(int x, int y, float dmg)    // Spawns bullet at x and y, first reusing an already inactive one first. Sets damage of the bullet too.
{
	bullet.push_back(Bullet());
	bullet[bullet.size() - 1].setPosition(x, y);
	bullet[bullet.size() - 1].setTexture(&bulletTexture);
	bullet[bullet.size() - 1].setDamage(dmg);
}

void TurretOverseer::setBulletTarget(int x, int y, int b)     // Sets bullet coords to aim towards.
{
	bullet[b].setTarget(x, y);
}
