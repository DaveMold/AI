#include "stdafx.h"
#include "Factory.h"



Factory::Factory(EnemyManager* eMan)
{
    eManager = eMan;
    texture.loadFromFile("Resorces/Img/Factory.png");
    sprite.setTexture(texture);
    acceleration = new Pvector(0, 0);
    velocity = new Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
    location = new Pvector(rand() % 6000 + 1, rand() % 5000 + 1);//x, y);
    creationTimer.restart();
	range = 300;
	projectiles.reserve(2);
}

void Factory::Update(Pvector* target)
{

	if (sqrt(pow(target->x - sprite.getPosition().x, 2.0f) + pow(target->y - sprite.getPosition().y, 2.0f)) < range && projectiles.size() < 3)
	{
		projectiles.push_back(new Projectile(sf::Vector2f(target->x, target->y), sprite.getPosition()));
	}

	for (auto itr = projectiles.begin(); itr != projectiles.end(); itr++)
	{
		if ((*itr)->UpdateSeeking(*target))
		{
			projectiles.erase(itr);
			break;
		}
	}

    //To make the slow down not as abrupt
    acceleration->mulScalar(.4);
    // Update velocity
    velocity->addVector(*acceleration);
    // Limit speed
    velocity->limit(speed);
    location->addVector(*velocity);
    // Reset accelertion to 0 each cycle
    acceleration->mulScalar(0);

    if (creationTimer.getElapsedTime().asSeconds() > CreationTime)
    {
        eManager->addPredator(location->x, location->y);
        creationTimer.restart();
    }
}

void Factory::Draw(sf::RenderWindow &w, sf::Vector2f &wb)
{
    borders();
    sprite.setPosition(sf::Vector2f(location->x, location->y));
    w.draw(sprite);
	for (auto itr = projectiles.begin(); itr != projectiles.end(); itr++)
	{
		(*itr)->Draw(w);
	}
}

Factory::~Factory()
{
}

void Factory::CalculateAlignment(std::vector<Factory*> facs)
{
    int size = facs.size();
    for (int i = 0; i < size; i++)
    {
        if (facs[i] != this)
        {
            if (this->location->distance(*(facs[i]->location)) < flockingDistance)
            {
                alignment.x += facs[i]->getVelocity()->x;
                alignment.y += facs[i]->getVelocity()->y;
                neighborCount++;
            }
        }
    }
    if (neighborCount == 0)
    {
        alignment = Pvector(0, 0);
    }
    else
    {
        alignment.x /= neighborCount;
        alignment.y /= neighborCount;

        alignment.normalize();
        neighborCount = 0;
    }
}

void Factory::CalculateCohesion(std::vector<Factory*> facs)
{
    int size = facs.size();
    for (int i = 0; i < size; i++)
    {
        if (facs[i] != this)
        {
            if (this->location->distance(*(facs[i]->location)) < flockingDistance)
            {
                cohesion.x += facs[i]->getLocation()->x;
                cohesion.y += facs[i]->getLocation()->y;
                neighborCount++;
            }
        }
    }
    if (neighborCount == 0)
    {
        cohesion = Pvector(0, 0);
    }
    else
    {
        cohesion.x /= neighborCount;
        cohesion.y /= neighborCount;
        cohesion = Pvector(cohesion.x - location->x, cohesion.y - location->y);
        cohesion.normalize();
        neighborCount = 0;
    }
}

void Factory::CalculateSeperation(std::vector<Factory*> facs)
{
    int size = facs.size();
    for (int i = 0; i < size; i++)
    {
        if (facs[i] != this)
        {
            if (this->location->distance(*(facs[i]->location)) < flockingDistance)
            {
                seperation.x += facs[i]->getLocation()->x - location->x;
                seperation.y += facs[i]->getLocation()->y - location->y;
                neighborCount++;
            }
        }
    }
    if (neighborCount == 0)
    {
        seperation = Pvector(0, 0);
    }
    else
    {
        seperation.x /= neighborCount;
        seperation.y /= neighborCount;
        seperation.x *= -1;
        seperation.y *= -1;
        seperation.normalize();
        neighborCount = 0;
    }
}

///Make velocity magnitude == 1 then
///multiply by factory::Speed to
///set correct velocity
void Factory::NormalizeVelocity()
{
    velocity->normalize();
    velocity->x *= speed;
    velocity->y *= speed;
}

Pvector Factory::Avoid(Pvector playerLocation)
{
    if (location->distance(playerLocation) < 200)
    {
        Pvector desired = *location - playerLocation;
       // desired.subVector(playerLocation);  // A vector pointing from the location to the target
                               // Normalize desired and scale to maximum speed
        desired.normalize();
        desired.mulScalar(speed);
        // Steering = Desired minus Velocity
        *acceleration = desired - *velocity;
        acceleration->limit(maxSteeringForce);  // Limit to maximum steering force
        return *acceleration;
    }
}

void Factory::applyForce(Pvector force)
{
    acceleration->addVector(force);
}
//
//void Factory::borders()
//{
//    if (location->x < 0) location->x += w_width;
//    if (location->y < 0) location->y += w_height;
//    if (location->x > 1000) location->x -= w_width;
//    if (location->y > 1000) location->y -= w_height;
//}

void Factory::borders()
{
    if (location->x < 0) location->x = MAP_WIDTH;
    else if (location->x > MAP_WIDTH) location->x = 0;
    if (location->y < 0) location->y = MAP_HEIGHT;
    else if (location->y > MAP_HEIGHT) location->y = 0;
}

sf::Vector2f Factory::GetPos()
{
    return sprite.getPosition();
}

sf::FloatRect Factory::GetBounds()
{
    return sprite.getGlobalBounds();
}

bool Factory::CollisionProjectilePlayer(Player* p)
{
	sf::Vector2f pPos, ePos;
	sf::FloatRect pBounds, eBounds;
	ePos = p->GetPos();
	eBounds = p->GetBounds();
	for (auto itr = projectiles.begin(); itr != projectiles.end(); itr++)
	{
		pPos = (*itr)->GetPos();
		pBounds = (*itr)->GetBounds();
		//callculate distance between two points
		float dis = sqrt(pow(ePos.x - pPos.x, 2.0f) + pow(ePos.y - pPos.y, 2.0f));
		if ((eBounds.width / 2.0f) + (pBounds.width / 2.0f) > dis)
		{
			projectiles.erase(itr);
			return true;
		}
	}
	return false;
}