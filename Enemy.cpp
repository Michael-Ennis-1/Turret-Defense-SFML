#include "Enemy.h"

Enemy::Enemy()               // Sets targets for the enemys to aim towards, also sets size and texture and sound         
{
	setSize(sf::Vector2f(64, 64));
	setCollisionBox(sf::FloatRect(8, 8, 56, 56));
	setTextureRect(sf::IntRect(0, 0, 64, 64));

	// This part sets up the animations
	death.addFrame(sf::IntRect(0, 0, 64, 64));
	death.addFrame(sf::IntRect(64, 0, 64, 64));
	death.addFrame(sf::IntRect(128, 0, 64, 64));
	death.addFrame(sf::IntRect(192, 0, 64, 64));
	death.addFrame(sf::IntRect(256, 0, 64, 64));
	death.setFrameSpeed(1.0f / 10.0f);

	// This part sets the coords for the enemies to move towards.
	target[0] = sf::Vector2f(1458, 512);
	target[1] = sf::Vector2f(1458, 142);
	target[2] = sf::Vector2f(858, 142);
	target[3] = sf::Vector2f(858, 750);
	target[4] = sf::Vector2f(500, 750);
	target[5] = sf::Vector2f(500, 620);
	target[6] = sf::Vector2f(260, 620);
	target[7] = sf::Vector2f(260, 750);
	target[8] = sf::Vector2f(0, 750);
}

void Enemy::update(float dt) // Checks if hp is lesss than 0, then if alive, checks which target to move towards, then starts moving towards the target.
{

	// Checks all the enemies to see if they have reached their target, then sends them on their way to the next one.
	if (alive == true)
	{
		for (int i = 0; i < 9; i++)
		{
			if (VectorHelper::magnitude(target[i] - getPosition()) < 10.0f)
			{
				currentTarget = i + 1;
			}

			// Checks if the enemies have made it to the very end without being dead, then deals damage to player's HP.
			if (currentTarget == 9 && hp > 0)
			{
				alive = false;
				dealDamage = true;
			}
		}

		// Move section.
		direction = target[currentTarget] - getPosition();
		direction = VectorHelper::normalise(direction);
		move = sf::Vector2f(direction.x * speed, direction.y * speed);
		setPosition(getPosition() + (move * dt));

		// This section checks if dead, then perform animation and sound.
		if (hp <= 0)
		{

			// There is a timer here to make sure the animation ends when its over, rather than repeating the same animation.
			if (animationTimer.getElapsedTime() <= deathTime)
			{
				death.animate(dt);
				setTextureRect(death.getCurrentFrame());
				dead = true;
			}
			else
			{
				alive = false;
				setPosition(0, 0);
			}
		}
	}

	// Sets texture to full circle, for when the player is set alive again in case the animation ran over too many frames.
	if (alive == false)
	{
		setTextureRect(sf::IntRect(0, 0, 64, 64));
	}
}

void Enemy::damage(float dmg) // Resets animation timer and lowers hp by input damage.
{
	hp = hp - dmg;
	animationTimer.restart();
}

void Enemy::setAlive(int t)   // Resets enemy to alive, and specifies the type it is going to be. This makes it easy to reuse already used enemies.
{
	alive = true;
	currentTarget = 0;

	// The dead variable helps stop turrets from aiming at a dead target, and bullets from colliding with it as well.
	dead = false;
	if (t == 1)
	{
		speed = 50.0f;
		hp = 5;
		deadValue = 1;
	}
	if (t == 2)
	{
		speed = 40.0f;
		hp = 15;
		deadValue = 3;
	}
	if (t == 3)
	{
		speed = 60.0f;
		hp = 8;
		deadValue = 2;
	}

	// deadChecked helps the player only gain score once the enemy dies, rather than giving score forever if the enemy is dead.
	deadChecked = false;
}

void Enemy::setType(int t)    // Sets type for when an enemy is spawned for the first time.
{
	if (t == 1)
	{
		speed = 50.0f;
		hp = 5;
		deadValue = 1;
	}
	if (t == 2)
	{
		speed = 40.0f;
		hp = 15;
		deadValue = 3;
	}
	if (t == 3)
	{
		speed = 60.0f;
		hp = 8;
		deadValue = 2;
	}
}

void Enemy::doneDamage()     // Resets the boolean to cause damage to the player, after the damage has already been done.
{
	dealDamage = false;
}

bool Enemy::aliveStatus()    // Returns the alive status of the Enemy.
{
	return alive;
}

bool Enemy::collectStatus()  // Returns the exact moment the enemy died, rather than after the animation has ended.
{
	return dead;
}

bool Enemy::madeItThrough()  // Returns the amount of damage to deal to the player.
{
	return dealDamage;
}

int Enemy::collectValue()    // Gives a certain amount of money and score, based on the deadValue, to the player if they killed the enemy and it has not been taken
{                            // already. Otherwise, returns 0.
	if (hp <= 0 && deadChecked == false)
	{
		deadChecked = true;
		return deadValue;
	}
	else
	{
		return 0;
	}
}