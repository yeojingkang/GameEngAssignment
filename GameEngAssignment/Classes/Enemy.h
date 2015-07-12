#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Player.h"
#include "EnemyType.h"

#include "Definitions.h"

class CEnemy : public cocos2d::Sprite
{
public:
	CEnemy();
	~CEnemy();

	static CEnemy* create();

	void Init(CEnemy* eSprite, cocos2d::Vec2 playerPos, CEnemyType type, CPlayer* player);
	void Update(float, cocos2d::Vec2);

	string getTypeName(){ return typeName; }

	int getHP(){ return hp; }
	void decreaseHP(int amt){ hp -= amt; }

	void Die();

	void MoveToPlayer(CEnemy* eSprite);

	//handler for onContactBegin
	//handler for detecting collision
	bool onContactBegin(PhysicsContact &contact);

private:
	float speed;
	cocos2d::Vec2 position, direction;
	string typeName;
	unsigned int hp, bounty;
	CPlayer* thePlayer;

	void finishedMoving(Object *pSender);
};

#endif