#include "Button.h"

Button::Button(std::string buttonText, int textSize, sf::Font& font, sf::Vector2f position, sf::Vector2f size, sf::Color bgColor, sf::Color bgPressedColor, sf::Color outlineColor, sf::Color textColor, int outlineThick, bool isHidden)
{
	text.setCharacterSize(textSize);
	text.setFillColor(textColor);
	text.setFont(font);
	text.setPosition(position);
	text.setString(buttonText);

	button.setSize(size);
	button.setFillColor(bgColor);
	button.setOutlineColor(outlineColor);
	button.setOutlineThickness(outlineThick);
	button.setPosition(position);

	bgPressed = bgPressedColor;
	bg = bgColor;
	charSize = textSize;

	hidden = isHidden;
}

void Button::autoSizeAdjust()
{
	float buttonWidth = text.getLocalBounds().width;
	float buttonHeight = text.getLocalBounds().height;

	button.setSize({ buttonWidth + 3, buttonHeight + 7 });
}

bool Button::isMouseOver(sf::Vector2i mousePos)
{
	if (hidden)
	{
		return false;
	}
	else 
	{
		float buttonWidth = button.getLocalBounds().width;
		float buttonHeight = button.getLocalBounds().height;

		float leftBoundary = button.getPosition().x;
		float rightBoundary = leftBoundary + buttonWidth;
		float upBoundary = button.getPosition().y;
		float downBoundary = upBoundary + buttonHeight;

		if (mousePos.x <= rightBoundary && mousePos.x >= leftBoundary && mousePos.y >= upBoundary && mousePos.y <= downBoundary && !hidden)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


}
	

void Button::drawTo(sf::RenderWindow &window)
{
	if (!hidden)
	{
		window.draw(button);
		window.draw(text);
	}
}

bool Button::getState()
{
	return state;
}

void Button::setState(bool newState)
{
	state = newState;

	if (state)
	{
		setBGColor(bgPressed);
	}
	else
	{
		setBGColor(bg);
	}
}

void Button::setPosition(sf::Vector2f position)
{
	text.setPosition(position);
	button.setPosition(position);
}


void Button::setButtonSize(sf::Vector2f size)
{
	button.setSize(size);
}

void Button::setTextSize(int size)
{
	text.setCharacterSize(size);
}

void Button::setBGColor(sf::Color bgColor)
{
	button.setFillColor(bgColor);
}

void Button::setTextColor(sf::Color textColor)
{
	text.setFillColor(textColor);
}

void Button::setText(std::string newText)
{
	text.setString(newText);
}


void Button::setHidden(bool hide)
{
	hidden = hide;
}

bool Button::getHiddenStatus()
{
	return hidden;
}