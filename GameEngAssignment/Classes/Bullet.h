#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include <string>
#include "Enemy.h"

#include "Definitions.h"

using namespace cocos2d;
using namespace std;

class CBullet : public cocos2d::Sprite
{
public:

	CBullet();
	~CBullet();

	static CBullet* create();

	void Init();
	
	void SetActive(bool);
	bool GetActive();
	
	void SetMoveVec(Vec2* moveVec);
	Vec2* GetMoveVec();

	void SetBulletSpeed(float s);
	float GetBulletSpeed();

	void SetBulletDamage(float);
	float GetBulletDamage(void);

	void MoveForward();

	void Update(float dt);

	//handler for onContactBegin
	//handler for detecting collision
	bool onContactBegin(PhysicsContact &contact);

private:
	PhysicsBody* bulletBody;

	float xPos;
	float yPos;

	bool active;

	Vec2* moveVec;

	float bulletSpeed;
	float damage;

	Rect bounds;

};

#endif // __BULLET_H__