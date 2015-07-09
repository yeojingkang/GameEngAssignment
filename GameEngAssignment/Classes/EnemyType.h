#ifndef __ENEMYTYPE_H__
#define __ENEMYTYPE_H__

#include "cocos2d.h"

using namespace std;

class CEnemyType
{
public:
	CEnemyType();
	~CEnemyType();

	void Init(string, int, int, float);
	void Overwrite(int, int, float);

	string getName(){ return name; }
	int getHP(){ return hp; }
	int getBounty(){ return bounty; }
	int getSpeed(){ return speed; }

private:
	string name;
	unsigned int hp;
	unsigned int bounty;
	float speed;
};

#endif