#include <SFML/Graphics.hpp>
#include "celestialObject.h"
#include "Textbox.h"
#include "Button.h"
#include "objectSprite.h"
#include <iostream>
#include <string>
#include <cmath>

#define pi 3.14159265358979323846

using namespace std;

//yellow, gray, red, brown, blue, white
int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 100;
	sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Title", sf::Style::Fullscreen, settings);
	window.setFramerateLimit(false);
	window.setKeyRepeatEnabled(true);
	sf::Event event;


	//Variables to store information to be passed to celestialObject
	double radius = 0;
	string name;
	float timePassed = 0, timePaused = 0;
	sf::Color chosenColor = sf::Color::Color(0, 0, 0, 0);

	//vector to store the objects to work with
	vector<celestialObject> objects;
	objects.emplace_back(celestialObject(30, 1.9891e30, "Sun", window.getSize().x/2, window.getSize().y/2, objects.size(), sf::Color::Yellow));
	celestialObject::defineMeterToPixelRatio(2, window.getSize().y);
	celestialObject::setPointCount(10000);

	//stores font for all text
	sf::Font Font;
	if (!Font.loadFromFile("arial.ttf"))
	{
		// Error...
	}


	bool spritePlaced = false;
	bool vectorDrawn = false;
	bool runSim = false;

	//Text fields for information to be added
	Textbox objectNameTextBox(20, { 50, 1350 }, Font, sf::Color::White, 15, false, true, true, true, "Object Name: ");
	Textbox objectRadiusTextBox(20, { 450, 1350 }, Font, sf::Color::White, 5, false, true, false, true, "Object Radius: ");
	Textbox timeScaleTextBox(20, { 2300, 50 }, Font, sf::Color::White, -1, false, false, false, false, "Time Scale:");
	Textbox chosenColorTextField(20, { 2300, 1350 }, Font, sf::Color::White, -1, false, false, false, false, "Chosen Color: ");
	timeScaleTextBox.setText("1 sec/sec");



	//buttons to add planets/stars and to start/stop the sim
	Button addPlanet("Add Planet", 20, Font, { 1300, 1350 }, { 100, 200 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, false);
	Button startSim("Start Simulation", 20, Font, { 1700, 1350 }, { 100, 200 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, false);
	Button speedTime("Speed Time", 20, Font, { 2300, 100 }, { 100, 200 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, false);
	Button slowTime("Slow Time", 20, Font, { 2300, 150 }, { 100, 200 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, false);
	Button color("Choose Color", 20, Font, { 2000, 1350 }, { 100, 200 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, false);
	Button yellow("Yellow", 20, Font, { 100, 1200 }, { 100, 50 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, true);
	Button gray("Gray", 20, Font, { 300, 1200 }, { 100, 50 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, true);
	Button red("Red", 20, Font, { 500, 1200 }, { 100, 50 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, true);
	Button brown("Brown", 20, Font, { 700, 1200 }, { 100, 50 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, true);
	Button blue("Blue", 20, Font, { 900, 1200 }, { 100, 50 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, true);
	Button white("White", 20, Font, { 1100, 1200 }, { 100, 50 }, sf::Color::Color(255, 255, 255, 255), sf::Color::Color(128, 128, 128, 255), sf::Color::White, sf::Color::Black, 2, true);
	addPlanet.autoSizeAdjust();
	startSim.autoSizeAdjust();
	speedTime.autoSizeAdjust();
	slowTime.autoSizeAdjust();
	color.autoSizeAdjust();
	yellow.autoSizeAdjust();
	gray.autoSizeAdjust();
	red.autoSizeAdjust();
	brown.autoSizeAdjust();
	blue.autoSizeAdjust();
	white.autoSizeAdjust();

	sf::Clock clock;
	float time = 0;
	float totalTime = 0;

	while (window.isOpen())
	{
		//checks if the return key is pressed and deselects all textboxes if true
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			objectNameTextBox.setSelected(false);
			objectRadiusTextBox.setSelected(false);
		}
		//checks if the escape key is pressed and deselects all textboxes if true
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			objectNameTextBox.setSelected(false);
			objectRadiusTextBox.setSelected(false);
		}
		//checks if the left mouse button is pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{	//checks if the mouse is over and of the buttons when pressed and selects them if true
			if (addPlanet.isMouseOver(sf::Mouse::getPosition(window)))
			{
				addPlanet.setState(true);
			}
			if (startSim.isMouseOver(sf::Mouse::getPosition(window)))
			{
				startSim.setState(true);
			}
			if (speedTime.isMouseOver(sf::Mouse::getPosition(window)))
			{
				speedTime.setState(true);
			}
			if (slowTime.isMouseOver(sf::Mouse::getPosition(window)))
			{
				slowTime.setState(true);
			}
			if (color.isMouseOver(sf::Mouse::getPosition(window)))
			{
				color.setState(true);
			}
			if (yellow.isMouseOver(sf::Mouse::getPosition(window)) && !yellow.getHiddenStatus())
			{
				yellow.setState(true);
			}
			if (gray.isMouseOver(sf::Mouse::getPosition(window)) && !gray.getHiddenStatus())
			{
				gray.setState(true);
			}
			if (red.isMouseOver(sf::Mouse::getPosition(window)) && !red.getHiddenStatus())
			{
				red.setState(true);
			}
			if (brown.isMouseOver(sf::Mouse::getPosition(window)) && !brown.getHiddenStatus())
			{
				brown.setState(true);
			}
			if (blue.isMouseOver(sf::Mouse::getPosition(window)) && !blue.getHiddenStatus())
			{
				blue.setState(true);
			}
			if (white.isMouseOver(sf::Mouse::getPosition(window)) && !white.getHiddenStatus())
			{
				white.setState(true);
			}
		}
		else
		{
			addPlanet.setState(false);
			startSim.setState(false);
			speedTime.setState(false);
			slowTime.setState(false);
			color.setState(false);
			yellow.setState(false);
			gray.setState(false);
			red.setState(false);
			brown.setState(false);
			blue.setState(false);
			white.setState(false);
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			//checks if a textfield is having text entered into it
			if (event.type == sf::Event::TextEntered)
			{
				objectNameTextBox.typedOn(event);
				objectRadiusTextBox.typedOn(event);
			}
			if (event.type == sf::Event::KeyPressed)
			{

			}
			//checks for mouse click
			if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
			{
				//checks if the textboxes were clicked
				objectNameTextBox.mouseSelect(sf::Mouse::getPosition(window));
				objectRadiusTextBox.mouseSelect(sf::Mouse::getPosition(window));

				//makes sure the user entered all necessary data
				if (addPlanet.isMouseOver(sf::Mouse::getPosition(window)))
				{
					addPlanet.setState(false);

					if((chosenColor.r == 0 && chosenColor.g == 0 && chosenColor.b == 0 && chosenColor.a == 0) || !objectNameTextBox.checkIfEmpty() || !objectRadiusTextBox.checkIfEmpty())
					{
						if ((chosenColor.r == 0 && chosenColor.g == 0 && chosenColor.b == 0 && chosenColor.a == 0))
						{
							chosenColorTextField.showErrorMessage("NO COLOR CHOSEN!!!");
						}
						if (!objectNameTextBox.checkIfEmpty())
						{
							objectNameTextBox.showErrorMessage("NO NAME ENTERED!!!");
						}
						if (!objectRadiusTextBox.checkIfEmpty())
						{
							objectRadiusTextBox.showErrorMessage("NO RADIUS ENTERED!!!");
						}

						continue;
					}
					

					//converts user input into usable parameters for celestialObject
					string radiusText = objectRadiusTextBox.getText();

					if (objectNameTextBox.getText().length() > 0)
					{
						name = objectNameTextBox.getText();
					}
					if (radiusText.length() > 0)
					{
						radius = stod(radiusText);
					}

					//resets textboxs
					objectNameTextBox.clearField();
					objectRadiusTextBox.clearField();
					chosenColorTextField.clearField();

					//creates sprite for the soon to be created celestialObject instance
					objects.emplace_back(celestialObject(radius, name, window, event, objects.size(), objects, chosenColor));
					chosenColor = sf::Color::Color(0, 0, 0, 0);
				}


				else if (startSim.isMouseOver(sf::Mouse::getPosition(window)) && !runSim)
				{
					runSim = true;
					startSim.setText("Stop Simulation");
				}
				else if (startSim.isMouseOver(sf::Mouse::getPosition(window)) && runSim)
				{
					runSim = false;
					startSim.setText("Start Simulation");
				}

				else if (speedTime.isMouseOver(sf::Mouse::getPosition(window)))
				{
					timeScaleTextBox.setText(celestialObject::incrementTimeWarp(1));
				}
				else if (slowTime.isMouseOver(sf::Mouse::getPosition(window)))
				{
					timeScaleTextBox.setText(celestialObject::incrementTimeWarp(-1));
				}

				else if (color.isMouseOver(sf::Mouse::getPosition(window)))
				{
					yellow.setHidden(false);
					gray.setHidden(false);
					red.setHidden(false);
					brown.setHidden(false);
					blue.setHidden(false);
					white.setHidden(false);
				}

				else if (yellow.isMouseOver(sf::Mouse::getPosition(window)))
				{
					chosenColor = sf::Color::Yellow;
					chosenColorTextField.setText("Yellow");
					yellow.setHidden(true);
					gray.setHidden(true);
					red.setHidden(true);
					brown.setHidden(true);
					blue.setHidden(true);
					white.setHidden(true);
				}
				else if (gray.isMouseOver(sf::Mouse::getPosition(window)))
				{
					chosenColor = sf::Color::Color(128, 128, 128, 255);
					chosenColorTextField.setText("Gray");
					yellow.setHidden(true);
					gray.setHidden(true);
					red.setHidden(true);
					brown.setHidden(true);
					blue.setHidden(true);
					white.setHidden(true);
				}
				else if (red.isMouseOver(sf::Mouse::getPosition(window)))
				{
					chosenColor = sf::Color::Red;
					chosenColorTextField.setText("Red");
					yellow.setHidden(true);
					gray.setHidden(true);
					red.setHidden(true);
					brown.setHidden(true);
					blue.setHidden(true);
					white.setHidden(true);
				}
				else if (brown.isMouseOver(sf::Mouse::getPosition(window)))
				{
					chosenColor = sf::Color::Color(163, 73, 46, 255);
					chosenColorTextField.setText("Brown");
					yellow.setHidden(true);
					gray.setHidden(true);
					red.setHidden(true);
					brown.setHidden(true);
					blue.setHidden(true);
					white.setHidden(true);
				}
				else if (blue.isMouseOver(sf::Mouse::getPosition(window)))
				{
					chosenColor = sf::Color::Color(91, 93, 223, 255);
					chosenColorTextField.setText("Blue");
					yellow.setHidden(true);
					gray.setHidden(true);
					red.setHidden(true);
					brown.setHidden(true);
					blue.setHidden(true);
					white.setHidden(true);
				}
				else if (white.isMouseOver(sf::Mouse::getPosition(window)))
				{
					chosenColor = sf::Color::White;
					chosenColorTextField.setText("White");
					yellow.setHidden(true);
					gray.setHidden(true);
					red.setHidden(true);
					brown.setHidden(true);
					blue.setHidden(true);
					white.setHidden(true);
				}
			}
		}

		window.clear();
		
		if (runSim)
		{
			timePassed = clock.getElapsedTime().asSeconds() - timePaused;
			totalTime = timePassed;
			celestialObject::simulate(window, objects, timePassed);
			clock.restart();
		}
		else
		{
			celestialObject::pauseSim(window, objects);
			clock.restart();
		}



		objectNameTextBox.drawTo(window);
		objectRadiusTextBox.drawTo(window);
		timeScaleTextBox.drawTo(window);
		chosenColorTextField.drawTo(window);


		addPlanet.drawTo(window);
		startSim.drawTo(window);
		speedTime.drawTo(window);
		slowTime.drawTo(window);
		color.drawTo(window);
		yellow.setHidden(false);
		gray.drawTo(window);
		red.drawTo(window);
		brown.drawTo(window);
		blue.drawTo(window);
		white.drawTo(window);

		window.display();
	}

	return 0;
}




void realSolarSystem(int meterToPixelRatio)
{

}