#include "Wave.h"


CWave::CWave()	:
elapsedTime(0.0f)
{
}
CWave::~CWave()
{
}

monsterSpawnList CWave::update(float dt, cocos2d::Vec2 playerPosition){
	monsterSpawnList list;

	elapsedTime += dt;

	for (vector<CSubwave*>::iterator itr = theSubwaves.begin(); itr != theSubwaves.end(); ++itr){
		if ((*itr)->getActive()){
			monsterSpawnList newList = (*itr)->update(dt, playerPosition);
			list.insert(newList.begin(), newList.end());
		}
		else{
			//Check if enough time has passed for subwave to activate
			if (elapsedTime >= (*itr)->getActivateTime())
				(*itr)->activate();
		}
	}

	return list;
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