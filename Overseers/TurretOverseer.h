#pragma once

#include "Framework/GameObject.h"
#include "Framework/Input.h"
#include <vector>
#include "BaseTurret.h"
#include "Bullet.h"
#include "InfoBox.h"

#include <iostream>

class TurretOverseer : public GameObject
{
public:
	// |***General Functions***| \\
	
	TurretOverseer();
	void update(float dt);
	void handleInput(float dt);
	void render(sf::RenderWindow* window);

	// |***Turret Functions***| \\

	void spawnTurret(int x, int y, int t);     // Spawns new turret at intput coordinates, as type t
	void setTarget(int x, int y, int t);       // Sets target coordinates for an input turret to aim towards
	void setAim(bool aim, int t);              // Sets an inputted turret's aim boolean, depending on if it is aiming at something or not
	void doneFiring(int t);                    // Sets a specific turret's firing variable to false, when it is finished firing

	bool isTargeting(int t);                   // Checks a specific turret's aim boolean
	bool isFiring(int t);                      // Checks if a specific turret is ready to fire
	float checkDamage(int t);                  // Checks a specific turret's bullet damage
	float returnRange(int t);                  // Checks a specific turret's range


	// |***Bullet Functions***| \\

	void spawnBullet(int x, int y, float dmg); // Spawns new bullet at input coordinates, and sets damage for that bullet
	void setBulletTarget(int x, int y, int b); // Sets target coordinates for a specific bullet to aim towards


	// |***Public Variables***| \\
	// Could potentially turn these into Getter functions instead.
	std::vector<BaseTurret> turret;
	std::vector<Bullet> bullet;

protected:

	// Declares textures
	sf::Texture bulletTexture, basicTexture, secondTexture, thirdTexture;

	// Declares variables that are used for aiming turret.
	sf::Vector2f offset;
	sf::Vector2f centre = sf::Vector2f(64, 64);

	float diffx = 0, diffy = 0, angle = 0;

	// Declares other miscellaneous variables.
	bool alreadySpawnedBullet = false, mouseColliding = false, clicked = false;
	int tType;

	// Declare Infobox, for turret info
	InfoBox infoBox;
};
