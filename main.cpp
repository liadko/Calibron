
#include "header.h"



int main()
{
	//Window
	sf::RenderWindow window(sf::VideoMode(width, height), "Program", sf::Style::Close, sf::ContextSettings(24, 8, 8));
	//window.setFramerateLimit(100);

	cout << "Calibron 12\n\n";

	cout << "Click: advance one move.\n";
	cout << "Space: advance until solved.\n";
	cout << "Press B: backtrack.\n\n";
	cout << "Press S: screenshot.\n\n";

	

	bool advancing = false;

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
				else if (event.key.code == sf::Keyboard::S)
					saveScreenshot(window);


		//Algorithm
		if (advancing)
		{
			
			//for (int i = 0; i < 5000 && advancing; i++)
				if (advance())
				{
					cout << "Puzzle is solved. Press 'B' to backtrack and look for a symmetry of the solution.\n";
					
					advancing = false;

				}
		
		}




		draw(window);

	}

	return 0;
}


//Timing code:

//sf::Clock clock;

//auto start(clock.getElapsedTime().asMilliseconds());
// 
// perform
// 
//auto end(clock.getElapsedTime().asMilliseconds());
//std::cout << end - start << '\n';