#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/BaseLevel.h"
#include "Framework/Input.h"
#include <string>
#include <iostream>
#include "Framework/TileMap.h"
#include "Map.h"
#include "Framework/Collision.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "BaseTurretTemplate.h" // First Header
#include "BaseTurret.h"         // Second Header
#include "TurretOverseer.h"     // Third Header
#include "Enemy.h"              // Fourth Header
#include "EnemyOverseer.h"      // Fifth Header
#include "Menu.h"               // Sixth Header


class Level : public BaseLevel{
public:
	Level(sf::RenderWindow* hwnd, Input* in, GameState* gs, AudioManager* aud);
	~Level();

	void handleInput(float dt) override;
	void update(float dt) override;
	void render();


private:
	// Declares new tilemap, so that the background can render. Also declares menu class.
	TileMap tileMap;
	Map map;
	Menu menu;

	// Declares new template for placing turrets, declares the overseers that help manage the game.
	BaseTurretTemplate Type1TT, Type2TT, Type3TT;
	TurretOverseer TOverseer;
	EnemyOverseer EOverseer;

	// Declares a simple collision detection system, so that the player cannot place turrets too close by to each other.
	int Colliding = 0;

	// Declares variables to help with turret range checking.
	float x = 0, y = 0, distance = 0;

	// Declares bools to handle pause/play/end
	bool start = false, pause = false, end = false;
};