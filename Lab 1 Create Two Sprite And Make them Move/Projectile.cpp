#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(sf::Vector2f dir, sf::Vector2f pos) : direction(dir), range(400), spritePosOffSet(16), speed(7.0f) {
	sprite.setPosition(pos.x - spritePosOffSet, pos.y - spritePosOffSet);
	startPos = pos;
	location = new Pvector(pos.x, pos.y);
	texture.loadFromFile("Resorces/Img/Projectile.png");
	sprite.setTexture(texture);
	acceleration = new Pvector(0, 0);
	velocity = new Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
}

Projectile::~Projectile() {

}

void Projectile::SetPos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

bool Projectile::Update() {
	sf::Vector2f temp = sprite.getPosition();
	if (sqrt(pow(startPos.x - temp.x, 2.0f) + pow(startPos.y - temp.y, 2.0f)) > range)
	{
		return true;//return true if projectile is to be removed from the list as it has reached its range.
	}
	temp += (direction * speed);
	SetPos(temp);
	return false;
}

bool Projectile::UpdateSeeking(Pvector target) {
	sf::Vector2f temp = sprite.getPosition();
	if (sqrt(pow(startPos.x - temp.x, 2.0f) + pow(startPos.y - temp.y, 2.0f)) > range)
	{
		return true;//return true if projectile is to be removed from the list as it has reached its range.
	}
	Pvector desired = target - temp;
	// desired.subVector(playerLocation);  // A vector pointing from the location to the target
	// Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(speed);
	// Steering = Desired minus Velocity
	*acceleration = desired - *velocity;
	acceleration->limit(maxSteeringForce);  // Limit to maximum steering force

											//To make the slow down not as abrupt
	acceleration->mulScalar(.4);
	// Update velocity
	velocity->addVector(*acceleration);
	// Limit speed
	velocity->limit(speed);
	location->addVector(*velocity);
	// Reset accelertion to 0 each cycle
	acceleration->mulScalar(0);
	SetPos(sf::Vector2f(location->x,location->y));
	return false;
}

void Projectile::Draw(sf::RenderWindow &w) {
	w.draw(sprite);
}

bool Projectile::ScreenBounds(sf::RenderWindow &w) {
	//checks if the projectile has gone off the screen.
	sf::Vector2f pos = sprite.getPosition();
	if ((pos.x < 0 - (spritePosOffSet * 2)) || (pos.x > w.getSize().x) || (pos.y < 0 - (spritePosOffSet * 2)) || (pos.y > w.getSize().y + 1))
		return true;
	else
		return false;
}

sf::Vector2f Projectile::GetPos() {
	return sprite.getPosition();
}

sf::FloatRect Projectile::GetBounds() {
	return sprite.getGlobalBounds();
}