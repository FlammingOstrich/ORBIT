#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class Textbox
{
	public: 
		Textbox(int size, sf::Vector2f position, sf::Font& font, sf::Color color, int limit, bool setSel, bool allowNumber, bool allowCharacter, bool allowSpecialChar, std::string placeholderText);

		void setSelected(bool setSel);

		void setLimit(bool trueOrFalse, int limit);
		
		void setLimit(bool trueOrFalse);

		void setFont(sf::Font& font);

		void setPosition(sf::Vector2f position);

		void allowNumber(bool allow);

		void allowCharacter(bool allow);

		void typedOn(sf::Event input);

		void drawTo(sf::RenderWindow& window);

		void mouseSelect(sf::Vector2i mousePos);

		std::string getText();

		bool getSelectedStatus();

		void allowSpecialCharacter(bool allow);

		void calculateContainer();

		void clearField();

		bool checkIfEmpty();

		void showErrorMessage(std::string error);

		void setText(std::string text);
	private:
		sf::Text textbox;
		std::ostringstream text;
		bool isSel = false;
		bool hasLimit = false;
		bool allowNum, allowChar, allowSpecChar;
		int limit;
		float leftBoundary, rightBoundary, upBoundary, downBoundary;
		sf::Vector2f pos;
		sf::RectangleShape rectangle;
		std::string placeholder;
		float boxWidth, boxHeight;

		void inputLogic(int charTyped);
		

		void deleteChar();
		

};

