#include "Bullet.h"

USING_NS_CC;

CBullet::CBullet()
{
	xPos = 0;
	yPos = 0;
	active = false;
	bulletSprite = NULL;
	bulletSpeed = 0;
	active = false;
	movementVec = NULL;
}
CBullet::~CBullet(){}

void CBullet::Init()
{
	SetSprite("bullet.png");
	active = false;
	xPos = 0;
	yPos = 0;
	bulletSprite->setPosition(xPos, yPos);
	bulletSprite->setScale(1.5f);
	bulletSpeed = 100;
	movementVec = new Vec2(0, 0);
	bounds = bulletSprite->getBoundingBox();
	damage = 100;

	bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize());

	bulletBody->setDynamic(false);
	bulletBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	bulletBody->setContactTestBitmask(true);

	bulletSprite->setPhysicsBody(bulletBody);

}

void CBullet::SetSprite(string filename)
{
	this->bulletSprite = Sprite::create(filename);
}

Sprite* CBullet::GetSprite()
{
	return this->bulletSprite;
}

void CBullet::SetActive(bool active)
{
	this->active = active;
}

bool CBullet::GetActive()
{
	return this->active;
}

void CBullet::SetMoveVec(Vec2* v)
{
	this->movementVec = v;
}

Vec2* CBullet::GetMoveVec()
{
	return this->movementVec;
}

void CBullet::SetBulletSpeed(float s)
{
	this->bulletSpeed = s;
}

float CBullet::GetBulletSpeed()
{
	return this->bulletSpeed;
}

bool CBullet::CheckCollision(Rect r)
{
	if (this->bounds.intersectsRect(r))
	{
		active = false;
		return true;
	}
	else
	{
		return false;
	}
}

bool CBullet::CheckCollision(CEnemy* enemy){
	if (this->bounds.intersectsRect(enemy->getSprite()->getBoundingBox())){
		enemy->decreaseHP(damage);
		active = false;
		return true;
	}
	else
		return false;
}

void CBullet::Update(float dt)
{
	bulletSprite->setPosition(bulletSprite->getPositionX() + movementVec->x * dt * this->bulletSpeed, bulletSprite->getPositionY() + movementVec->y * dt * this->bulletSpeed);
	
}