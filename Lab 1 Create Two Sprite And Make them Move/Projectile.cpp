#include "stdafx.h"
#include "Projectile.h"

Projectile::Projectile(sf::Vector2f dir, sf::Vector2f pos) : direction(dir), range(400), spritePosOffSet(8), speed(7.0f) {
	sprite.setPosition(pos.x - spritePosOffSet/2, pos.y - spritePosOffSet/2);
	startPos = pos;
	texture.loadFromFile("Resorces/Img/Projectile.png");
	sprite.setTexture(texture);
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