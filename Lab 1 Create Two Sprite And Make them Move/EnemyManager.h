#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H

//includes
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Enemy.h"
#include "Pvector.h"

using namespace std;

class EnemyManager {
private:

public:
	vector<Enemy*> enemies;
	EnemyManager();
	~EnemyManager();
	int getSize();
	Enemy getEnemy(int i);
	void addEnemy(Enemy b);
	void flocking();
	void swarming(Pvector mousepos);
};
#endif