#include "Map.h"

Map::Map()
{
	loadTexture("gfx/DirtPath.png");

	// Pushes back all 8 tiles onto the stack.
	for (int i = 0; i < 8; i++)
	{
		tile.setSize(sf::Vector2f(120, 120));
		tileSet.push_back(tile);
	}

	// Declares each individual tile.
	tileSet[0].setTextureRect(sf::IntRect(0, 0, 120, 120));   // Top to Bottom
	tileSet[1].setTextureRect(sf::IntRect(120, 0, 120, 120)); // Left to Right
	tileSet[2].setTextureRect(sf::IntRect(240, 0, 120, 120)); // Right to Bottom
	tileSet[3].setTextureRect(sf::IntRect(360, 0, 120, 120)); // Right to Top
	tileSet[4].setTextureRect(sf::IntRect(480, 0, 120, 120)); // Left to Top
	tileSet[5].setTextureRect(sf::IntRect(600, 0, 120, 120)); // Left to Bottom
	tileSet[6].setTextureRect(sf::IntRect(720, 0, 120, 120)); // Green tile
	tileSet[7].setTextureRect(sf::IntRect(840, 0, 120, 120)); // Black tile

	// Sets the dimensions of the map.
	mapDimensions = sf::Vector2u(16, 9);

	// Sets up the entire map, it's position and builds it.
	tileMap = {
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 2, 1, 1, 1, 1, 5, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 0, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 0, 6, 6, 6, 6, 3, 1, 1, 1,
		6, 6, 2, 1, 5, 6, 6, 0, 6, 6, 6, 6, 6, 6, 6, 6,
		1, 1, 4, 6, 3, 1, 1, 4, 6, 6, 6, 6, 6, 6, 6, 6,
		6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
		7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
	};
	setPosition(sf::Vector2f(0, 0));
	buildLevel();
}