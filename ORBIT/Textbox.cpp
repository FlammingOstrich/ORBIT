#include "Textbox.h"

Textbox::Textbox(int size, sf::Vector2f position, sf::Font& font, sf::Color color, int lim, bool setSel, bool allowNumber, bool allowCharacter, bool allowSpecialChar, std::string placeholderText)
{
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	textbox.setFont(font);
	textbox.setPosition(position);
	isSel = setSel;
	allowNum = allowNumber;
	allowChar = allowCharacter;
	allowSpecChar = allowSpecialChar;
	pos = position;

	placeholder = placeholderText;

	if (lim == -1)
	{
		setLimit(false);
	}
	else if (lim >= 0)
	{
		setLimit(true, lim);
	}



	calculateContainer();

	if (isSel)
	{
		textbox.setString(placeholder + "_");
	}
	else
	{
		textbox.setString(placeholder);
	}
}

void Textbox::calculateContainer()
{
	std::string filler = placeholder;
	if (!allowSpecChar)
	{
		if (hasLimit)
		{
			for (int i = 0; i < limit; i++)
			{
				filler.append("0");
			}
		}
		else
		{
			for (int i = 0; i < 11; i++);
			{
				filler.append("0");
			}
		}
		textbox.setString(filler + "_");
	}
	else if (allowSpecChar)
	{
		if (hasLimit)
		{
			for (int i = 0; i < limit; i++)
			{
				filler.append("#");
			}
		}
		else
		{
			for (int i = 0; i < 11; i++);
			{
				filler.append("#");
			}
		}
	
		textbox.setString(filler + "_");
	}
	

	leftBoundary = pos.x;
	rightBoundary = leftBoundary + textbox.getLocalBounds().width;
	upBoundary = pos.y;
	downBoundary = upBoundary + textbox.getLocalBounds().height;

	boxWidth = textbox.getLocalBounds().width;
	boxHeight = textbox.getLocalBounds().height;

	rectangle.setSize({ boxWidth + 3, boxHeight + 7 });
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(3);
	rectangle.setPosition(pos);
}

void Textbox::setSelected(bool setSel)
{
	isSel = setSel;
	if (!isSel)
	{
		textbox.setString(placeholder + text.str());
	}
	else
	{
		textbox.setString(placeholder + text.str() + "_");
	}
}

void Textbox::clearField()
{
	text.str("");

	if (!isSel)
	{
		textbox.setString(placeholder);
	}
	else
	{
		textbox.setString(placeholder + "_");
	}
}

void Textbox::setPosition(sf::Vector2f position)
{
	textbox.setPosition(position);
}

void Textbox::setLimit(bool trueOrFalse, int lim)
{
	hasLimit = trueOrFalse;
	limit = lim;
}

void Textbox::setLimit(bool trueOrFalse)
{
	hasLimit = trueOrFalse;
}

void Textbox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}

void Textbox::drawTo(sf::RenderWindow& window)
{
	window.draw(textbox);

	window.draw(rectangle);
}

std::string Textbox::getText()
{
	double x = std::stod("33.3");
	return text.str();
}

void Textbox::allowNumber(bool allow)
{
	allowNum = allow;
}

void Textbox::allowCharacter(bool allow)
{
	allowChar = allow;
}

void Textbox::allowSpecialCharacter(bool allow)
{
	allowSpecChar = allow;
}
bool Textbox::getSelectedStatus()
{
	return isSel;
}

void Textbox::typedOn(sf::Event input)
{
	if (isSel)
	{
		int charInput = input.text.unicode;
		if (charInput != ENTER_KEY && charInput != ESCAPE_KEY)
		{
			if (!allowNum)
			{
				if (charInput >= 48 && charInput <= 57)
				{
					return;
				}
			}
			if (!allowChar)
			{
				if (charInput == 32 || (charInput >= 65 && charInput <= 90) || (charInput >= 97 && charInput <= 122))
				{
					return;
				}
			}
			if (!allowSpecChar)
			{
				if ((charInput >= 0 && charInput <= 7) || (charInput >= 9 && charInput <= 12) || (charInput >= 14 && charInput <= 26) || (charInput >= 28 && charInput <= 31) || (charInput >= 33 && charInput <= 47) || (charInput >= 59 && charInput <= 64) || (charInput >= 91 && charInput <= 96) || (charInput >= 123 && charInput <= 127))
				{
					return;
				}
			}

			if (charInput < 128)
			{
				if (hasLimit)
				{
					if ((int)text.str().length() < limit)
					{
						inputLogic(charInput);
					}
					else if ((int)text.str().length() >= limit && charInput == DELETE_KEY)
					{
						deleteChar();
					}
				}
				else
				{
					inputLogic(charInput);
				}
			}
		}
	}
}


void Textbox::mouseSelect(sf::Vector2i mousePos)
{
	if (mousePos.x <= rightBoundary && mousePos.x >= leftBoundary && mousePos.y >= upBoundary && mousePos.y <= downBoundary)
	{
		if (isSel == true)
		{
			return;
		}
		else
		{
			setSelected(true);
		}
	}
	else
	{
		setSelected(false);
	}
}


void Textbox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ESCAPE_KEY && charTyped != ENTER_KEY)
	{
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (text.str() != placeholder)
		{
			deleteChar();
		}
	}
	textbox.setString(placeholder + text.str() + "_");
}

void Textbox::deleteChar()
{
	std::string newText = text.str().substr(0, text.str().length() - 1);

	text.str("");
	text << newText;

	textbox.setString(placeholder + text.str());
}

bool Textbox::checkIfEmpty()
{
	if (text.str().length() > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Textbox::showErrorMessage(std::string error)
{
	textbox.setString(error);
	float textWidth = textbox.getLocalBounds().width;
	float textHeight = textbox.getLocalBounds().height;

	rectangle.setSize({ textWidth + 3, textHeight + 12 });
}

void Textbox::setText(std::string text)
{
	textbox.setString(placeholder + text);

	float textWidth = textbox.getLocalBounds().width;
	float textHeight = textbox.getLocalBounds().height;

	rectangle.setSize({ textWidth + 3, textHeight + 12 });
}