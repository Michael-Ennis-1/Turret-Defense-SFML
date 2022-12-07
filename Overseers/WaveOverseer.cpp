#include "WaveOverseer.h"

WaveOverseer::WaveOverseer()
{
	// This constructor was not really necessary, but I included it as good practice.
}

void WaveOverseer::update(float dt)
{

	// Wave section, deals with how many and how often enemies should spawn. 
	if (spawnTimer.getElapsedTime() > sf::milliseconds(3000) && spawn < 3)
	{
		type = 1;
		spawnNow = true;
		waveNumber = 1;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 3) // Always includes a 30 second timer every wave, so player has time to place turrets.
	{
		spawnNow = true;
		waveNumber = 2;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(1500) && spawn < 6 && spawn > 3)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 6)
	{
		type = 3;
		spawnNow = true;
		waveNumber = 3;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(3000) && spawn < 9 && spawn > 6)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 9)
	{
		type = 1;
		spawnNow = true;
		waveNumber = 4;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(2500) && spawn > 9 && spawn < 19)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 19)
	{
		type = 3;
		spawnNow = true;
		waveNumber = 5;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(2000) && spawn > 19 && spawn < 22)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 22)
	{
		type = 2;
		spawnNow = true;
		waveNumber = 6;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(2000) && spawn > 22 && spawn < 28)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 28)
	{
		type = 1;
		spawnNow = true;
		waveNumber = 7;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(500) && spawn > 28 && spawn < 40)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 40)
	{
		type = 3;
		spawnNow = true;
		waveNumber = 8;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(1000) && spawn > 40 && spawn < 55)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 55)
	{
		type = 2;
		spawnNow = true;
		waveNumber = 9;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(1000) && spawn > 55 && spawn < 70)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 70)
	{
		type = 1;
		spawnNow = true;
		waveNumber = 10;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(250) && spawn > 70 && spawn < 90)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 90)
	{
		type = 2;
		spawnNow = true;
		waveNumber = 11;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(2000) && spawn > 90 && spawn < 110)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 110)
	{
		type = 3;
		spawnNow = true;
		waveNumber = 12;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(500) && spawn > 110 && spawn < 130)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 130)
	{
		type = 1;
		spawnNow = true;
		waveNumber = 13;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(750) && spawn > 130 && spawn < 160)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 160)
	{
		type = 2;
		spawnNow = true;
		waveNumber = 14;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(1000) && spawn > 160 && spawn < 185)
	{
		spawnNow = true;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(30000) && spawn == 185)
	{
		type = 3;
		spawnNow = true;
		waveNumber = 15;
	}
	if (spawnTimer.getElapsedTime() > sf::milliseconds(500) && spawn > 185 && spawn < 230)
	{
		spawnNow = true;
	}
	if (spawn == 230)
	{
		lastSpawned = true;
	}
}

void WaveOverseer::resetSpawn()      // Resets spawnNow variable after it has spawned, and restarts the spawnTimer and increments spawn.
{
	spawnNow = false;
	spawnTimer.restart();
	spawn = spawn + 1;
}

int WaveOverseer::returnType()       // Returns what type of enemy to spawn.
{
	return type;
}

int WaveOverseer::returnWaveNumber() // Returns what wave number the overseer is currently on.
{
	return waveNumber;
}

bool WaveOverseer::readyToSpawn()    // Returns whether or not an enemy should be spawned.
{
	return spawnNow;
}

bool WaveOverseer::finalSpawned()    // Returns true if the last enemy has been spawned, so the game is won when all enemies are dead and hp > 0.
{
	return lastSpawned;
}