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

#include "windows.h"

//#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <windows.h>
#include <iostream>
#include <math.h>
#include "Player.h"
#include "EnemyManager.h"
#include "ProjectileManager.h"
#include "InputManager.h"


int main()
{
	int numEnemies = 10;

	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Moving Sprites");
	//used for getting the mouse posistion.
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	const int window_height = desktop.height;
	const int window_width = desktop.width;

    window.setFramerateLimit(60);
	sf::Clock clock = sf::Clock();
	sf::Time elapsedTime;

	//BackGround
	sf::Texture backGroundTexture;
	sf::Sprite backGroundSprite;
	backGroundTexture.loadFromFile("Resorces/Img/background.png");
	backGroundSprite.setTexture(backGroundTexture);
	backGroundSprite.setPosition(0, 0);
	

	//Entities
	Player player = Player();
	EnemyManager eManager;
	ProjectileManager* projectileMgr = ProjectileManager::instance();
	InputManager* inputMgr = InputManager::instance();

	//set up world.
	sf::Vector2f worldBounds;
	worldBounds.x = window.getSize().x * 9.0f;
	worldBounds.y = window.getSize().y * 9.0f;
	
	//create some Enemies
	for (int i = 0; i < numEnemies; i++) {
		Swarmer * e = new Swarmer(window_width / 3, window_height / 3); //Starts all enemy in the center of the screen.
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
		InputManager::instance()->UpdatePressedKeys(Event);
		player.Update(worldBounds);
		projectileMgr->Update(window);

		//Get the mouse posistion and send it to the swarm method.
		POINT mousePos;
		if (GetCursorPos(&mousePos))
		{
			if (ScreenToClient(window.getSystemHandle(),  &mousePos))
			{
				//std::cout << "mouse pos : (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
				eManager.swarming(Pvector(mousePos.x, mousePos.y));
			}
		}
		eManager.flocking();
		eManager.swarmECollision();

		 //prepare frame
		window.clear();
		window.setView(player.getView());
		window.draw(backGroundSprite);
		player.Draw(window);
		projectileMgr->Draw(window);
		eManager.Draw(window, worldBounds);

		window.setView(player.getMiniMapView());
		window.draw(backGroundSprite);
		player.Draw(window);
		projectileMgr->Draw(window);
		eManager.Draw(window, worldBounds);
		
		// Finally, display rendered frame on screen
		window.display();
		clock.restart();
	} //loop back for next frame

	return EXIT_SUCCESS;

}
