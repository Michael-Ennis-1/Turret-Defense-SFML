#pragma once
#include "Framework\GameObject.h"
#include <string>
#include <string.h>

class InfoBox : public GameObject
{
public:

	// |***General Functions***| \\

	InfoBox();
	void update(float dt);

	// |***Set Functions***| \\

	void setAlive(bool al);  // Changes whether the infobox is shown or not
	void setType(int t);     // Changes specifics in terms of what the info box will show

	// |***Get Functions***| \\

	bool aliveStatus();      // Returns alive status


	// These are public so that the TOverseer itself can directly access them to place their position, and render them
	sf::RectangleShape box;
	sf::CircleShape rangeCircle;
	sf::Text text, text2, text3;

protected:

	// Decides which text to display, based on the type of turret.
	int type;

	// Declares font and strings for the infobox to show.
	sf::Font font;

	std::string stringRange, stringDamage, stringReload;
};

