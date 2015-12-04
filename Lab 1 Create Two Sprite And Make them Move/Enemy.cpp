#include "Enemy.h"

Enemy::Enemy() {
	slow_before_player = true;
	if (slow_before_player == true)
		texture.loadFromFile("../../Resorces/Img/BlackHole1.png");
	else
		texture.loadFromFile("../../Resorces/Img/BlackHole2.png");
	sprite.setTexture(texture);
	sprite.setPosition(rand() % 750 + 1, rand() % 550 + 1);
	direction = sf::Vector2f(0.03, 0);

}

void Enemy::Move(sf::Vector2f target) {
	sf::Vector2f temp = sprite.getPosition();

	/*//slope calulations
	//slope pos to target
	float slope_target = (target.y - temp.y) / (target.x - temp.x);
	//slope pos to direction
	float slope_direction = (direction.y - temp.y) / (direction.x - temp.x);

	if (slope_target < slope_direction)
		rotation -= 0.001;
	else if (slope_target > slope_direction)
		rotation += 0.001;*/
	//test for slope calulated turning

	direction = target - temp;
	//normailize direction
	float lenght = sqrt(pow(target.x - temp.x, 2) + pow(target.y - temp.y, 2));
	direction /= lenght;

	//if enemy show slow before hitting into player
	if (slow_before_player == true) {
		if (lenght <= radius_slow_approach && speed >= 0)
			speed -= decelerate;
		else if (lenght <= radius_slow_approach && speed <= 0)
			speed = 0;
		else if (speed <= max_speed)
			speed += decelerate;
	}

	temp += (direction * speed);
	SetPos(temp);
}

sf::Vector2f Enemy::ScreenRap(sf::Vector2f pos, sf::RenderWindow &w) {
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

void Enemy::Update(sf::RenderWindow &w, sf::Vector2f target) {
	//Key input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		if (slow_before_player == true)
			slow_before_player = false;
		else
			slow_before_player = true;
	}
	if (slow_before_player == true){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
			radius_slow_approach++;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
			radius_slow_approach--;
	}
	Move(target);
	sprite.setPosition(ScreenRap(sprite.getPosition(), w));
}

void Enemy::SpeedUp() {
	speed += 0.0001;
}

void Enemy::SlowDown() {
	speed -= 0.0001;
}

void Enemy::SetPos(sf::Vector2f pos) {
	sprite.setPosition(pos);
}

void Enemy::Draw(sf::RenderWindow &w) {
	w.draw(sprite);
}