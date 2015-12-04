#ifndef ENEMY_H
#define ENEMY_H

#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <stdlib.h> 

class Enemy {

	//vairbles
	bool slow_before_player;
	float rotation = 0.2;//Radiants
	float speed = 3.0f;
	float max_speed = 3.0f;
	float decelerate = .1f;
	float radius_slow_approach = 5;
	float spritePosOffSet = 16;//sprite size / 2; sprite size == 32
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Sprite sprite;

public:
	Enemy();
	void Move(sf::Vector2f target);
	sf::Vector2f ScreenRap(sf::Vector2f pos, sf::RenderWindow &w);
	void Update(sf::RenderWindow &w, sf::Vector2f target);
	void SetPos(sf::Vector2f pos);
	void SpeedUp();
	void SlowDown();
	void Draw(sf::RenderWindow &w);

};
#endif