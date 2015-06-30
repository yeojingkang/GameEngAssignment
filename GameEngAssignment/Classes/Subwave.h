#pragma once

#include "Enemy.h"

class CSubwave
{
public:
	CSubwave();
	~CSubwave();

	void init(float activateTime, int normal);
	CEnemy* update(float dt, cocos2d::Vec2 playerPosition);
	void activate(){ active = true; }

	int getTotalMonsters(){ return normal; }
	bool getActive(){ return active; }
	float getActivateTime(){ return activateTime; }

private:
	bool active;
	float activateTime, spawnTimer;
	int normal;
};

