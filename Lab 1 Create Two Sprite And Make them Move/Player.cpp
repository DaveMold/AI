#include "Player.h"

Player::Player() {
	texture.loadFromFile("Resorces/Img/SpaceShip1-White/spaceship1_small-White.png");
	sprite.setTexture(texture);
	sprite.setPosition(400, 100);
	sprite.setOrigin(spritePosOffSet,spritePosOffSet);
    sprite.setRotation(90.0f);
}

void Player::Move() {
	//sprite One
	/*sf::Vector2f temp = sprite.getPosition();*/
    float rotation = sprite.getRotation();
    rotation *= (3.14f / 180);
	direction = sf::Vector2f(cos(rotation), sin(rotation));
    
	sf::Vector2f temp = direction * speed;
	sprite.move(temp);
}

sf::Vector2f Player::ScreenRap(sf::Vector2f pos, sf::RenderWindow &w) {
	if (pos.x < 0 - (spritePosOffSet * 2))
		pos.x = w.getSize().x;
	else if (pos.x > w.getSize().x)
		pos.x = 1 - (spritePosOffSet * 2);
	if (pos.y < 0 - (spritePosOffSet * 2))
		pos.y = w.getSize().y;
	else if (pos.y > w.getSize().y + 1)
		pos.y = 1 - (spritePosOffSet * 2);
	return pos;
}

void Player::Update(sf::RenderWindow &w) {
	//Key input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		sprite.rotate(-1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.rotate(1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		SpeedUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		SlowDown();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		speed = 0;
	}
	Move();
	/*sprite.Rotation(rotation);*/
	sprite.setPosition(ScreenRap(sprite.getPosition(), w));
}

void Player::SpeedUp() {
	speed += 1.0f;
}

void Player::SlowDown() {
	speed -= 1.0f;
}

void Player::SetPos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

sf::Vector2f Player::GetPos() {
	return sprite.getPosition();
}

void Player::Draw(sf::RenderWindow &w) {
	w.draw(sprite);
}