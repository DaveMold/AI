#pragma once

#include "stdafx.h"

#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-d.lib")
#pragma comment(lib,"sfml-audio-d.lib")
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else
#pragma comment(lib,"sfml-graphics.lib")
#pragma comment(lib,"sfml-audio.lib")
#pragma comment(lib,"sfml-system.lib")
#pragma comment(lib,"sfml-window.lib")
#pragma comment(lib,"sfml-network.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


int main()
{
	int numEnemies = 10;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Sprites");
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	const int window_height = desktop.height;
	const int window_width = desktop.width;
    window.setFramerateLimit(60);

	sf::Clock clock = sf::Clock();
	sf::Time elapsedTime;
	Player player = Player();
	EnemyManager eManager;
	
	//create some Enemies
	for (int i = 0; i < numEnemies; i++) {
		Enemy * e = new Enemy(window_width / 3, window_height / 3); //Starts all enemy in the center of the screen.
		eManager.addEnemy(e);
	}
	
    for (int i = 0; i < 1; i++)
    {
        Factory * f = new Factory(100, 100);
        eManager.addFactory(f);
    }

	// Start game loop
	while (window.isOpen()) {
		// Process events
		sf::Event Event;

		while (window.pollEvent(Event)) {
			
			

			switch (Event.type) {
				// Close window : exit
				case sf::Event::Closed:
					window.close();
					break;
				default:
					break;
			}//end switch
		}//end while
		player.Update(window);
		eManager.flocking();
		 //prepare frame
		window.clear();
		player.Draw(window);
		eManager.Draw(window);
		// Finally, display rendered frame on screen
		window.display();
		clock.restart();
	} //loop back for next frame

	return EXIT_SUCCESS;

}
