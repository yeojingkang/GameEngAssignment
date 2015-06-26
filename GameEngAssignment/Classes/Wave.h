#pragma once

#include "cocos2d.h"
#include "Subwave.h"

using namespace std;

class CWave
{
public:
	CWave();
	~CWave();

	vector<CEnemy*>* update(float dt, cocos2d::Vec2 playerPosition);

	void setSubwave(float activateTime, int normal);
	void setSubwave(CSubwave* newSubwave);

	int getNormalMonsters(){ return normal; }
	int getTotalMonsters();

	void spawnedNormalMonster(){ --normal; }

private:
	int normal;
	float elapsedTime;
	vector<CSubwave*> theSubwaves;
};

