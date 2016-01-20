#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager() {

}

EnemyManager::~EnemyManager() {

}

void EnemyManager::Draw(sf::RenderWindow &w) {
	for (int i = 0; i < enemies.size(); i++) {
		enemies[i]->Draw(w);
	}
    for (int i = 0; i < factories.size(); i++)
    {
        factories[i]->Draw(w);
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