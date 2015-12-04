#include "EnemyManager.h"

EnemyManager::EnemyManager() {

}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Draw(sf::RenderWindow &w) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Draw(w);
	}
}

int EnemyManager::getSize()
{
	return enemies.size();
}

Enemy EnemyManager::getEnemy(int i)
{
	return *enemies[i];
}

void EnemyManager::addEnemy(Enemy* b)
{
	enemies.push_back(b);
}

void EnemyManager::flocking()
{
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->run(enemies);
	}
}

void EnemyManager::swarming(Pvector mousepos)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		/*if (enemies[i]predator)
			enemies[i].swarm(flock);
		else*/
			enemies[i]->swarmToPoint(enemies, mousepos);
	}
}