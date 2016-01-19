#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H


using namespace std;

class EnemyManager {
private:

    vector<Enemy*> enemies;
    vector<Factory *> factories;

public:
	
	EnemyManager();
	~EnemyManager();
	void Draw(sf::RenderWindow &w);
	int getSize();
	Enemy getEnemy(int i);
	void addEnemy(Enemy* b);
    void addFactory(Factory* fac);
	void flocking();

	void swarming(Pvector mousepos);
};
#endif