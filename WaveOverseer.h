#pragma once
#include "Framework/GameObject.h"


class WaveOverseer
{
public:

	// |***General Functions***| \\

	WaveOverseer();
	void update(float dt);

	// |***Set Functions***| \\

	void resetSpawn();      // Resets spawn variable, used when a spawn has occured

	// |***Return Functions***| \\

	int returnType();       // Returns enemy type
	int returnWaveNumber(); // Returns wave number
	bool readyToSpawn();    // Returns true if an enemy should be spawned, otherwise returns false
	bool finalSpawned();    // Returns true if teh last enemy has been spawned, used for when the game ends after the last enemy has been killed and hp > 0

protected:

	sf::Clock spawnTimer;
	int spawn = 0, type, waveNumber = 0;
	bool spawnNow = false, lastSpawned = false;

};
