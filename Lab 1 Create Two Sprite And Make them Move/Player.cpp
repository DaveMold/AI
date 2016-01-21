#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

Player::Player() {
	texture.loadFromFile("Resorces/Img/Player/Player.png");
	sprite.setTexture(texture);
	sprite.setPosition(400, 100);
	followPlayer.setCenter(400, 300);
	followPlayer.setSize(800, 600);
	sprite.setOrigin(spritePosOffSet,spritePosOffSet);
    sprite.setRotation(90.0f);
}

void Player::Move() {
	//sprite One
	sf::Vector2f temp = sprite.getPosition();
    float rotation = sprite.getRotation();
    rotation *= (3.14f / 180);
	direction = sf::Vector2f(cos(rotation), sin(rotation));
    
	temp += direction * speed;
	SetPos(temp);
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
	if (InputManager::instance()->Held("Left")) {
		sprite.rotate(-1.0f);
	}
	if (InputManager::instance()->Held("Right")) {
        sprite.rotate(1.0f);
	}
	if (InputManager::instance()->Held("Up")) {
		SpeedUp();
	}
	if (InputManager::instance()->Held("Down")) {
		SlowDown();
	}
	if (InputManager::instance()->Pressed("End")) {
		speed = 0;
	}
	if (InputManager::instance()->Pressed("PageDown")) {
		ProjectileManager::instance()->AddProjectile(direction, sprite.getPosition());
	}
	Move();
	/*sprite.Rotation(rotation);*/
	moveView(sprite.getPosition());
	sprite.setPosition(ScreenRap(sprite.getPosition(), w));
}

void Player::SpeedUp() {
    speed <= 2.8f ? speed += .2f : speed = 3.0f;
}

void Player::SlowDown() {
    speed >= .2f ? speed -= .2f : speed = 0;
}

void Player::SetPos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

sf::Vector2f Player::GetPos() {
	return sprite.getPosition();
}

sf::View Player::getView() {
	return followPlayer;
}

void Player::moveView(sf::Vector2f pos) {
	followPlayer.move(pos);
}

void Player::Draw(sf::RenderWindow &w) {
	w.draw(sprite);
}