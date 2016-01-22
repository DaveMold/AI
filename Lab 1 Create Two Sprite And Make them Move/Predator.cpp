#include "stdafx.h"
#include "Predator.h"


Predator::Predator()
{
    texture.loadFromFile("Resorces/Img/Predator/Predator.png");
    sprite.setTexture(texture);
    acceleration = new Pvector(0, 0);
    velocity = new Pvector(rand() % 3 - 2, rand() % 3 - 2); // Allows for range of -2 -> 2
}

Predator::Predator(float x, float y, Factory* fac) : Predator()
{
    owner = fac;
    location = new Pvector(x, y);//x, y);
}


Predator::~Predator()
{
}

void Predator::Update()
{
    //To make the slow down not as abrupt
    acceleration->mulScalar(.3);
    // Update velocity
    velocity->addVector(*acceleration);
    // Limit speed
    velocity->limit(speed);
    location->addVector(*velocity);
    // Reset accelertion to 0 each cycle
    acceleration->mulScalar(0);
    float angle = std::atan2(velocity->y, velocity->x) * (180 / PI);
    sprite.setRotation(angle);
}

void Predator::Draw(sf::RenderWindow &w, sf::Vector2f &wb)
{
    borders();
    sprite.setPosition(sf::Vector2f(location->x, location->y));
    w.draw(sprite);
}

void Predator::borders()
{
    if (location->x < 0) location->x = MAP_WIDTH;
    else if (location->x > MAP_WIDTH) location->x = 0;
    if (location->y < 0) location->y = MAP_HEIGHT;
    else if (location->y > MAP_HEIGHT) location->y = 0;
}

void Predator::CalculateAlignment(std::vector<Predator*> preds)
{
    int size = preds.size();
    for (int i = 0; i < size; i++)
    {
        if (preds[i] != this)
        {
            if (this->location->distance(*(preds[i]->location)) < flockingDistance)
            {
                alignment.x += preds[i]->getVelocity()->x;
                alignment.y += preds[i]->getVelocity()->y;
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

void Predator::CalculateCohesion(std::vector<Predator*> preds)
{
    int size = preds.size();
    for (int i = 0; i < size; i++)
    {
        if (preds[i] != this)
        {
            if (this->location->distance(*(preds[i]->location)) < flockingDistance)
            {
                cohesion.x += preds[i]->getLocation()->x;
                cohesion.y += preds[i]->getLocation()->y;
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

void Predator::CalculateSeperation(std::vector<Predator*> preds)
{
    int size = preds.size();
    for (int i = 0; i < size; i++)
    {
        if (preds[i] != this)
        {
            if (this->location->distance(*(preds[i]->location)) < flockingDistance)
            {
                seperation.x += preds[i]->getLocation()->x - location->x;
                seperation.y += preds[i]->getLocation()->y - location->y;
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

Pvector Predator::Seek(Pvector playerLocation)
{
    auto temp = playerLocation;
    temp.subScalar(30);
    Pvector desired = temp - *location;
    // desired.subVector(playerLocation);  // A vector pointing from the location to the target
    // Normalize desired and scale to maximum speed
    desired.normalize();
    desired.mulScalar(speed);
    // Steering = Desired minus Velocity
    *acceleration = desired - *velocity;
    acceleration->limit(maxSteeringForce);  // Limit to maximum steering force
    return *acceleration;
}

sf::Vector2f Predator::GetPos()
{
    return sprite.getPosition();
}

sf::FloatRect Predator::GetBounds()
{
    return sprite.getGlobalBounds();
}