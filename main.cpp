#include <SFML/Graphics.hpp>
#include <iostream>

using std::vector;
using std::cout;

#include "header.h"





int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(width, height), "Program", sf::Style::Close, sf::ContextSettings(24, 8, 8));
	//window.setFramerateLimit(100);

	//sf::Clock clock;

	cout << "Calibron 12: Invented by Theodore Edison (son of tommy).\n";
	cout << "Goal: Fit all 12 pieces into a perfect square.\n";
	cout << "Only one solution, 8 if you count the symmetries.\n\n";

	cout << "Left Click: advance one move.\n";
	//cout << "Right Click: backtrack - go back to last time you weren't sure about what to do\n";
	//cout<< "and remember not to repeat what you did.\n";
	cout << "Space: advance until completion.\n";


	initOutlineShape();

	bool advancing = false;
	//int solvedCount = 0;

	//Main Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed) window.close();

			else if (event.type == sf::Event::MouseButtonPressed)
				advance();

			else if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
					advancing ^= true;
				else if (event.key.code == sf::Keyboard::B)
					backtrack();


		//const auto& mousePos = sf::Mouse::getPosition(window);


		//Algorithm
		if (advancing)
		{
			//auto start(clock.getElapsedTime().asMilliseconds());


			//while(true)
			//for (int i = 0; i < 5000; i++)
			if (advance())
			{
				cout << "Puzzle is solved. Right click to backtrack and look for another solution.\n";
				advancing = false;
				//break;


				//draw(window); //draw the finished frame
				//solvedCount++;
				//saveScreenshot(window, solvedCount);
				//try backtrack, stop advancing if can't
				//backtrack();

			}
			//else break;



		//auto end(clock.getElapsedTime().asMilliseconds());
		//advancing = false;
		//std::cout << end - start << '\n';
		}




		draw(window);

	}

	return 0;
}
