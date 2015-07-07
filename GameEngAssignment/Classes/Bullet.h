#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"
#include <string>
#include "Enemy.h"

#include "Definitions.h"

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
	
	void SetMoveVec(Vec2* v);
	Vec2* GetMoveVec();

	void SetBulletSpeed(float s);
	float GetBulletSpeed();

	bool CheckCollision(Rect r);
	bool CheckCollision(CEnemy* enemy);

	void Update(float dt);

private:
	Sprite* bulletSprite;
	PhysicsBody* bulletBody;

	float xPos;
	float yPos;

	bool active;

	Vec2* movementVec;
	float bulletSpeed;
	unsigned int damage;

	Rect bounds;

};

#endif // __BULLET_H__