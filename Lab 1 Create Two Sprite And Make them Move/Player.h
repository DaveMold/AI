#ifndef PLAYER_H
#define PLAYER_H

<<<<<<< HEAD
#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include "ProjectileManager.h"

=======
>>>>>>> 698b49a611378ba2daea3488a09cb128c5ef1448
class Player {

	//vairbles
	float speed = 1.0f;
	float spritePosOffSet = 16;//sprite size / 2; sprite size == 32
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Sprite sprite;

public:
	Player();
	void Move();
	sf::Vector2f ScreenRap(sf::Vector2f pos, sf::RenderWindow &w);
	void Update(sf::RenderWindow &w);
	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	void SpeedUp();
	void SlowDown();
	void Draw(sf::RenderWindow &w);

};
#endif
