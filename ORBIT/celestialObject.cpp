#include "celestialObject.h"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#include "objectSprite.h"


double celestialObject::mToPX;
double celestialObject::timeFactor = 0;
int celestialObject::orbitPointCount;
std::vector<int> celestialObject::timeFactors = { 1, 60, 3600, 43200, 86400, 172800, 345600, 604800, 1210000, 2628000, 7884000, 15770000, 31540000};

celestialObject::celestialObject(int radius, std::string n, sf::RenderWindow &w, sf::Event e, int vectorPos, std::vector<celestialObject>& objects, sf::Color color) : sprite(radius, n, color)
{
	r = radius;
	sprite.addSprite(w, e);
	
	int coordx = sprite.getPosition().x + r;
	int coordy = sprite.getPosition().y + r;
	coords = { coordx, coordy };

	orbitPath.setFillColor(sf::Color::Transparent);
	orbitPath.setOutlineColor(sf::Color::White);
	orbitPath.setOutlineThickness(1);
	orbitPath.setPointCount(orbitPointCount);

	calculateOrbit(objects);

	id = vectorPos;
}

celestialObject::celestialObject(int radius, double mass, std::string n, int x, int y, int vectorPos, sf::Color color) : sprite(radius, n, x, y, color)
{
	r = radius;
	m = mass;
	int coordx = x;
	int coordy = y;
	coords = { coordx, coordy };
	
	T = 0;

	id = vectorPos;
}

void celestialObject::simulate(sf::RenderWindow& window, std::vector<celestialObject>& objects, float elapsedTime)
{
	//get adjusted time per jump
	//get elapsed time since last frame
	//divide elapsed time by time per jump
	//if less than 1, do nothing
	//else, jump by the amount
	for (int y = 1; y < objects.size(); y++)
	{
		celestialObject& i = objects[y];

		i.amountToJump += (elapsedTime / (i.timePerJump / timeFactors[timeFactor])) + i.initialOrbitPos;
		
		if (i.amountToJump > i.orbitPath.getPointCount())
		{
			i.amountToJump = 0;
		}
		std::cout << i.amountToJump << std::endl;

		i.coords.x = i.orbitPath.getTransform().transformPoint(i.orbitPath.getPoint(i.amountToJump)).x;
		i.coords.y = i.orbitPath.getTransform().transformPoint(i.orbitPath.getPoint(i.amountToJump)).y;
		i.sprite.setPosition({ i.coords.x, i.coords.y});

		window.draw(i.orbitPath);
		i.sprite.drawTo(window);
		objects[0].sprite.drawTo(window);
	}
}

void celestialObject::pauseSim(sf::RenderWindow& window, std::vector<celestialObject>& objects)
{
	for (celestialObject& i : objects)
	{
		window.draw(i.orbitPath);
		i.sprite.drawTo(window);
	}
}

void celestialObject::defineMeterToPixelRatio(int factor, int vertWinSize)
{
	mToPX = factor * 1.496e11 / vertWinSize;
}

void celestialObject::calculateOrbit(std::vector<celestialObject>& objects)
{
	double xd = mToPX * (coords.x - objects[0].coords.x);
	double yd = mToPX * (coords.y - objects[0].coords.y);
	double d = hypot(xd, yd);

	T = 2 * M_PI * sqrt(pow(d, 3) / (G * objects[0].m));

	timePerJump = T / orbitPointCount;

	orbitPath.setRadius(d / mToPX);

	float x = objects[0].coords.x - orbitPath.getRadius();
	float y = objects[0].coords.y - orbitPath.getRadius();

	orbitPath.setPosition({ x, y });
}
void celestialObject::setPointCount(int count)
{
	orbitPointCount = count;
}

std::string celestialObject::incrementTimeWarp(int increment)
{
	if (timeFactor + increment < 0)
	{
		return "1 sec/sec";
	}
	else if (timeFactor + increment > timeFactors.size() - 1)
	{
		return "1 yr/sec";
	}
	else
	{
		timeFactor += increment;

		if (timeFactor == 0)
		{
			return "1 sec/sec";
		}
		else if (timeFactor == 1)
		{
			return "1 min/sec";
		}
		else if (timeFactor == 2)
		{
			return "1 hr/sec";
		}
		else if (timeFactor == 3)
		{
			return "12 hrs/sec";
		}
		else if (timeFactor == 4)
		{
			return "1 day/sec";
		}
		else if (timeFactor == 5)
		{
			return "2 days/sec";
		}
		else if (timeFactor == 6)
		{
			return "4 days/sec";
		}
		else if (timeFactor == 7)
		{
			return "1 week/sec";
		}
		else if (timeFactor == 8)
		{
			return "2 weeks/sec";
		}
		else if (timeFactor == 9)
		{
			return "1 month/sec";
		}
		else if (timeFactor == 10)
		{
			return "3 months/sec";
		}
		else if (timeFactor == 11)
		{
			return "6 months/sec";
		}
		else if (timeFactor == 12)
		{
			return "1 yr/sec";
		}
	}

	return "error";
}
//0         1      2     3       4        5        6        7        8        9			10		  11		12
//1 sec | 1min | 1hr | 12hrs | 1 day | 2 days | 4 days | 1 week | 2 week | 1 month | 3 months | 6 months | 1 yr

