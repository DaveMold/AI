#include "stdafx.h"
#include "ProjectileManager.h"

ProjectileManager* ProjectileManager::mInstance = nullptr;
ProjectileManager::ProjectileManager() {

}

ProjectileManager* ProjectileManager::instance() {
	if (mInstance == nullptr)
	{
		mInstance = new ProjectileManager();
	}

	return mInstance;
}


ProjectileManager::~ProjectileManager() {

}

void ProjectileManager::Update(sf::RenderWindow &w) {
	bool removed = true;
	std::vector<Projectile*>::iterator removeItr;
	for (auto itr = projectiles.begin(); itr != projectiles.end(); itr++) {
		(*itr)->Update();
		if ((*itr)->ScreenBounds(w))
		{
			removed = false;
			removeItr = itr;
		}
	}
	if (removed == false)
	{
		removed = true;
		projectiles.erase(removeItr);
	}

}

void ProjectileManager::Draw(sf::RenderWindow &w) {
	for (auto itr = projectiles.begin(); itr != projectiles.end(); itr++) {
		(*itr)->Draw(w);
	}
}

void ProjectileManager::AddProjectile(sf::Vector2f dir, sf::Vector2f pos) {
	projectiles.push_back(new Projectile(dir, pos));
}

bool ProjectileManager::Collision(Swarmer* e) {
	sf::Vector2f pPos, ePos;
	sf::FloatRect pBounds, eBounds;
	ePos = e->GetPos();
	eBounds = e->GetBounds();
	for (auto itr = projectiles.begin(); itr != projectiles.end(); itr++) {
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