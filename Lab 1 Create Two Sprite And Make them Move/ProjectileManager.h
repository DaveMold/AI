#ifndef _PROJECTILEMANAGER_H
#define _PROJECTILEMANAGER_H

//includes
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Projectile.h"


class ProjectileManager {
private:
	std::vector<Projectile*> projectiles;//!< used to store the porjectiles.
	static ProjectileManager* mInstance;//!< used to access the ProjectileManager from anywhere in the code.
public:
	static ProjectileManager* instance();
	ProjectileManager();//!< constructor.
	~ProjectileManager();//!< deconstructor.
	void Update(sf::RenderWindow &w);//!< will update all the projectiles. If the projectiles Update reutnrs true, it is killed.
	void Draw(sf::RenderWindow &w);//!< draws all the projectiles
	void AddProjectile(sf::Vector2f dir, sf::Vector2f pos); //!< adds a projectile to the list with a start location and direction to fire at.


	bool CollisionSwarm(Swarmer* e);//!< collision detection for the swarmer. if the swarmer is nearer to the projectile than the distance between their centres then there is a collision and both should be killed.
    bool CollisionFac(Factory* e);//!< collision detection for the Factory. if the Factory is nearer to the projectile than the distance between their centres then there is a collision and both should be killed.
    bool CollisionPred(Predator* e);//!< collision detection for the Predator. if the Predator is nearer to the projectile than the distance between their centres then there is a collision and both should be killed.
};
#endif