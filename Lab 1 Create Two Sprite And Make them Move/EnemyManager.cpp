#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager() : swarmingRange(100), swarmAI(FLOCKING) {

}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Draw(sf::RenderWindow &w, sf::Vector2f &wb) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Draw(w,wb);
	}
    for (int i = 0; i < factories.size(); i++)
    {
        factories[i]->Draw(w,wb);
    }
}

int EnemyManager::getSize()
{
	return enemies.size();
}

Swarmer EnemyManager::getEnemy(int i)
{
	return *enemies[i];
}

void EnemyManager::addEnemy(Swarmer* b)
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

void EnemyManager::swarmECollision() {
	for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
		if (ProjectileManager::instance()->Collision(*itr))
		{
			enemies.erase(itr);
			break;
		}
	}
}

void EnemyManager::swarming(Pvector mousepos)
{
	for (int i = 0; i < enemies.size(); i++)
	{
			enemies[i]->swarmToPoint(enemies, mousepos);
	}
}

void EnemyManager::UpdateFactories()
{
    for (int i = 0; i < factories.size(); i++)
    {
        factories[i]->Update();
    }
}

void EnemyManager::addFactory(Factory* fac)
{
    factories.push_back(fac);
}

void EnemyManager::swarmEAI(Pvector target) {
	sf::Vector2f ePos;
	for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
		ePos = (*itr)->GetPos();
		//callculate distance between two points
		float dis = sqrt(pow(ePos.x - target.x, 2.0f) + pow(ePos.y - target.y, 2.0f));
		if (dis < swarmingRange)
			swarmAI = SWARM;
		else
			swarmAI = FLOCKING;
	}

	switch (swarmAI)
	{
	case SWARM:
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
			(*itr)->swarmToPoint(enemies, target);
		}
		break;
	case FLOCKING:
		for (auto itr = enemies.begin(); itr != enemies.end(); itr++) {
			(*itr)->flock(enemies);
		}
		break;
	default:
		std::cout << "default EM::swarmAI" << std::endl;
		break;
	}
}