#include "Wave.h"


CWave::CWave()	:
elapsedTime(0.0f)
{
}
CWave::~CWave()
{
}

vector<int> CWave::update(float dt, cocos2d::Vec2 playerPosition){
	vector<int> list;

	elapsedTime += dt;

	for (vector<CSubwave*>::iterator itr = theSubwaves.begin(); itr != theSubwaves.end(); ++itr){
		if ((*itr)->getActive()){
			int type = (*itr)->update(dt, playerPosition);

			//If list doesn't have an element to store the count of the enemy type, create it
			if (type >= 0){
				if (type + 1 > list.size()){
					while (list.size() < type + 1){
						list.push_back(0);
					}
				}

				++list[type];
			}
		}
		else{
			//Check if enough time has passed for subwave to activate
			if (elapsedTime >= (*itr)->getActivateTime())
				(*itr)->activate();
		}
	}

	return list;
}

void CWave::setSubwave(float activateTime, vector<int> enemies){
	CSubwave* newSubwave = new CSubwave();
	newSubwave->init(activateTime, enemies);
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

void CWave::typeNotDefined(int type){
	for (vector<CSubwave*>::iterator itr = theSubwaves.begin(); itr != theSubwaves.end(); ++itr){
		if ((*itr)->hasType(type))
			(*itr)->typeNotDefined(type);
	}
}