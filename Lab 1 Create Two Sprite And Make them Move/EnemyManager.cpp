#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager() : swarmingRange(100), swarmAI(FLOCKING)
{

}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Draw(sf::RenderWindow &w, sf::Vector2f &wb)
{
    int size = enemies.size();
    for (int i = 0; i < size; i++)
    {
        enemies[i]->Draw(w, wb);
    }
    size = factories.size();
    for (int i = 0; i < size; i++)
    {
        factories[i]->Draw(w, wb);
    }
    size = preds.size();
    for (int i = 0; i < size; i++)
    {
        preds[i]->Draw(w, wb);
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

void EnemyManager::swarmECollision()
{
    int size = enemies.size();
    for (int i = 0; i < size; i++)
    {
        if (ProjectileManager::instance()->Collision(enemies[i]))
        {
            enemies.erase(std::remove(enemies.begin(),enemies.end(),enemies[i]),enemies.end());
            size--;
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

void EnemyManager::UpdateFactories(Pvector playerVelo)
{
    int size = factories.size();
    for (int i = 0; i < size; i++)
    {
        factories[i]->CalculateAlignment(factories);
        factories[i]->CalculateCohesion(factories);
        factories[i]->CalculateSeperation(factories);

        auto force = new Pvector(factories[i]->getAlignment().x * .7f + factories[i]->getCohesion().x * .6f + factories[i]->getSeperation().x * .75f,
            factories[i]->getAlignment().y * .7f + factories[i]->getCohesion().y * .6f + factories[i]->getSeperation().y * .75f);

        factories[i]->applyForce(*force);
        factories[i]->Avoid(playerVelo);
        factories[i]->Update();
    }

    /*for (int i = 0; i < factories.size(); i++)
    {
        factories[i]->Update();
    }*/
}

void EnemyManager::addFactory(Factory* fac)
{
    factories.push_back(fac);
}

void EnemyManager::swarmEAI(Pvector target)
{
    sf::Vector2f ePos;
    for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
    {
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
            for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
            {
                (*itr)->swarmToPoint(enemies, target);
            }
            break;
        case FLOCKING:
            for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
            {
                (*itr)->flock(enemies);
            }
            break;
        default:
            std::cout << "default EM::swarmAI" << std::endl;
            break;
    }
}

void EnemyManager::addPredator(float x, float y)
{
    preds.push_back(new Predator(x, y));
}

void EnemyManager::UpdatePredators(Pvector playerPos)
{
    int size = preds.size();
    for (int i = 0; i < size; i++)
    {
        preds[i]->CalculateAlignment(preds);
        preds[i]->CalculateCohesion(preds);
        preds[i]->CalculateSeperation(preds);

        auto force = new Pvector(preds[i]->getAlignment().x * .7f + preds[i]->getCohesion().x * .6f + preds[i]->getSeperation().x * .75f,
            preds[i]->getAlignment().y * .7f + preds[i]->getCohesion().y * .6f + preds[i]->getSeperation().y * .75f);

        preds[i]->Seek(playerPos);

        preds[i]->Update();
        
    }
}