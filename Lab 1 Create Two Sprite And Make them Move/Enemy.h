#ifndef ENEMY_H
#define ENEMY_H


class Enemy {

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
	Enemy(float x, float y);
	void Move(sf::Vector2f target);
	sf::Vector2f ScreenRap(sf::Vector2f pos, sf::RenderWindow &w);
	void Update(sf::RenderWindow &w, sf::Vector2f target);
	void SetPos(sf::Vector2f pos);
	void SpeedUp();
	void SlowDown();
	void Draw(sf::RenderWindow &w);


	void applyForce(Pvector force);
	// Three Laws that boids follow
	Pvector Separation(vector<Enemy*> enemies);
	Pvector Alignment(vector<Enemy*> enemies);
	Pvector Cohesion(vector<Enemy*> enemies);
	//Functions involving SFML and visualisation linking
	Pvector seek(Pvector v);
	void run(vector <Enemy*> v);
	void update();
	void flock(vector <Enemy*> v);
	void borders();
	float angle(Pvector v);
	void swarm(vector <Enemy*> v);
	void swarmToPoint(vector <Enemy*> v, Pvector pos);
};
#endif