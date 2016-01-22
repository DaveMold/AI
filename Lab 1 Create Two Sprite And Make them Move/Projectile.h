#ifndef _PROJECTILE_H
#define _PROJECTILE_H

//includes
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Pvector.h"

class Projectile {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float speed;
	sf::Vector2f direction;
	float spritePosOffSet;
	sf::Vector2f startPos;
	int range;
	Pvector*  velocity;// = 0.03;
	Pvector* acceleration;// = 0.01;
	float maxSteeringForce;// = 1.0f;
	Pvector* location;
public:
	Projectile(sf::Vector2f dir, sf::Vector2f pos);//!< constructor.
	~Projectile();
	void SetPos(sf::Vector2f pos);//!<  sets the projectiles sprite posisiton.
	bool Update();//!<  updates the projectile to translate to a location and delete its self when it has excided its range.
	bool UpdateSeeking(Pvector target);//!< seeks to the target location and delets its self on collision.
	void Draw(sf::RenderWindow &w);//!<  Draws the projectile.
	bool ScreenBounds(sf::RenderWindow &w);//!< basic screen rap for the large area.
	sf::Vector2f GetPos();//!< gets the projectile posision to use for collision detection for other classes.
	sf::FloatRect GetBounds();//!< gets the Bounds posision to use for collision detection for other classes.
};
#endif