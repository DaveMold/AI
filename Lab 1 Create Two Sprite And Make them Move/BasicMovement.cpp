#pragma once
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

//#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <windows.h>
#include <iostream>
#include <math.h>
#include "Player.h"
#include "Enemy.h"


int main()
{
	int numEnemies = 10;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Sprites");
    window.setFramerateLimit(60);
	sf::Clock clock = sf::Clock();
	sf::Time elapsedTime;
	Player player = Player();
	//Enemy enemy = Enemy();
	std::vector<Enemy*> Enemies;
	//create some Enemies
	for (int i = 0; i < numEnemies; i++) {
		Enemies.push_back(new Enemy());
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
		for (int i = 0; i < Enemies.size(); i++) {
			Enemies[i]->Update(window, player.GetPos());
		}
		 //prepare frame
		window.clear();
		player.Draw(window);
		for (int i = 0; i < Enemies.size(); i++) {
			Enemies[i]->Draw(window);
		}
		// Finally, display rendered frame on screen
		window.display();
		clock.restart();
	} //loop back for next frame

	return EXIT_SUCCESS;

}
