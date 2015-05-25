#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"

class CEnemy
{
public:
	CEnemy();
	~CEnemy();

	void Init(cocos2d::Vec2);
	void Update(float, cocos2d::Vec2);

	cocos2d::Sprite* getSprite(void){ return theSprite; };

private:
	float speed;
	cocos2d::Vec2 position, direction;
	cocos2d::Sprite* theSprite;

	void updateSpritePosition();
};

#endif