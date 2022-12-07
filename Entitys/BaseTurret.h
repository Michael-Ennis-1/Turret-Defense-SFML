#pragma once
#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"


class BaseTurret : public GameObject
{
public:
	// |***General Functions***| \\

	BaseTurret();
	void update(float dt);

	// |***Set Functions***| \\

	void Targeting();             // Sets targeting boolean to true
	void NotTargeting();          // Sets targeting boolean to false
	void takenShot();             // Sets firing boolean to false
	void setOG(int x, int y);     // Sets copy of origin coords
	void setTurretType(int type); // Come back to this function pls, sets turret range, bullet damage and reload rate

	// |***Return Functions***| \\

	bool amItargeting();          // Returns targeting boolean
	bool amIfiring();             // Returns firing boolean
	float bulletDamage();         // Returns bullet damage variable
	float returnRange();          // Returns range variable
	int returnTurretType();       // Returns turret type varaible
	int returnOy();               // Returns Origin X
	int returnOx();               // Returns Origin Y


protected:
	// Declare Variables
	bool Aiming = false, Firing = false, animGo = false, mouseColliding = false, clicked = false;
	float damagePerShot, targetX, targetY, range;
	int tType, oX, oY;

	// Declare timer variables and set times for reloading
	sf::Clock reloadTimer;
	sf::Clock animationTimer;
	sf::Time reload;
	sf::Time animTime = sf::milliseconds(250);

	// Declare animation
	Animation shoot;
};


