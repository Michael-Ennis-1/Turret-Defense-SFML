#include "BaseTurretTemplate.h"

BaseTurretTemplate::BaseTurretTemplate()
{

	// Sets up all the textures for the turrets, and the attributes of the templates.
	Template.loadFromFile("gfx/Turret1CE2.png");
	Template2.loadFromFile("gfx/Turret2.png");
	Template3.loadFromFile("gfx/Turret3.png");

	setSize(sf::Vector2f(128, 128));
	setCollisionBox(sf::FloatRect(0, 0, 128, 128));
	setTextureRect((sf::IntRect(0, 0, 128, 128)));

}

void BaseTurretTemplate::update(float dt)
{
	// Checks if mouse clicked on the template, then moves the template over the centre of the mouse.
	if (clicked == true)
	{
		setPosition(input->getMouseX() - 64, input->getMouseY() - 64);
	}

	// Checks if mouse is over the template.
	if (input->getMouseX() > getPosition().x && input->getMouseX() < getPosition().x + 128 && input->getMouseY() > getPosition().y && input->getMouseY() < getPosition().y + 128)
	{
		mouseColliding = true;
	}
	else
	{
		mouseColliding = false;
	}

	// Checks if template is colliding with any object/pathway, then changes it's look to a turret with red outline symbolising that it's unable to be placed down
	// Otherwise changes it back to the original template.
	if (Colliding == true)
	{
		setTextureRect((sf::IntRect(640, 0, 128, 128)));
	}
	else
	{
		setTextureRect((sf::IntRect(0, 0, 128, 128)));
	}
}

void BaseTurretTemplate::handleInput(float dt)
{
	// Checks if left mouse down and mouse is touching template.
	if (input->isLeftMouseDown() && mouseColliding == true)
	{
		clicked = true;
	}

	// Checks if template colliding with object, if it isn't and the right mouse button is down and the template is currently following the mouse,
	// Then it sets the boolean for mouse which was clicked earlier to false, sets a signal for the Turret Overseer to spawn new turret, and sends template back to
	// original position.
	if (input->isRightMouseDown() && clicked == true && Colliding == false)
	{
		clicked = false;
		spawn = true;
		setPosition(Ox, Oy);
	}
}

void BaseTurretTemplate::collisionResponse()     // Sets colliding to true.
{
	Colliding = true;
}

void BaseTurretTemplate::resetCollision()        // Sets collision to false.
{
	Colliding = false;
}

void BaseTurretTemplate::spawnComplete()         // Sets spawn to false after a spawn has been completed.
{
	spawn = false;
}

void BaseTurretTemplate::setCoords(int x, int y) // Sets the position of the template, and stores the Original X and Original Y coords so that it can be sent back to
{                                                // its original position after having done its job.
	setPosition(x, y);
	Ox = x;
	Oy = y;
}

void BaseTurretTemplate::setText(int text)       // Sets the texture of the turret, based on whichever type it is.
{
	if (text == 1)
	{
		setTexture(&Template);
	}
	if (text == 2)
	{
		setTexture(&Template2);
	}
	if (text == 3)
	{
		setTexture(&Template3);
	}
}

bool BaseTurretTemplate::spawnRequired()          // Returns spawn variable.
{
	return spawn;
}
