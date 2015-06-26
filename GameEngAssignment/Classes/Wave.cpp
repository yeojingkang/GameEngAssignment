#include "Wave.h"


CWave::CWave()	:
elapsedTime(0.0f)
{
}
CWave::~CWave()
{
}

vector<CEnemy*>* CWave::update(float dt, cocos2d::Vec2 playerPosition){
	vector<CEnemy*>* spawnedEnemies = new vector<CEnemy*>();

	elapsedTime += dt;

	for (vector<CSubwave*>::iterator itr = theSubwaves.begin(); itr != theSubwaves.end(); ++itr){
		if ((*itr)->getActive()){
			//If subwave spawned an enemy, add it to the list to return to gameScene
			if (CEnemy* newEnemy = (*itr)->update(dt, playerPosition)){
				spawnedEnemies->push_back(newEnemy);
			}
		}
		else{
			//Check if enough time has passed for subwave to activate
			if (elapsedTime >= (*itr)->getActivateTime())
				(*itr)->activate();
		}
	}

	return spawnedEnemies;
}

void CWave::setSubwave(float activateTime, int normal){
	CSubwave* newSubwave = new CSubwave();
	newSubwave->init(activateTime, normal);
	theSubwaves.push_back(newSubwave);
}
void CWave::setSubwave(CSubwave* newSubwave){
	theSubwaves.push_back(newSubwave);
}

int CWave::getTotalMonsters(){
	int total = 0;

	for (vector<CSubwave*>::iterator itr = theSubwaves.begin(); itr != theSubwaves.end(); ++itr){
		total += (*itr)->getTotalMonsters();
	}

	return total;
}