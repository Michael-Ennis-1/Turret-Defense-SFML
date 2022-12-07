#pragma once

#include <vector>
#include "Enemy.h"
#include "WaveOverseer.h"
#include <string>

class EnemyOverseer
{
public:
	// |***General Functions***| \\

	EnemyOverseer();
	void update(float dt);
	void render(sf::RenderWindow* window);

	// |***Enemy Functions***| \\        

	void damage(float dmg, int e);         // Does input amount of damage to a specific enemy
	void spawn(int t);                     // Spawns a new enemy, of type t

	std::vector<Enemy> enemy;

	// |***Game Functions***| \\

	void setGold(int g);                   // Sets the player's amount of gold.

	int getGold();                         // Returns the player's amount of gold.

	bool gameWon();                        // Returns true if the game was won
	bool gameLost();                       // Returns true if the game was lost
	bool hasGameEnded();                   // Returns true if the game has ended

protected:

	// Declares all the information displayed to the screen and win/loss screens
	sf::Text waveNumberText, waveText, scoreNumberText, scoreText, playerHPNumber, playerHPText, goldNumber, goldText, turret1Cost, turret2Cost, turret3Cost;
	sf::Font font;

	// Declares enemy textures and a wave overseer to manage the waves
	WaveOverseer WOverseer;
	sf::Texture enemyTexture, enemyTexture2, enemyTexture3;

	// Used throughout the class
	bool spawned = false, lost = false, win = false, gameEnd = false, allDead = false;
	int wNum = 0, score = 0, gold = 120, playerHP = 10, eValue;

};

