//includes
#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(float x, float y) {
	slow_before_player = true;
	acceleration = new Pvector(0, 0);
	velocity = new Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
	location = new Pvector(x, y);
	maxSpeed = 0.5f;
	maxForce = 0.5f;

	slow_before_player = true;
	if (slow_before_player == true)
		texture.loadFromFile("Resorces/Img/BlackHole1.png");
	else
		texture.loadFromFile("Resorces/Img/BlackHole2.png");
	sprite.setTexture(texture);
	/*sprite.setPosition(rand() % 750 + 1, rand() % 550 + 1);
	direction = sf::Vector2f(0.03, 0);*/
	sprite.setPosition(rand() % 750 + 1, rand() % 550 + 1);
	direction = sf::Vector2f(1, 0);

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
	sprite.setPosition(ScreenRap(sf::Vector2f(location->x,location->y),w));
	w.draw(sprite);
}


sf::VideoMode desktopTemp = sf::VideoMode::getDesktopMode();
const int window_height = desktopTemp.height;
const int window_width = desktopTemp.width;

#define w_height window_height
#define w_width window_width
#define PI 3.141592635

using namespace std;


void Enemy::applyForce(Pvector force)
{
	acceleration->addVector(force);
}

Pvector Enemy::Separation(vector<Enemy*> enemies)
{
	// If the enemy we're looking at is a predator, do not run the separation
	// algorithm

	// Distance of field of vision for separation between Enemies
	float desiredseparation = 20;

	Pvector steer(0, 0);
	int count = 0;
	// For every Enemy in the system, check if it's too close
	for (int i = 0; i < enemies.size(); i++)
	{
		// Calculate distance from current enemy to the enemy we're looking at
		float d = location->distance(*enemies[i]->location);
		// If this is a fellow enemy and it's too close, move away from it
		if ((d > 0) && (d < desiredseparation))
		{
			Pvector diff(0, 0);
			diff = diff.subTwoVector(*location, *enemies[i]->location);
			diff.normalize();
			diff.divScalar(d);      // Weight by distance
			steer.addVector(diff);
			count++;
		}
		//separate only slightly
		if ((d > 0) && (d < desiredseparation))
		{
			Pvector pred2pred(0, 0);
			pred2pred = pred2pred.subTwoVector(*location, *enemies[i]->location);
			pred2pred.normalize();
			pred2pred.divScalar(d);
			steer.addVector(pred2pred);
			count++;
		}
		
		/*// If current enemy is not a predator, but the enemy we're looking at is
		// a predator, then create a large separation Pvector
		else if ((d > 0) && (d < desiredseparation + 70) && enemies[i].predator == true)
		{
			Pvector pred(0, 0);
			pred = pred.subTwoVector(location, enemies[i]->location);
			pred.mulScalar(900);
			steer.addVector(pred);
			count++;
		}*/
	}
	// Adds average difference of location to acceleration
	if (count > 0)
		steer.divScalar((float)count);
	if (steer.magnitude() > 0)
	{
		// Steering = Desired - Velocity
		steer.normalize();
		steer.mulScalar(maxSpeed);
		steer.subVector(*velocity);
		steer.limit(maxForce);
	}
	return steer;
}

Pvector Enemy::Alignment(vector<Enemy*> enemies)
{
	// algorithm
	float neighbordist = 50;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		float d = location->distance(*enemies[i]->location);
		if ((d > 0) && (d < neighbordist)) // 0 < d < 50
		{
			sum.addVector(*enemies[i]->velocity);
			count++;
		}
	}
	// If there are enemies close enough for alignment...
	if (count > 0)
	{
		sum.divScalar((float)count);// Divide sum by the number of close boids (average of velocity)
		sum.normalize();	   		// Turn sum into a unit vector, and
		sum.mulScalar(maxSpeed);    // Multiply by maxSpeed
									// Steer = Desired - Velocity
		Pvector steer;
		steer = steer.subTwoVector(sum, *velocity); //sum = desired(average)  
		steer.limit(maxForce);
		return steer;
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

Pvector Enemy::Cohesion(vector<Enemy*> enemies)
{
	// algorithm
	float neighbordist = 50;

	Pvector sum(0, 0);
	int count = 0;
	for (int i = 0; i < enemies.size(); i++)
	{
		float d = location->distance(*enemies[i]->location);
		if ((d > 0) && (d < neighbordist))
		{
			sum.addVector(*enemies[i]->location);
			count++;
		}
	}
	if (count > 0)
	{
		sum.divScalar(count);
		return seek(sum);
	}
	else {
		Pvector temp(0, 0);
		return temp;
	}
}

Pvector Enemy::seek(Pvector v)
{
	Pvector desired;
	desired.subVector(v);  // A vector pointing from the location to the target
						   // Normalize desired and scale to maximum speed
	desired.normalize();
	desired.mulScalar(maxSpeed);
	// Steering = Desired minus Velocity
	acceleration->subTwoVector(desired, *velocity);
	acceleration->limit(maxForce);  // Limit to maximum steering force
	return *acceleration;
}

void Enemy::update()
{
	//To make the slow down not as abrupt
	acceleration->mulScalar(.4);
	// Update velocity
	velocity->addVector(*acceleration);
	// Limit speed
	velocity->limit(maxSpeed);
	location->addVector(*velocity);
	// Reset accelertion to 0 each cycle
	acceleration->mulScalar(0);
}

void Enemy::run(vector <Enemy*> v)
{
	flock(v);
	update();
	borders();
}

void Enemy::flock(vector<Enemy*> v)
{
	Pvector sep = Separation(v);
	Pvector ali = Alignment(v);
	Pvector coh = Cohesion(v);
	// Arbitrarily weight these forces
	sep.mulScalar(1.5);
	ali.mulScalar(1.0); // Might need to alter weights for different characteristics
	coh.mulScalar(1.0);
	// Add the force vectors to acceleration
	applyForce(sep);
	applyForce(ali);
	applyForce(coh);
}

void Enemy::borders()
{
	if (location->x < 0) location->x += w_width;
	if (location->y < 0) location->y += w_height;
	if (location->x > 1000) location->x -= w_width;
	if (location->y > 1000) location->y -= w_height;
}

float Enemy::angle(Pvector v)
{
	// From the definition of the dot product
	float angle = (float)(atan2(v.x, -v.y) * 180 / PI);
	return angle;
}

void Enemy::swarm(vector <Enemy*> v)
{
	/*		Lenard-Jones Potential function
	Vector R = me.position - you.position
	Real D = R.magnitude()
	Real U = -A / pow(D, N) + B / pow(D, M)
	R.normalise()
	force = force + R*U
	*/
	Pvector	R;
	float A = 100, B = 5000, N = 1, M = 2, U, D;
	Pvector sum(0, 0);
	for (int j = 0; j < v.size(); j++) {
		R = R.subTwoVector(*location, *v[j]->location);
		D = R.magnitude();
		if (D == 0)
			continue;
		U = (-A / pow(D, N)) + (B / pow(D, M));
		R.normalize();
		R.mulScalar(U);
		sum.addVector(R);
	}

	applyForce(sum);
	update();
	borders();
}

void Enemy::swarmToPoint(vector <Enemy*> v, Pvector pos)
{
	/*		Lenard-Jones Potential function
	Vector R = me.position - you.position
	Real D = R.magnitude()
	Real U = -A / pow(D, N) + B / pow(D, M)
	R.normalise()
	force = force + R*U
	*/
	Pvector	R;
	float A = 100, B = 5000, N = 1, M = 2, U, D;
	Pvector sum(0, 0);
	R = R.subTwoVector(*location, pos);
	D = R.magnitude();
	U = (-A / pow(D, N)) + (B / pow(D, M));
	R.normalize();
	R.mulScalar(U);
	sum.addVector(R);

	applyForce(sum);
	update();
	borders();
}