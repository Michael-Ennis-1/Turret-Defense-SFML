#pragma once
#include "Framework/GameObject.h"
#include "Framework/Collision.h"
#include "Framework/Input.h"

class BaseTurretTemplate : public GameObject
{
public:

	// |***General Functions***| \\

	BaseTurretTemplate();
	void update(float dt);
	void handleInput(float dt);

	// |***Set Functions***| \\

	void collisionResponse();     // Sets collision variable to true.
	void resetCollision();        // Resets collision variable.
	void spawnComplete();         // Sets spawn variable to false, used after a turret has been spawned.
	void setCoords(int x, int y); // Sets coordinates of the template, and stores the X and Y so it can go back there after finishing it's job.
	void setText(int text);       // Sets the texture of the turret template.

	// |***Return Functions***| \\

	bool spawnRequired();         // Returns yes when the player wants the turret placed.


protected:

	// Declares texture variables.
	sf::Texture Template, Template2, Template3;

	// Declares other variables, mainly used to make the handling of input easier and holding onto certain coordinates.
	bool mouseColliding = false, clicked = false, Colliding = false, spawn = false;
	int Ox, Oy;


};

