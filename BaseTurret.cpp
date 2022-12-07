#include "BaseTurret.h"

BaseTurret::BaseTurret()                 // Sets up turret texture
{
	setSize(sf::Vector2f(128, 128));
	setCollisionBox(sf::FloatRect(0, 0, 128, 128));
	setTextureRect(sf::IntRect(0, 0, 128, 128));

	shoot.addFrame(sf::IntRect(0, 0, 128, 128));
	shoot.addFrame(sf::IntRect(128, 0, 128, 128));
	shoot.addFrame(sf::IntRect(256, 0, 128, 128));
	shoot.addFrame(sf::IntRect(384, 0, 128, 128));
	shoot.addFrame(sf::IntRect(512, 0, 128, 128));
	shoot.setFrameSpeed(1.0f / 20.0f);
}

void BaseTurret::update(float dt)
{

	// This part checks that the reload timer has beaten the reload time of a specific turret, then sets the turret to begin the firing phase.
	if (reloadTimer.getElapsedTime() >= reload)
	{
		Firing = true;
		animationTimer.restart();
	}

	// This part checks for animations to begin, then starts animating the shot being taken. After the animation has been complete, it sets back to original
	// graphic and resets the variable for the next shot.
	if (animGo == true)
	{
		shoot.animate(dt);
		setTextureRect(shoot.getCurrentFrame());

		if (animationTimer.getElapsedTime() >= animTime)
		{
			setTextureRect(sf::IntRect(0, 0, 128, 128));
			animGo = false;
		}
	}
}

void BaseTurret::Targeting()             // Sets aim variable to true, used if the turret is aiming at something.
{
	Aiming = true;
}

void BaseTurret::NotTargeting()          // Sets aim variable to false, used so that the turret can swap targets.
{
	Aiming = false;
}

void BaseTurret::takenShot()             // Sets firing variable to false, used when the turret has already fired. Also restarts the reload timer and begins the
{                                        // firing animation.
	Firing = false;
	reloadTimer.restart();
	animGo = true;
}

void BaseTurret::setOG(int x, int y)     // Sets the origin coordinates of the turret, since their origin changes when the turret rotates.
{
	oX = x;
	oY = y;
}

void BaseTurret::setTurretType(int type) // Sets type of turret, changing bullet damage, range and reload
{
	tType = type;
	if (type == 1)
	{
		damagePerShot = 2;
		range = 300;
		reload = sf::milliseconds(2500);
	}
	if (type == 2)
	{
		damagePerShot = 5;
		range = 500;
		reload = sf::milliseconds(7500);
	}
	if (type == 3)
	{
		damagePerShot = 1;
		range = 200;
		reload = sf::milliseconds(1000);
	}
}

bool BaseTurret::amItargeting()          // Returns aiming variable, to check if the turret aiming at something
{
	return Aiming;
}

bool BaseTurret::amIfiring()             // Returns firing variable, to check if the turret is ready to fire
{
	return Firing;
}

float BaseTurret::bulletDamage()         // Returns damage per shot, to check the damage the turret's bullets do
{
	return damagePerShot;
}

float BaseTurret::returnRange()          // Returns range that the turret can fire within
{
	return range;
}

int BaseTurret::returnTurretType()       // Returns turret type
{
	return tType;
}

int BaseTurret::returnOx()               // Returns Origin X coord
{
	return oX;
}

int BaseTurret::returnOy()               // Returns Origin Y coord
{
	return oY;
}