#ifndef FACTORY_H
#define FACTORY_H

#include "stdafx.h"

class EnemyManager;

class Factory
{

public:
    Factory(EnemyManager* eMan);

    void Update(Pvector* target);
    void CalculateAlignment(std::vector<Factory*> facs);
    void CalculateCohesion(std::vector<Factory*> facs);
    void CalculateSeperation(std::vector<Factory*> facs);
    void NormalizeVelocity();
    Pvector Avoid(Pvector playerLocation);
    void applyForce(Pvector force);
    void borders();
	bool CollisionProjectilePlayer(Player* p);
    sf::Vector2f GetPos();
    sf::FloatRect GetBounds();
    //void borders();
    void Draw(sf::RenderWindow & w, sf::Vector2f &wb);
    ~Factory();

    Pvector* getVelocity() { return velocity; }
    void setVelocity(Pvector velo) { *velocity = velo; }
    Pvector* getLocation() { return location; }
    void setLocation(Pvector loc) { *location = loc; }


    Pvector getAlignment() { return alignment; }
    Pvector getCohesion() { return cohesion; }
    Pvector getSeperation() { return seperation; }
    int getNumPredsOwned() { return numPredsOwned; }
    int getHealth() { return Health; }

    void DealDamage();
    void removePred();

private:
    EnemyManager* eManager;
    sf::Texture texture;
    sf::Vector2f direction;
    sf::Sprite sprite;
    float rotation = 0.2;//Radiants
    float speed = 1.5f;
    float maxSteeringForce = 1.0f;
	float range;

    float spritePosOffSet = 16;
    Pvector* location;
    Pvector*  velocity;// = 0.03;
    Pvector* acceleration;// = 0.01;

    Pvector alignment;
    Pvector cohesion;
    Pvector seperation;
    int flockingDistance = 300;
    int neighborCount;
    int Health = 4;
    int numPredsOwned = 0;
    int maxNumPreds = 2;
    sf::Clock creationTimer;
    const float CreationTime = 5;

	//Seeking Projectiles
	std::vector<Projectile*> projectiles;
};

#endif // !FACTORY_H