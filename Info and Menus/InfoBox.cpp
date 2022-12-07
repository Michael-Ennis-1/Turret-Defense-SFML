#include "InfoBox.h"

InfoBox::InfoBox() // Declares all information for the box itself, and the text inside of the box as well as the range circle's color and thickness.
{
	box.setSize(sf::Vector2f(200, 100));
	box.setFillColor(sf::Color::Red);
	box.setOutlineColor(sf::Color::Black);
	box.setOutlineThickness(2.0f);

	rangeCircle.setFillColor(sf::Color::Transparent);
	rangeCircle.setOutlineColor(sf::Color::Red);
	rangeCircle.setOutlineThickness(2.0f);

	font.loadFromFile("font/arial.ttf");

	text.setFont(font);
	text.setCharacterSize(12);
	text.setFillColor(sf::Color::White);

	text2.setFont(font);
	text2.setCharacterSize(12);
	text2.setFillColor(sf::Color::White);

	text3.setFont(font);
	text3.setCharacterSize(12);
	text3.setFillColor(sf::Color::White);
}

void InfoBox::update(float dt)
{

	// This section changes the string of the box, depending on what type of turret it is. Also sets the radius of the range circle.
	if (type == 1)
	{
		stringRange = "Range of this turret is 300 pixels";
		stringDamage = "Damage of this turret is 2 dmg";
		stringReload = "Reload of this turret is 2.5 seconds";
		rangeCircle.setRadius(300);
	}
	if (type == 2)
	{
		stringRange = "Range of this turret is 500 pixels";
		stringDamage = "Damage of this turret is 5 dmg";
		stringReload = "Reload of this turret is 7.5 seconds";
		rangeCircle.setRadius(500);
	}
	if (type == 3)
	{
		stringRange = "Range of this turret is 200 pixels";
		stringDamage = "Damage of this turret is 1 dmg";
		stringReload = "Reload of this turret is 1 second";
		rangeCircle.setRadius(200);
	}

	// This section sets the position of the box and string, relative to wherever the box is, which is definied in the EOverseer depending on mouse input.
	text.setPosition(box.getPosition().x + 10, box.getPosition().y + 5);
	text.setString(stringRange);

	text2.setPosition(box.getPosition().x + 10, box.getPosition().y + 20);
	text2.setString(stringDamage);

	text3.setPosition(box.getPosition().x + 10, box.getPosition().y + 35);
	text3.setString(stringReload);
}

void InfoBox::setAlive(bool al) // Sets the alive boolean depending on input.
{
	alive = al;
}

void InfoBox::setType(int t)    // Sets turret type depending on input.
{
	type = t;
}

bool InfoBox::aliveStatus()     // Returns alive status.
{
	return alive;
}