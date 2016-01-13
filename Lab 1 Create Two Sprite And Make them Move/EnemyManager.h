#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H


using namespace std;

class EnemyManager {
private:

public:
	vector<Enemy*> enemies;
	EnemyManager();
	~EnemyManager();
	void Draw(sf::RenderWindow &w);
	int getSize();
	Enemy getEnemy(int i);
	void addEnemy(Enemy* b);
	void flocking();

	void swarming(Pvector mousepos);
};
#endif