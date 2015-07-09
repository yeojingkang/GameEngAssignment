#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Player.h"
#include "EnemyType.h"

#include "Definitions.h"

class CEnemy
{
public:
	CEnemy();
	~CEnemy();

	void Init(cocos2d::Vec2 playerPos, CEnemyType type, CPlayer* player);
	void Update(float, cocos2d::Vec2);

	cocos2d::Sprite* getSprite(void){ return theSprite; };

	string getTypeName(){ return typeName; }

	int getHP(){ return hp; }
	void decreaseHP(int amt){ hp -= amt; }

	bool getActive(){ return active; }

	void Die();

	void MoveToPlayer(Sprite* sprite);

private:
	float speed;
	cocos2d::Vec2 position, direction;
	cocos2d::Sprite* theSprite;
	string typeName;
	unsigned int hp, bounty;
	CPlayer* thePlayer;
	bool active;

	void finishedMoving(Object *pSender);
};

#endif