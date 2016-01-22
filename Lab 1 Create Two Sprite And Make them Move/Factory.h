#ifndef FACTORY_H
#define FACTORY_H

#include "stdafx.h"

class EnemyManager;

class Factory
{

public:
    Factory(EnemyManager* eMan);//!< constructor

    void Update(Pvector* target);//!< scales the acceleration and applies it and the veloicty to the location of the Factory. creates a projectile to and seeks it to the player when the player is in range. only two projectiles at a time though. erases them when the collide with the player.
	//! Three Laws that boids follow  
	void CalculateAlignment(std::vector<Factory*> facs);
    void CalculateCohesion(std::vector<Factory*> facs);
    void CalculateSeperation(std::vector<Factory*> facs);
    void NormalizeVelocity();//!< normalizes the velocity.
    Pvector Avoid(Pvector playerLocation); //!< uses the reverse of the seek to stay away from the player.
    void applyForce(Pvector force);//!< applies the force to the acceleration.
    void borders();//!< screen rap for the large area.
	bool CollisionProjectilePlayer(Player* p);//!< checks the distance between the plyer and projectile if it is less than the distance between there centres when touching.
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

    sf::Clock creationTimer;
    const float CreationTime = 5;

	//Seeking Projectiles
	std::vector<Projectile*> projectiles;
};

#endif // !FACTORY_H