#include "Bullet.h"

Bullet::Bullet()
{

	// Set up for each bullet
	setSize(sf::Vector2f(32, 32));
	setCollisionBox(sf::FloatRect(5, 5, 27, 27));
}

void Bullet::update(float dt)
{

	// Moves the bullet by the (unit vector * speed) * dt
	setPosition(getPosition() + (move123 * dt));

	// Makes the bullet dissapear if it goes out of the boundaries of the screen
	if (getPosition().x > 1920 || getPosition().x < 0 || getPosition().y > 1080 || getPosition().y < 0)
	{
		alive = false;
	}
}

void Bullet::setAlive()              // Sets a bullet alive
{
	alive = true;
}

void Bullet::setDamage(float dmg)    // Sets a bullet's damage
{
	damage = dmg;
}

void Bullet::setTarget(int x, int y) // Sets a bullet's target
{

	// The bullet sets a target by getting the unit vector of the vector between the enemy and itself, then moves by that unit vector * speed
	targetX = x;
	targetY = y;
	targetTrajectory = sf::Vector2f(targetX - getPosition().x, targetY - getPosition().y);
	targetTrajectory = VectorHelper::normalise(targetTrajectory);

	move123 = sf::Vector2f(targetTrajectory * speed);
}

void Bullet::collisionResponse()     // Sets a bullet to dead, and sets it's position to (0, 0).
{
	alive = false;
	setPosition(0, 0);
}

bool Bullet::aliveCheck()            // Returns alive boolean
{
	return alive;
}

float Bullet::hitDamage()            // Returns damage
{
	return damage;
}