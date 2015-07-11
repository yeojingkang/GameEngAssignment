#include "Bullet.h"

USING_NS_CC;

CBullet::CBullet()
{
	xPos = 0;
	yPos = 0;
	active = false;
	bulletSprite = NULL;
	moveVec = NULL;
	bulletSpeed = 0;
	active = false;
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
	bulletSpeed = 200;
	bounds = bulletSprite->getBoundingBox();
	damage = 100;
	moveVec = NULL;

	bulletSprite->setTag(BULLET_TAG);

	bulletBody = PhysicsBody::createBox(bulletSprite->getContentSize());

	bulletBody->setDynamic(false);
	//bulletBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	//bulletBody->setCategoryBitmask(ENEMY_COLLISION_BITMASK);
	bulletBody->setContactTestBitmask(0xFFFFFFFF);

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

void CBullet::SetBulletSpeed(float s)
{
	this->bulletSpeed = s;
}

float CBullet::GetBulletSpeed()
{
	return this->bulletSpeed;
}

void CBullet::SetMoveVec(Vec2* moveVec)
{
	this->moveVec = moveVec;
}

Vec2* CBullet::GetMoveVec(void)
{
	return this->moveVec;
}

void CBullet::SetBulletDamage(float damage)
{
	this->damage = damage;
}

float CBullet::GetBulletDamage(void)
{
	return this->damage;
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
		return true;
	}
	else
		return false;
}

void CBullet::MoveForward()
{
	float time = 1000 / bulletSpeed;
	Vec2 targetPos = bulletSprite->getPosition() + this->moveVec->getNormalized() * 1000;
	auto actionMove = MoveTo::create(time, targetPos);
	bulletSprite->runAction(actionMove);
}

void CBullet::Update(float dt)
{
	if (bulletSprite->getNumberOfRunningActions() == 0)
	{
		delete this;
	}
}