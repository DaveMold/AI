#ifndef _PROJECTILE_H
#define _PROJECTILE_H

//includes
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Pvector.h"

using namespace std;

class Projectile {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speed;
	float acceleration;// = 0.01;
	sf::Vector2f direction;
	float spritePosOffSet;
	sf::Vector2f startPos;
	int range;
public:
	Projectile(sf::Vector2f dir, sf::Vector2f pos);
	~Projectile();
	void SetPos(sf::Vector2f pos);
	bool Update();
	void Draw(sf::RenderWindow &w);
	bool ScreenBounds(sf::RenderWindow &w);
	sf::Vector2f GetPos();
	sf::FloatRect GetBounds();
};
#endif