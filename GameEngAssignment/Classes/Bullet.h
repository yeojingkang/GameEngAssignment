#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;
using namespace std;

class CBullet
{
public:

	CBullet();
	~CBullet();

	void Init();

	void SetSprite(string filename);
	Sprite* GetSprite();
	
	void SetActive(bool);
	bool GetActive();
	
	void SetPlayerPos(Vec2);
	Vec2 GetPlayerPos();

	bool CheckCollision(Rect r);

	void Update(float dt);

private:
	Sprite* bulletSprite;

	float xPos;
	float yPos;

	bool active;

	Vec2 playerPos;

	Rect bounds;
};

#endif // __BULLET_H__