#include "Player.h"

USING_NS_CC;

CPlayer CPlayer::thePlayer;

CPlayer::CPlayer()
{
	xPos = 0;
	yPos = 0;
	moveSpeed = 0;
	velocity = new Point(0, 0);
	playerSprite = NULL;
	shootVec = NULL;
	gold = 0;
	hp = 100;
	didMoved = false;
}

void CPlayer::Init()
{
	SetPlayerSprite("player.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;
	moveSpeed = 200;
	playerSprite->setPosition(xPos, yPos);
	playerSprite->setScale(1.5f);
	shootVec = NULL;
	didMoved = false;

	//setting players physics body
	playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
	playerBody->setGravityEnable(false);
	playerBody->setDynamic(false);
	playerBody->setContactTestBitmask(0xFFFFFFFF);
	playerSprite->setTag(PLAYER_TAG);
	playerSprite->setPhysicsBody(playerBody);
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

void CPlayer::SetMoveSpeed(float speed)
{
	this->moveSpeed = speed;
}

float CPlayer::GetMoveSpeed(void)
{
	return this->moveSpeed;
}

void CPlayer::SetShootVec(Vec2* shootVec)
{
	this->shootVec = shootVec;
}

Vec2* CPlayer::GetShootVec(void)
{
	return this->shootVec;
}

void CPlayer::SetDidMoved(bool didMoved)
{
	this->didMoved = didMoved;
}

bool CPlayer::GetDidMoved()
{
	return this->didMoved;
}

void CPlayer::doneMovement(Object *pSender)
{
	CPlayer *eSprite = CPlayer::getInstance();
	this->Movement();
}

void CPlayer::Movement()
{
	float time = 10 / moveSpeed;
	Vec2 targetPos = this->getPlayerSprite()->getPosition() + this->GetVelocity()->getNormalized() * 10;
	auto actionMove = MoveTo::create(time, targetPos);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(CPlayer::doneMovement, this));
	Sequence* seq = Sequence::create(actionMove, actionDone, NULL);
	this->getPlayerSprite()->runAction(seq);
}

void CPlayer::update(float dt)
{
}