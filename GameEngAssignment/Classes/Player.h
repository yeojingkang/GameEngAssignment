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

	void SetGunPoint(Vec2*);
	Vec2* GetGunPoint();

	bool CheckCollision(Rect r);

	void MoveUpDown(bool up, float speed);
	void MoveLeftRight(bool left, float speed);

	void SetMoveSpeed(float);
	float GetMoveSpeed();

	int GetGold(){ return gold; }
	void AddGold(int amt){ gold += amt; }
	void DecreaseGold(int amt){ gold -= amt; }

	int GetHP(){ return hp; }

	void update(float dt);

private:
	Sprite* playerSprite;

	float xPos;
	float yPos;

	float moveSpeed;

	Vec2* velocity;

	Vec2* gunPoint;

	Rect bounds;

	unsigned int gold, hp;
};

#endif // __PLAYER_H__