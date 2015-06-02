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
	bulletSprite->setScale(1.5f);
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
	
}