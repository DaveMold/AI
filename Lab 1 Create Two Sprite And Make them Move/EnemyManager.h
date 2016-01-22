#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H


using namespace std;

class EnemyManager {
private:

    vector<Swarmer*> enemies;
    vector<Factory *> factories;
    vector<Predator*> preds;
	int swarmingRange; //!<when the swarming enemies are with in this range they will stop flocking to swarm on the player.
	enum swarmAIType { SWARM, FLOCKING };
	swarmAIType swarmAI;


public:
	
	EnemyManager();//!< constructor
	~EnemyManager();
	void Draw(sf::RenderWindow &w, sf::Vector2f &wb);//!<  Draws the enemies.
	int getSize();
	Swarmer getEnemy(int i);
	void addEnemy(Swarmer* b);//!< adds a passed enemy to a list.
    void addFactory(Factory* fac); //!< adds the factory to a list.
	void flocking(); //!< applies flocking to the enemies.
	void CheckCollisions();
	void swarming(Pvector mousepos);
    void UpdateFactories(Player* p);
	void swarmEAI(Pvector target);
    void addPredator(float x, float y); //!<  create a predidtor.
    void UpdatePredators(Pvector playerPos); //!<  updates preditors
};
#endif