#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Textbox.h"
#include <vector>
#include "Button.h"


class objectSprite
{

public:
	objectSprite(int radius, std::string name, sf::Color);

	objectSprite(int radius, std::string name, int x, int y, sf::Color);
	

	void drawTo(sf::RenderWindow& window);

	void setPosition(sf::Vector2i pos);

	sf::Vector2f getPosition();

	int getRadius();

	void setRadius(int radius);

	void addSprite(sf::RenderWindow &w, sf::Event e);

	std::string labelText;

	void move(int x, int y);

	void drawLabel(sf::RenderWindow &window);

	//merges sprite i into sprite j. Sprite i is deleted in the process


	sf::Font getFont();

	std::string getName();

	void setName(std::string newName);

	static void destroy(int id);
	double initialXVel, initialYVel;

	static void setFont();

private:
	sf::CircleShape circle;
	sf::Text label;
	sf::Vector2i position;
	bool isPlaced = false;
	int r;
	sf::Font font;
	std::string n;

	void setLabelPosition();


};

