#pragma once

#include "Enemy.h"

class CSubwave
{
public:
	CSubwave();
	~CSubwave();

	void init(float activateTime, vector<int> enemies);
	int update(float dt, cocos2d::Vec2 playerPosition);
	void activate(){ active = true; }

	int getTotalMonsters();
	bool getActive(){ return active; }
	float getActivateTime(){ return activateTime; }

private:
	bool active;
	float activateTime, spawnTimer;
	vector<int> enemies;
};

