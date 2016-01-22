#include "stdafx.h"
#include "Player.h"
#include "InputManager.h"

Player::Player() {
	texture.loadFromFile("Resorces/Img/Player/Player.png");
	sprite.setTexture(texture);
	sprite.setPosition(400, 100);
	followPlayer.setCenter(400, 300);
	followPlayer.setSize(800, 600);
	followPlayer.setViewport(sf::FloatRect(0, 0, 1, 1));
	miniMapView.setCenter(3600, 2700);
	miniMapView.setSize(100, 50);
	miniMapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
	miniMapView.zoom(16);
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

sf::Vector2f Player::ScreenRap(sf::Vector2f pos, sf::Vector2f &w) {
	if (pos.x < 0 - (spritePosOffSet * 2))
		pos.x = w.x;
	else if (pos.x > w.x)
		pos.x = 1 - (spritePosOffSet * 2);
	if (pos.y < 0 - (spritePosOffSet * 2))
		pos.y = w.y;
	else if (pos.y > w.y + 1)
		pos.y = 1 - (spritePosOffSet * 2);
	return pos;
}

void Player::Update(sf::Vector2f &w) {
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
	followPlayer.setCenter(sprite.getPosition());
	miniMapView.setCenter(sprite.getPosition());
	sprite.setPosition(ScreenRap(sprite.getPosition(), w));
}

void Player::SpeedUp() {
    speed <= 3.8f ? speed += .2f : speed = 4.0f;
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

sf::FloatRect Player::GetBounds() {
	return sprite.getLocalBounds();
}

sf::View Player::getView() {
	return followPlayer;
}

sf::View Player::getMiniMapView() {
	return miniMapView;
}

void Player::Draw(sf::RenderWindow &w) {
	w.draw(sprite);
}