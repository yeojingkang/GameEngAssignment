#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Player.h"

enum enemyType{
	ENEMYTYPE_NORMAL = 0,
	ENEMYTYPE_TOTAL
};

class CEnemy
{
public:
	CEnemy();
	~CEnemy();

	void Init(cocos2d::Vec2, enemyType, CPlayer*);
	void Update(float, cocos2d::Vec2);

	cocos2d::Sprite* getSprite(void){ return theSprite; };

	enemyType getType(){ return type; }

	int getHP(){ return hp; }
	void decreaseHP(int amt){ hp -= amt; }

	void Die();

private:
	float speed;
	cocos2d::Vec2 position, direction;
	cocos2d::Sprite* theSprite;
	enemyType type;
	unsigned int hp, bounty;
	CPlayer* thePlayer;

	void updateSpritePosition();
};

#endif