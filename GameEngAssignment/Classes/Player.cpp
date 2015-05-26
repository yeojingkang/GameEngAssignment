#include "Player.h"

USING_NS_CC;

CPlayer::CPlayer()
{
	xPos = 0;
	yPos = 0;
	velocity = new Point(0, 0);
	playerSprite = NULL;
}

void CPlayer::Init()
{
	SetPlayerSprite("player.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;
	playerSprite->setPosition(xPos, yPos);
	bounds = playerSprite->getBoundingBox();

	
}

void CPlayer::SetPlayerSprite(string filename)
{
	this->playerSprite = Sprite::create(filename);
}

Sprite* CPlayer::getPlayerSprite()
{
	return playerSprite;
}

bool CPlayer::CheckCollision(Rect r)
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

void CPlayer::MoveLeftRight(bool left, float speed)
{
	if (left)
	{
		velocity->x = -speed;
	}
	else if (!left)
	{
		velocity->x = speed;
	}
}

void CPlayer::MoveUpDown(bool up, float speed)
{
	if (up)
	{
		velocity->y = speed;
	}
	else if (!up)
	{
		velocity->y = -speed;
	}
}

void CPlayer::SetVelocity(float x, float y)
{
	velocity->set(x, y);
}

Vec2* CPlayer::GetVelocity()
{
	return velocity;
}

void CPlayer::update(float dt)
{
	playerSprite->setPositionX(playerSprite->getPositionX() + (velocity->x * dt));
	playerSprite->setPositionY(playerSprite->getPositionY() + (velocity->y * dt));
}