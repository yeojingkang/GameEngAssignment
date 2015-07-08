#include "Subwave.h"


CSubwave::CSubwave()
{
}
CSubwave::~CSubwave()
{
}

void CSubwave::init(float activateTime, vector<int> enemies){
	this->activateTime = activateTime;
	this->active = false;
	this->spawnTimer = 0.0f;
	this->enemies = enemies;
}
int CSubwave::update(float dt, cocos2d::Vec2 playerPosition){
	//If there is no more monster left to spawn, end 
	if (getTotalMonsters() <= 0)
		return -1;

	spawnTimer += dt;

	if (spawnTimer >= 1.0f){
		spawnTimer = 0.0f;

		//Determine enemy type to spawn
		int type = cocos2d::random(0, (int)enemies.size() - 1);
		--enemies[type];

		return type;
	}

	return -1;
}

int CSubwave::getTotalMonsters(){
	int total = 0;

	for (vector<int>::iterator itr = enemies.begin(); itr != enemies.end(); ++itr){
		total += *itr;
	}

	return total;
}