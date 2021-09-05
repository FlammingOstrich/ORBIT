#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Button
{
	public:
		Button(std::string buttonText, int textSize, sf::Font &font, sf::Vector2f position, sf::Vector2f size, sf::Color bgColor, sf::Color bgPressedColor, sf::Color outlineColor, sf::Color textColor, int outlineThick, bool isHidden);

		bool isMouseOver(sf::Vector2i mousePos);
		
		void drawTo(sf::RenderWindow& window);

		bool getState();

		void setState(bool newState);

		void setPosition(sf::Vector2f position);

		void setButtonSize(sf::Vector2f size);

		void setTextSize(int size);

		void setBGColor(sf::Color bg);
		
		void setTextColor(sf::Color textColor);

		void setText(std::string newText);

		void autoSizeAdjust();

		void setHidden(bool hide);

		bool getHiddenStatus();

	private:
		sf::RectangleShape button;
		sf::Text text;
		sf::Color bgPressed, bg;
		bool state = false;
		bool hidden;
		int charSize;
};

