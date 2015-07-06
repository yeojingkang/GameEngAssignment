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
monsterSpawnList CSubwave::update(float dt, cocos2d::Vec2 playerPosition){
	monsterSpawnList list;

	//If there is no more monster left to spawn, end 
	if (getTotalMonsters() <= 0)
		return list;

	spawnTimer += dt;

	if (spawnTimer >= 1.0f){
		//Determine enemy type, currently only normal monsters
		list["Normal"] = 1;
		--normal;

		spawnTimer = 0.0f;
	}

	return list;
}