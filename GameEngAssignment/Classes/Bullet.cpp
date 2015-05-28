#include "Bullet.h"

USING_NS_CC;

CBullet::CBullet()
{
	xPos = 0;
	yPos = 0;
	active = false;
	bulletSprite = NULL;
}

void CBullet::Init()
{
	SetSprite("bullet.png");
	active = false;
	xPos = 0;
	yPos = 0;
	bulletSprite->setPosition(xPos, yPos);
	bounds = bulletSprite->getBoundingBox();

	
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

void CBullet::SetPlayerPos(Vec2 pos)
{
	this->playerPos = pos;
}

Vec2 CBullet::GetPlayerPos()
{
	return this->playerPos;
}

bool CBullet::CheckCollision(Rect r)
{
	if (this->bounds.intersectsRect(r))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void CBullet::Update(float dt)
{
	Vec2 dirVector = bulletSprite->getPosition() - playerPos;
	dirVector.normalize();

	bulletSprite->setPosition(bulletSprite->getPosition() + dirVector * dt * 100);
}