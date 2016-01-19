#include "Projectile.h"

Projectile::Projectile(sf::Vector2f dir, sf::Vector2f pos) : direction(dir) {
	sprite.setPosition(pos);
	texture.loadFromFile("Resorces/Img/Projectile.png");
	sprite.setTexture(texture);
	spritePosOffSet = 8;
	speed = 3.0f;
}

Projectile::~Projectile() {

}

void Projectile::SetPos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Projectile::Update() {
	sf::Vector2f temp = sprite.getPosition();

	temp += (direction * speed);
	SetPos(temp);
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