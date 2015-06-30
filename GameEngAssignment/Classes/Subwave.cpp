#include "Subwave.h"


CSubwave::CSubwave()
{
}
CSubwave::~CSubwave()
{
}

void CSubwave::init(float activateTime, int normal){
	this->activateTime = activateTime;
	this->normal = normal;
	this->active = false;
	this->spawnTimer = 0.0f;
}
CEnemy* CSubwave::update(float dt, cocos2d::Vec2 playerPosition){
	//If there is no more monster left to spawn, end 
	if (getTotalMonsters() <= 0)
		return NULL;

	spawnTimer += dt;

	if (spawnTimer >= 1.0f){
		//Spawn monster
		CEnemy* newEnemy = new CEnemy();
		//Determine enemy type, currently only normal monsters

		newEnemy->Init(playerPosition);
		--normal;
		spawnTimer = 0.0f;

		return newEnemy;
	}

	return NULL;
}