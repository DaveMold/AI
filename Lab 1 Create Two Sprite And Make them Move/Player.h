#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"

class Player {

	//vairbles
	float speed = 1.0f;
	float spritePosOffSet = 16;//sprite size / 2; sprite size == 32
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Sprite sprite;
	sf::View followPlayer, miniMapView;
public:
	Player();
	void Move();
	sf::Vector2f ScreenRap(sf::Vector2f pos, sf::Vector2f &w);
	void Update(sf::Vector2f &w);
	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	sf::View getView();
	sf::View getMiniMapView();
	void SpeedUp();
	void SlowDown();
	void Draw(sf::RenderWindow &w);
};
#endif
