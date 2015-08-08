#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include <string>

using namespace cocos2d;
using namespace std;

class CPlayer : public cocos2d::Sprite
{

protected:
	CPlayer();

public:

	static CPlayer* create();
	static CPlayer* getInstance();
	void setNull();

	void Init();

	void SetVelocity(float, float);
	Vec2* GetVelocity();

	void MoveUpDown(bool up, float speed);
	void MoveLeftRight(bool left, float speed);

	void SetMoveSpeed(float);
	float GetMoveSpeed();

	void SetShootVec(Vec2*);
	Vec2* GetShootVec();

	void SetActive(bool);
	bool GetActive();

	int GetGold(){ return gold; }
	void AddGold(int amt){ gold += amt; }
	void DecreaseGold(int amt){ gold -= amt; }

	int GetHP(){ return hp; }

	void Movement();
	void doneMovement(Ref *pSender);
	void SetDidMoved(bool);
	bool GetDidMoved();

	//handler for detecting collision
	bool onContactBegin(PhysicsContact &contact);

private:

	PhysicsBody* playerBody;

	float xPos;
	float yPos;

	float moveSpeed;

	Vec2* velocity;

	Vec2* shootVec;

	bool active;

	bool didMoved;

	unsigned int gold, hp;
};

#endif // __PLAYER_H__