#include "EnemyOverseer.h"

EnemyOverseer::EnemyOverseer()
{

	// This section deals with relaying important info like Score, Gold, HP and Wave Number.
	enemyTexture.loadFromFile("gfx/Enemy1.png");
	enemyTexture2.loadFromFile("gfx/Enemy2.png");
	enemyTexture3.loadFromFile("gfx/Enemy3.png");

	font.loadFromFile("font/arial.ttf");

	waveNumberText.setFont(font);
	waveNumberText.setCharacterSize(20);
	waveNumberText.setPosition(1800, 0);
	waveNumberText.setFillColor(sf::Color::Red);

	waveText.setString("Wave: ");
	waveText.setFont(font);
	waveText.setCharacterSize(20);
	waveText.setPosition(1740, 0);
	waveText.setFillColor(sf::Color::Red);

	scoreNumberText.setFont(font);
	scoreNumberText.setCharacterSize(20);
	scoreNumberText.setPosition(60, 30);
	scoreNumberText.setFillColor(sf::Color::Cyan);

	scoreText.setString("Score: ");
	scoreText.setFont(font);
	scoreText.setCharacterSize(20);
	scoreText.setPosition(0, 30);
	scoreText.setFillColor(sf::Color::Cyan);

	playerHPNumber.setFont(font);
	playerHPNumber.setCharacterSize(20);
	playerHPNumber.setPosition(40, 0);
	playerHPNumber.setFillColor(sf::Color::Red);

	playerHPText.setString("HP: ");
	playerHPText.setFont(font);
	playerHPText.setCharacterSize(20);
	playerHPText.setPosition(0, 0);
	playerHPText.setFillColor(sf::Color::Red);

	goldNumber.setFont(font);
	goldNumber.setCharacterSize(20);
	goldNumber.setPosition(50, 60);
	goldNumber.setFillColor(sf::Color::Yellow);

	goldText.setString("Gold: ");
	goldText.setFont(font);
	goldText.setCharacterSize(20);
	goldText.setPosition(0, 60);
	goldText.setFillColor(sf::Color::Yellow);

	// This section deals with cost for each turret.
	turret1Cost.setString("50");
	turret1Cost.setFont(font);
	turret1Cost.setCharacterSize(20);
	turret1Cost.setPosition(0, 900);
	turret1Cost.setFillColor(sf::Color::Yellow);

	turret2Cost.setString("60");
	turret2Cost.setFont(font);
	turret2Cost.setCharacterSize(20);
	turret2Cost.setPosition(200, 900);
	turret2Cost.setFillColor(sf::Color::Yellow);

	turret3Cost.setString("70");
	turret3Cost.setFont(font);
	turret3Cost.setCharacterSize(20);
	turret3Cost.setPosition(400, 900);
	turret3Cost.setFillColor(sf::Color::Yellow);

}

void EnemyOverseer::spawn(int t)
{

	// This loop runs through and resets an enemy if one has died and is still a member of the vector, to save on processing power.
	for (int e = 0; e < enemy.size(); e++)
	{
		if (enemy[e].aliveStatus() == false && spawned == false)
		{
			enemy[e].setPosition(1920, 512);
			enemy[e].setAlive(t);
			spawned = true;
			if (t == 1)
			{
				enemy[e].setTexture(&enemyTexture);
			}
			if (t == 2)
			{
				enemy[e].setTexture(&enemyTexture2);
			}
			if (t == 3)
			{
				enemy[e].setTexture(&enemyTexture3);
			}

		}
	}

	// This loop runs if there was no space to reuse dead enemies. This part creates a new one entirely, and adds it onto the stack.
	if (spawned == false)
	{
		enemy.push_back(Enemy());
		enemy[enemy.size() - 1].setPosition(1920, 512);
		enemy[enemy.size() - 1].setType(t);
		if (t == 1)
		{
			enemy[enemy.size() - 1].setTexture(&enemyTexture);
		}
		if (t == 2)
		{
			enemy[enemy.size() - 1].setTexture(&enemyTexture2);
		}
		if (t == 3)
		{
			enemy[enemy.size() - 1].setTexture(&enemyTexture3);
		}
	}
	spawned = false;
}

void EnemyOverseer::update(float dt)
{
	// This section does two checks on every single enemy, and also updates all of the enemies.
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i].update(dt);

		// This check makes sure that if an enemy dies, the enemy's gold and score value is added to the screen.
		if (enemy[i].aliveStatus() == false)
		{
			eValue = enemy[i].collectValue();
			score = score + eValue;
			gold = gold + (eValue * 5);
		}

		// This check makes sure that if an enemy made it through to the end, then the player's hp is dropped by 1.
		if (enemy[i].madeItThrough() == true)
		{
			playerHP = playerHP - 1;
			enemy[i].doneDamage();

			// Sets the game to end if the player loses all their HP.
			if (playerHP < 1)
			{
				lost = true;
				gameEnd = true;
			}
		}
	}

	// This checks that an enemy needs to be spawned, and what type it should be.
	if (WOverseer.readyToSpawn() == true)
	{
		spawn(WOverseer.returnType());
		WOverseer.resetSpawn();
	}

	// Updates wave overseer.
	WOverseer.update(dt);

	// Sets the game to end if the player has lasted 15 waves and all the enemies are dead.
	if (WOverseer.returnWaveNumber() == 15 && WOverseer.finalSpawned() == true)
	{
		allDead = true;
		for (int i = 0; i < enemy.size(); i++)
		{
			if (enemy[i].aliveStatus() == true)
			{
				allDead = false;
			}

		}
		if (allDead == true)
		{
			win = true;
			gameEnd = true;
		}
	}

	// This section makes sure all the ints are converted to strings.
	waveNumberText.setString(std::to_string(WOverseer.returnWaveNumber()));
	scoreNumberText.setString(std::to_string(score));
	playerHPNumber.setString(std::to_string(playerHP));
	goldNumber.setString(std::to_string(gold));
}

void EnemyOverseer::render(sf::RenderWindow* window)
{
	if (win == false && lost == false)
	{
		// This part renders all the information on the player screen.
		window->draw(waveNumberText);
		window->draw(waveText);
		window->draw(scoreNumberText);
		window->draw(scoreText);
		window->draw(playerHPNumber);
		window->draw(playerHPText);
		window->draw(goldNumber);
		window->draw(goldText);
		window->draw(turret1Cost);
		window->draw(turret2Cost);
		window->draw(turret3Cost);

		// This part renders all the enemies.
		for (int i = 0; i < enemy.size(); i++)
		{
			if (enemy[i].aliveStatus() == true)
			{
				window->draw(enemy[i]);
			}
		}
	}
	// This part renders certain parts depending on whether the game was won/lost.
	if (win == true || lost == true)
	{
		window->draw(scoreNumberText);
		window->draw(scoreText);
		window->draw(playerHPNumber);
		window->draw(playerHPText);
		if (lost == true)
		{
			window->draw(waveText);
			window->draw(waveNumberText);
			waveText.setPosition(860, 800);
			waveNumberText.setPosition(900, 800);
		}

		scoreNumberText.setPosition(900, 400);
		scoreText.setPosition(840, 400);
		playerHPNumber.setPosition(900, 600);
		playerHPText.setPosition(860, 600);
	}
}

void EnemyOverseer::damage(float dmg, int e)
{

	// Damages an input enemy by the input damage.
	enemy[e].damage(dmg);
}

void EnemyOverseer::setGold(int g) // Sets gold amount to input.
{
	gold = g;
}

int EnemyOverseer::getGold()       // Returns gold variable.
{
	return gold;
}

bool EnemyOverseer::gameWon()      // Returns win variable.
{
	return win;
}

bool EnemyOverseer::gameLost()     // Returns lost variable.
{
	return lost;
}

bool EnemyOverseer::hasGameEnded() // Returns gameEnd variable.
{
	return gameEnd;
}