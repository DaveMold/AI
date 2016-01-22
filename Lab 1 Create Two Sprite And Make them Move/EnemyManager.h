#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H


using namespace std;

class EnemyManager {
private:

    vector<Swarmer*> enemies;
    vector<Factory *> factories;
    vector<Predator*> preds;
	int swarmingRange; //when the swarming enemies are with in this range they will stop flocking to swarm on the player.
	enum swarmAIType { SWARM, FLOCKING };
	swarmAIType swarmAI;


public:
	
	EnemyManager();
	~EnemyManager();
	void Draw(sf::RenderWindow &w, sf::Vector2f &wb);
	int getSize();
	Swarmer getEnemy(int i);
	void addEnemy(Swarmer* b);
    void addFactory(Factory* fac);
	void flocking();
	void CheckCollisions();
	void swarming(Pvector mousepos);
    void UpdateFactories(Player* p);
	void swarmEAI(Pvector target);
    void addPredator(float x, float y);
    void UpdatePredators(Pvector playerPos);
};
#endif