#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;
using namespace std;

class CPlayer
{

protected:
	CPlayer();

public:

	static CPlayer* getInstance()
	{
		return &thePlayer;
	}

	void Init();

	void SetPlayerSprite(string filename);
	Sprite* getPlayerSprite();

	void SetVelocity(float, float);
	Vec2* GetVelocity();

	bool CheckCollision(Rect r);

	void MoveUpDown(bool up, float speed);
	void MoveLeftRight(bool left, float speed);

	void SetMoveSpeed(float);
	float GetMoveSpeed();

	void SetShootVec(Vec2*);
	Vec2* GetShootVec();

	int GetGold(){ return gold; }
	void AddGold(int amt){ gold += amt; }
	void DecreaseGold(int amt){ gold -= amt; }

	int GetHP(){ return hp; }

	void update(float dt);

private:

	static CPlayer thePlayer;

	Sprite* playerSprite;

	float xPos;
	float yPos;

	float moveSpeed;

	Vec2* velocity;

	Vec2* shootVec;

	Rect bounds;

	unsigned int gold, hp;
};

#endif // __PLAYER_H__