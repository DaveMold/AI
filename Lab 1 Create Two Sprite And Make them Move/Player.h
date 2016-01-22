#ifndef PLAYER_H
#define PLAYER_H

#include "stdafx.h"

class Player {

	//vairbles
	float speed = 2.0f;
	float spritePosOffSet = 16;//sprite size / 2; sprite size == 32
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Sprite sprite;
	sf::View followPlayer, miniMapView;
    Pvector* velocity;
public:
	Player();//!< constructor.
	void Move();//!< updates the position with the values from the other methods
	sf::Vector2f ScreenRap(sf::Vector2f pos, sf::Vector2f &w); //!< basic screen rap on the large area.
	void Update(sf::Vector2f &w); //!< handles the keyboard input and what should happen in each circumstance as well as update the views for the viewport and minimap.
	void SetPos(sf::Vector2f pos);
	sf::Vector2f GetPos();
	sf::View getView();
	sf::View getMiniMapView();
	void SpeedUp();//!< increase the speed vairble.
	void SlowDown();//!< decreases the speed vairble.
	void Draw(sf::RenderWindow &w);//!< draws the player.
	sf::FloatRect GetBounds();//!< gets the players size for collision detection in other classes.
    Pvector* getVelocity() { return velocity; } //!< return the velocity of the player.
};
#endif
