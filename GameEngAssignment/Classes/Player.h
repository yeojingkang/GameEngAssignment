#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;
using namespace std;

class CPlayer
{
public:

	CPlayer();
	~CPlayer();

	void Init();

	void SetPlayerSprite(string filename);
	Sprite* getPlayerSprite();

	void SetVelocity(float, float);
	Vec2* GetVelocity();

	bool CheckCollision(Rect r);

	void MoveUpDown(bool up, float speed);
	void MoveLeftRight(bool left, float speed);

	void update(float dt);

private:
	Sprite* playerSprite;

	float xPos;
	float yPos;

	Vec2* velocity;

	Rect bounds;
};

#endif // __PLAYER_H__