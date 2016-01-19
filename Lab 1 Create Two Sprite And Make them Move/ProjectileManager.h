#ifndef _PROJECTILEMANAGER_H
#define _PROJECTILEMANAGER_H

//includes
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Projectile.h"

using namespace std;

class ProjectileManager {
private:
	std::vector<Projectile*> projectiles;
	static ProjectileManager* mInstance;
public:
	static ProjectileManager* instance();
	ProjectileManager();
	~ProjectileManager();
	void Update(sf::RenderWindow &w);
	void Draw(sf::RenderWindow &w);
	void AddProjectile(sf::Vector2f dir, sf::Vector2f pos);
};
#endif