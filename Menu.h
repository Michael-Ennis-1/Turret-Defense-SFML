#pragma once
#include "Framework\GameObject.h"
#include <string>
#include <string.h>
#include "Framework\Input.h"

class Menu : public GameObject
{
public:

	// |***General Functions***| \\

	Menu();
	void handleInput(float dt);
	void update(float dt);
	void render(sf::RenderWindow* window);

	// |***Set Functions***| \\

	void gameEnd(bool w);  // Sets gameEnd boolean to true, and sets whether the game was won or not depending on input.
	void setPause(bool p); // Sets pause to whatever is input, so that a basic pause screen is shown.

	// |***Get Functions***| \\

	bool returnStart();    // Returns start variable, for if the start button was clicked.

protected:

	// Declares menu box variables and menu text variables.
	sf::RectangleShape menuBox, startButton, tutorialButton;
	sf::Text titleText, startText, tutorialText;
	sf::Font font;

	// Declares other variables used throughout the class to help with things such as button touch, etc.
	bool tutClicked = false, startClicked = false, end = false, won, pause = false;
	int clicked = 0, mouseColliding = false;
};
