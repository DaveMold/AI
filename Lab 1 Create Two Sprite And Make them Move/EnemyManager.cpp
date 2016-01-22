#include "stdafx.h"
#include "EnemyManager.h"

EnemyManager::EnemyManager() : swarmingRange(200), swarmAI(FLOCKING)
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

void EnemyManager::CheckCollisions()
{
    int size = enemies.size();
    for (int i = 0; i < size; i++)
    {
        if (ProjectileManager::instance()->CollisionSwarm(enemies[i]))
        {
            enemies.erase(std::remove(enemies.begin(), enemies.end(), enemies[i]), enemies.end());
            size--;
        }
    }
    size = factories.size();
    for (int i = 0; i < size; i++)
    {
        if (ProjectileManager::instance()->CollisionFac(factories[i]))
        {
            factories[i]->DealDamage();
            if (factories[i]->getHealth() <= 0)
            {
                factories.erase(std::remove(factories.begin(), factories.end(), factories[i]), factories.end());
                size--;
            }
        }
    }
    size = preds.size();
    for (int i = 0; i < size; i++)
    {
        if (ProjectileManager::instance()->CollisionPred(preds[i]))
        {
            preds[i]->getOwner()->removePred();
            preds.erase(std::remove(preds.begin(), preds.end(), preds[i]), preds.end());
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

void EnemyManager::UpdateFactories(Player* p)
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
        factories[i]->Avoid(p->GetPos());
        factories[i]->Update(new Pvector(p->GetPos().x, p->GetPos().y));
        factories[i]->CollisionProjectilePlayer(p);
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
        if (dis <= swarmingRange)
            (*itr)->swarmToPoint(enemies, target);
        else
            (*itr)->run(enemies);
    }

    /* switch (swarmAI)
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
     }*/
}

void EnemyManager::addPredator(float x, float y, Factory* owner)
{
    preds.push_back(new Predator(x, y, owner));
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

bool EnemyManager::CollisionSwarm(Player* e)
{
    sf::Vector2f pPos, ePos;
    sf::FloatRect pBounds, eBounds;
    ePos = e->GetPos();
    eBounds = e->GetBounds();
    for (auto itr = enemies.begin(); itr != enemies.end(); itr++)
    {
        pPos = (*itr)->GetPos();
        pBounds = (*itr)->GetBounds();
        //callculate distance between two points
        float dis = sqrt(pow(ePos.x - pPos.x, 2.0f) + pow(ePos.y - pPos.y, 2.0f));
        if ((eBounds.width / 2.0f) + (pBounds.width / 2.0f) > dis)
        {
            enemies.erase(itr);
            e->TakeDamage();
            return true;
        }
    }
    return false;
}

bool EnemyManager::CollisionPred(Player* e)
{
    sf::Vector2f pPos, ePos;
    sf::FloatRect pBounds, eBounds;
    ePos = e->GetPos();
    eBounds = e->GetBounds();
    for (auto itr = preds.begin(); itr != preds.end(); itr++)
    {
        pPos = (*itr)->GetPos();
        pBounds = (*itr)->GetBounds();
        //callculate distance between two points
        float dis = sqrt(pow(ePos.x - pPos.x, 2.0f) + pow(ePos.y - pPos.y, 2.0f));
        if ((eBounds.width / 2.0f) + (pBounds.width / 2.0f) > dis)
        {
            preds.erase(itr);
            e->TakeDamage();
            return true;
        }
    }
    return false;
}