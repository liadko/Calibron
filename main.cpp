
#include "header.h"





int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(width, height), "Program", sf::Style::Close, sf::ContextSettings(24, 8, 8));
	//window.setFramerateLimit(100);

	//sf::Clock clock;

	cout << "Calibron 12\n\n";

	cout << "Click: advance one move.\n";
	cout << "Space: advance until solved.\n";
	cout << "Press B: backtrack.\n\n\n";

	initOutlineShape();

	bool advancing = false;
	int solvedCount = 0;

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
			//for (int i = 0; i < 5000 && advancing; i++)
				if (advance())
				{
					cout << "Puzzle is solved. Press 'B' to backtrack and look for a symmetry of the solution.\n";
					advancing = false;


					//draw(window); //draw the finished frame
					//solvedCount++;
					//saveScreenshot(window, solvedCount);
					//try backtrack, stop advancing if can't
					//backtrack();

				}



		//auto end(clock.getElapsedTime().asMilliseconds());
		//advancing = false;
		//std::cout << end - start << '\n';
		}




		draw(window);

	}

	return 0;
}
