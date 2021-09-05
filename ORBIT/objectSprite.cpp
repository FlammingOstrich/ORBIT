#include "objectSprite.h"
#include "Textbox.h"
#include <vector>
#include "Button.h"
#include "celestialObject.h"

#define pi 3.14159265358979323846

using namespace std;


sf::Font font;

objectSprite::objectSprite(int radius, std::string name, sf::Color color)
{
	font.loadFromFile("arial.ttf");

	circle.setRadius(radius);
	circle.setFillColor(color);

	n = name;
	r = radius;

	label.setFont(font);
	label.setCharacterSize(radius);
	label.setFillColor(sf::Color::White);
	label.setString(name);
}

objectSprite::objectSprite(int radius, std::string name, int x, int y, sf::Color color)
{
	font.loadFromFile("arial.ttf");

	circle.setRadius(radius);
	circle.setFillColor(color);

	n = name;
	r = radius;

	label.setFont(font);
	label.setCharacterSize(radius);
	label.setFillColor(sf::Color::White);
	label.setString(name);


	setPosition({ x, y });
}



void objectSprite::setName(std::string newName)
{
	label.setString(newName);
}

void objectSprite::setRadius(int radius)
{
	circle.setRadius(radius);
	label.setCharacterSize(radius);
}
std::string objectSprite::getName()
{
	return label.getString();
}

sf::Font objectSprite::getFont()
{
	
	return *label.getFont();
}

void objectSprite::drawTo(sf::RenderWindow &window)
{
	window.draw(circle); 
	label.setFont(font);
	window.draw(label);
}

void objectSprite::setPosition(sf::Vector2i pos)
{
	circle.setPosition(pos.x - r, pos.y - r);
	label.setPosition(pos.x + r, pos.y + r);
}

sf::Vector2f objectSprite::getPosition()
{
	return circle.getPosition();
}

int objectSprite::getRadius()
{
	return r;
}



void objectSprite::addSprite(sf::RenderWindow& window, sf::Event e)
{
	sf::Event event = e;
	
	bool spritePlaced = false;
	std::vector<double> initialVels{0, 0};

	sf::Text posLabel;
	posLabel.setFont(font);
	posLabel.setCharacterSize(15);
	posLabel.setFillColor(sf::Color::White);

	while (!spritePlaced)
	{

		window.clear();

		setPosition({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y});

		posLabel.setPosition(sf::Mouse::getPosition(window).x + 20 + r, sf::Mouse::getPosition(window).y + 20 + r);
		string xPos = to_string(sf::Mouse::getPosition(window).x);
		string yPos = to_string(sf::Mouse::getPosition(window).y);
		posLabel.setString("(" + xPos + ", " + yPos + ")");



		drawTo(window);
		window.draw(posLabel);	
		window.display();

		//places the sprite
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			spritePlaced = true;
		}
	}
}

void objectSprite::move(int x, int y)
{
	circle.move(x, y);
}


