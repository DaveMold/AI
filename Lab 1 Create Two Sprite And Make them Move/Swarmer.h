#ifndef ENEMY_H
#define ENEMY_H


class Swarmer {

	//vairbles
	Pvector* location;
	Pvector*  velocity;// = 0.03;
	Pvector* acceleration;// = 0.01;
	float maxSpeed = 0.03;
	float maxForce;

	bool slow_before_player;
	float rotation = 0.2;//Radiants
	float speed = 3.0f;
	float max_speed = 3.0f;
	float decelerate = 0.1f;
	float radius_slow_approach = 5;
	float spritePosOffSet = 16;//sprite size / 2; sprite size == 32
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Sprite sprite;

public:
	Swarmer(float x, float y);
	void Move(sf::Vector2f target);
	void SetPos(sf::Vector2f pos);
	void SpeedUp();
	void SlowDown();
	void Draw(sf::RenderWindow &w, sf::Vector2f &wb);
	sf::Vector2f GetPos();
	sf::FloatRect GetBounds();


	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(vector<Swarmer*> enemies);
	Pvector Alignment(vector<Swarmer*> enemies);
	Pvector Cohesion(vector<Swarmer*> enemies);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	void run(vector <Swarmer*> v);
	void update();
	void flock(vector <Swarmer*> v);
	void borders();
	float angle(Pvector v);
	void swarm(vector <Swarmer*> v);
	void swarmToPoint(vector <Swarmer*> v, Pvector pos);
};
#endif