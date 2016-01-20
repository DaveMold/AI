#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H


using namespace std;

class EnemyManager {
private:

    vector<Swarmer*> enemies;
    vector<Factory *> factories;

public:
	
	EnemyManager();
	~EnemyManager();
	void Draw(sf::RenderWindow &w);
	int getSize();
	Swarmer getEnemy(int i);
	void addEnemy(Swarmer* b);
    void addFactory(Factory* fac);
	void flocking();

	void swarming(Pvector mousepos);
    void UpdateFactories();
};
#endif