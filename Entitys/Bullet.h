#pragma once
#pragma once
#include "Framework/GameObject.h"
#include "Framework/VectorHelper.h"
#include <math.h>
class Bullet : public GameObject
{
public:

	// |***General Functions***| \\

	Bullet();
	void update(float dt);

	// |***Set Functions***| \\

	void setAlive();              // Sets a bullet alive.
	void setDamage(float dmg);    // Sets the damage of a bullet.
	void setTarget(int x, int y); // Sets the target coords of a bullet.
	void collisionResponse();     // Sets a bullet dead, and sets it's position to (0, 0).

	// |***Return Functions***| \\

	bool aliveCheck();            // Returns a bullet's alive boolean.

	float hitDamage();            // Returns a bullet's float damage.

protected:

	// Declares variables used by the bullet for speed, its target, and whether it;s in play.
	float damage, targetX, targetY, speed = 1000.f;
	bool alive = true;

	// Declares vectors for how the bullet moves.
	sf::Vector2f move123, targetTrajectory;
};
