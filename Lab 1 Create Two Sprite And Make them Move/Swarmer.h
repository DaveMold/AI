#ifndef ENEMY_H
#define ENEMY_H


class Swarmer {

	//vairbles
	Pvector* location;//!< used to 
	Pvector*  velocity;// = 0.03;
	Pvector* acceleration;// = 0.01;
	float maxSpeed = 0.03;
	float maxForce;

	bool slow_before_player;
	float rotation = 0.2;//Radiants
	float speed = 5.0f;
	float max_speed = 5.0f;
	float decelerate = 0.1f;
	float radius_slow_approach = 5;
	float spritePosOffSet = 16;//sprite size / 2; sprite size == 32
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Sprite sprite;

public:
	Swarmer(float x, float y);//!< constructor
	void Move(sf::Vector2f target);//!< moves to the target and slows and comes to a stop before colliding.
	void SetPos(sf::Vector2f pos);//!< sets the pos of the sprite.
	void SpeedUp();//!< increases the speed.
	void SlowDown();//!<  decreases the speed of the object.
	void Draw(sf::RenderWindow &w, sf::Vector2f &wb);//!<  Draws the Swarmer.
	sf::Vector2f GetPos();//!< gets the posision of the object for collsiion checks in other classes.
	sf::FloatRect GetBounds();//!<  gets the size of the object for collision checks in other classes.


	void applyForce(Pvector force);//!<  adds a force to the acceleration.
	//! Three Laws that boids follow
	Pvector Separation(std::vector<Swarmer*> enemies);
	Pvector Alignment(std::vector<Swarmer*> enemies);
	Pvector Cohesion(std::vector<Swarmer*> enemies);
	Pvector seek(Pvector v);//!< not used.
	void run(std::vector <Swarmer*> v);//!< calls flocking followed by the update and borders check.
	void update();//!< scales the acceleration and applies it and the veloicty to the location of the swarmer.
	void flock(std::vector <Swarmer*> v);//!< flocks the Swarmer to a point with a groupe that is sent to the method.
	void borders();//!< screen rap for the large area.
	float angle(Pvector v);
	void swarm(std::vector <Swarmer*> v);//!< swarms the swarmer to a point with a groupe provided.
	void swarmToPoint(std::vector <Swarmer*> v, Pvector pos); //!< swarms the swarmer to a point with a groupe provided.
};
#endif