#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include "Framework/VectorHelper.h"

class Enemy : public GameObject
{
public:
	// |***General Functions***| \\

	Enemy();
	void update(float dt);

	// |***Set Functions***| \\

	void damage(float dmg); // Lowers enemy's hp by the input damage.
	void setAlive(int t);   // Sets enemy alive, and sets their type.
	void setType(int t);    // Sets type of enemy.
	void doneDamage();      // Sets dealDamage to false after player has taken their damage.

	// |***Return Functions***| \\

	bool collectStatus();   // Returns dead boolean. Used for the exact moment the enemy died.
	bool aliveStatus();     // Returns alive boolean.
	bool madeItThrough();   // Returns true if the enemy has made it to the end of the track, otherwise false.

	int collectValue();

protected:

	// Declare animation variable
	Animation death;

	// Declare movement variables.
	sf::Vector2f target[9];
	sf::Vector2f direction;
	sf::Vector2f move;

	// Declare animation timer and time the animation will take.
	sf::Clock animationTimer;
	sf::Time deathTime = sf::milliseconds(500);

	// Declares other variables used throughout the enemy class.
	int currentTarget = 0, speed = 50.f, deadValue;
	float hp;
	bool alive = true, dead = false, deadChecked = false, dealDamage = false;
};
