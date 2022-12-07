#include "Menu.h"

Menu::Menu()
{

	// Declares the text attributes, and also the box attributes for both the button and the background. Also sets the string of the text.
	font.loadFromFile("font/arial.ttf");

	menuBox.setSize(sf::Vector2f(1920, 1080));
	menuBox.setFillColor(sf::Color::White);

	tutorialButton.setSize(sf::Vector2f(200, 100));
	tutorialButton.setFillColor(sf::Color::Black);

	startButton.setSize(sf::Vector2f(200, 100));
	startButton.setFillColor(sf::Color::Black);

	titleText.setFont(font);
	startText.setFont(font);
	tutorialText.setFont(font);

	titleText.setFillColor(sf::Color::Red);
	startText.setFillColor(sf::Color::Red);
	tutorialText.setFillColor(sf::Color::Red);

	titleText.setCharacterSize(24);
	startText.setCharacterSize(14);
	tutorialText.setCharacterSize(14);

	titleText.setString("Turret Defense Project ALPHA");
	startText.setString("Start");
	tutorialText.setString("Tutorial");

	menuBox.setPosition(0, 0);
	startButton.setPosition(860, 790);
	tutorialButton.setPosition(860, 490);

	titleText.setPosition(800, 200);
	startText.setPosition(startButton.getPosition().x + 80, startButton.getPosition().y + 40);
	tutorialText.setPosition(tutorialButton.getPosition().x + 80, tutorialButton.getPosition().y + 40);
}

void Menu::handleInput(float dt)
{

	// This part checks whether or not the player's mouse is over either of the buttons.
	if (input->getMouseX() > 860 && input->getMouseX() < 1060 && input->getMouseY() > 490 && input->getMouseY() < 590)
	{
		mouseColliding = 1;
	}
	else if (input->getMouseX() > 860 && input->getMouseX() < 1060 && input->getMouseY() > 790 && input->getMouseY() < 890)
	{
		mouseColliding = 2;
	}
	else
	{
		mouseColliding = 0;
	}

}

void Menu::update(float dt)
{

	// Checks if the player has pressed on the tutorial button, then changes the text attributes and string.
	if (input->isLeftMouseDown() == true && mouseColliding == 1)
	{
		clicked = 1;
		startText.setString("This game is a simple tower defence, where your objective is to not let any enemies cross through the map from the right to the left. You can press LMB on any turret to see its stats, then right click anywhere to hide that information. You will lose 1 hp for every enemy that gets past.");
		tutorialText.setString("You will have to pay some Gold to place one. Press LMB on the turret you want to place, and move it to a location you want to place it, then press RMB to place it. Press SPACE to pause the game. Press RMB to go back to the menu, or continue reading to see enemy information.");
		titleText.setString("Green enemies HP is 5, Red is 15 and Blue is 8. Reds are the slowest, followed by Green, then Blue, being the fastest. There is a 30 second delay between each wave, so you have time to prepare. Also, don't forget to press SPACE to pause. Press P to continue playing after pausing.");

		startText.setPosition(0, 0);
		tutorialText.setPosition(0, 20);
		titleText.setPosition(0, 60);

		titleText.setCharacterSize(14);
	}

	// Checks if the player has pressed the start button, then begins the game.
	if (input->isLeftMouseDown() == true && mouseColliding == 2)
	{
		startClicked = true;
	}

	// Checks if player has pressed the RMB so that the menu goes back to normal.
	if (input->isRightMouseDown() == true)
	{
		clicked = 0;
		startText.setString("Start");
		tutorialText.setString("Tutorial");
		titleText.setString("Turret Defense Project ALPHA");

		startText.setPosition(startButton.getPosition().x + 80, startButton.getPosition().y + 40);
		tutorialText.setPosition(tutorialButton.getPosition().x + 80, tutorialButton.getPosition().y + 40);
		titleText.setPosition(800, 200);

		titleText.setCharacterSize(24);
	}
}

void Menu::render(sf::RenderWindow* window)
{

	// Renders the menuBox regardless of what screen it's on, except in the game is playing.
	window->draw(menuBox);

	// Shows the buttons and the text if the game has not started or paused.
	if (end == false && pause == false)
	{
		if (clicked == 0)
		{
			window->draw(startButton);
			window->draw(tutorialButton);
		}

		window->draw(tutorialText);
		window->draw(titleText);
	}

	// If the game has ended, it checks whether the game was won or not and shows a Win or Lose screen depending on that variable.
	if (end == true)
	{
		startText.setCharacterSize(24);
		if (won == false)
		{
			startText.setString("Sorry you lost. Here are your results");
			startText.setPosition(700, 0);
			menuBox.setFillColor(sf::Color::Black);

		}
		if (won == true)
		{
			startText.setString("Congratulations! You won! Here are your results");
			startText.setPosition(600, 0);
			menuBox.setFillColor(sf::Color::White);
		}
	}

	// If the game has paused, shows the paused text.
	if (end == false && pause == true)
	{
		startText.setString("Game is paused. Press P to continue playing");
		startText.setPosition(900, 0);
	}
	window->draw(startText);
}

void Menu::gameEnd(bool w) // Sets whether the game was won or lost, and sets the end of the game to true.
{
	end = true;
	won = w;
}

void Menu::setPause(bool p) // Sets the pause boolean based on input.
{
	pause = p;
}

bool Menu::returnStart()    // Returns whether the start button has been clicked or not.
{
	return startClicked;
}
