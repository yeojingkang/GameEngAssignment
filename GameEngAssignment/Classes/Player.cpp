#include "Player.h"

USING_NS_CC;

//singleton stuffs for other classes to reference
static CPlayer *thePlayer = nullptr;

CPlayer::CPlayer()
{
	xPos = 0;
	yPos = 0;
	moveSpeed = 0;
	velocity = new Point(0, 0);
	shootVec = NULL;
	gold = 0;
	hp = 100;
	didMoved = false;
	active = false;
}

CPlayer* CPlayer::create()
{
	CPlayer* playerSprite = new CPlayer();
	
	if (playerSprite->initWithFile("player.png"))
	{
		playerSprite->autorelease();
		return playerSprite;
	}

	CC_SAFE_DELETE(playerSprite);
	return NULL;
}

CPlayer* CPlayer::getInstance()
{
	if (!thePlayer)
	{
		thePlayer = CPlayer::create();
		thePlayer->Init();
	}
	return thePlayer;
}

void CPlayer::Init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;
	moveSpeed = 200;
	this->setPosition(xPos, yPos);
	this->setScale(1.5f);
	shootVec = NULL;
	didMoved = false;
	active = true;

	//setting players physics body
	this->setTag(PLAYER_TAG);
	playerBody = PhysicsBody::createBox(this->getContentSize());
	playerBody->setGravityEnable(false);
	playerBody->setContactTestBitmask(0xFFFFFFFF);
	this->setPhysicsBody(playerBody);

	//listener for onContactBegin
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CPlayer::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
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

void CPlayer::SetActive(bool active)
{
	this->active = active;
}

bool CPlayer::GetActive()
{
	return this->active;
}

void CPlayer::doneMovement(Ref *pSender)
{
	CPlayer *eSprite = CPlayer::getInstance();
	this->Movement();
}

void CPlayer::Movement()
{
	float time = 10 / moveSpeed;
	Vec2 targetPos = this->getPosition() + this->GetVelocity()->getNormalized() * 10;
	auto actionMove = MoveTo::create(time, targetPos);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(CPlayer::doneMovement, this));
	Sequence* seq = Sequence::create(actionMove, actionDone, NULL);
	this->runAction(seq);
}

bool CPlayer::onContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	//check collision betweenplayer and enemy

	//player dies
	//sets active to false so gamescene can go to gameoverscene
	//player singleton is set to nullptr to ensure that the player can be added as a child again
	//also ensures that there are no assertion error due to it being a singleton class
	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == PLAYER_TAG && nodeB->getTag() == ENEMY_TAG)
		{
			dynamic_cast<CPlayer*>(nodeA)->active = false;
			thePlayer = nullptr;
		}
		else if (nodeB->getTag() == PLAYER_TAG && nodeA->getTag() == ENEMY_TAG)
		{
			dynamic_cast<CPlayer*>(nodeB)->active = false;
			thePlayer = nullptr;
		}
	}

	return true;
}