#ifndef CELESTIALOBJECT_H
#define CELESTIALOBJECT_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include "objectSprite.h"
#define G 6.67e-11


#pragma once


class celestialObject
{
private:
	
	sf::Vector2i coords;
	objectSprite sprite;
	sf::CircleShape orbitPath;
	static std::vector<int> timeFactors; //1 sec | 1min | 1hr | 12hrs | 1 day | 2 days | 4 days | 1 week | 2 week | 1 month | 3 months | 6 months | 9 months | 1 yr

	int r, id;
	double T, timePerJump, m;
	static double timeFactor, mToPX;
	static int orbitPointCount;
	int initialOrbitPos = 0;
	int amountToJump = 0;

	void calculateOrbit(std::vector<celestialObject>& objects);

public:
	celestialObject(int radius, std::string n, sf::RenderWindow& w, sf::Event e, int vectorPos, std::vector<celestialObject>& objects, sf::Color color);

	celestialObject(int radius, double mass, std::string n, int x, int y, int vectorPos, sf::Color color);

	static void traverseOrbit(sf::RenderWindow& window);

	static void defineMeterToPixelRatio(int factor, int vertWinSize); 

	static void setTimeFactor(double timeMultiplier);
	
	static void simulate(sf::RenderWindow& window, std::vector<celestialObject>& objects, float elapsedTime);
	static void pauseSim(sf::RenderWindow& window, std::vector<celestialObject>& objects);
	static void setPointCount(int count);
	static std::string incrementTimeWarp(int increment);
	

};

#endif // CELESTIALOBJECT_H
