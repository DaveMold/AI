#ifndef _ENMEYMANAGER_H
#define _ENMEYMANAGER_H

//includes
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "Enemy.h"

using namespace std;

class EnemyManager {
private:

public:
	vector<Enemy*> enemies;
	EnemyManager();
	~EnemyManager();
	
};
#endif