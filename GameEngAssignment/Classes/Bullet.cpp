#include "Bullet.h"

USING_NS_CC;

CBullet::CBullet()
{
	xPos = 0;
	yPos = 0;
	active = false;
	moveVec = NULL;
	bulletSpeed = 0;
	active = false;
}
CBullet::~CBullet(){}

CBullet* CBullet::create()
{
	CBullet* bullet = new CBullet();
	if (bullet->initWithFile("bullet.png"))
	{
		bullet->autorelease();
		bullet->Init();
		return bullet;
	}

	CC_SAFE_DELETE(bullet);
	return NULL;
}

void CBullet::Init()
{
	//SetSprite("bullet.png");
	active = false;
	xPos = 0;
	yPos = 0;
	this->setPosition(xPos, yPos);
	this->setScale(2.0f);
	bulletSpeed = 500;
	bounds = this->getBoundingBox();
	damage = 50;
	moveVec = NULL;

	this->setTag(BULLET_TAG);

	bulletBody = PhysicsBody::createBox(this->getContentSize());

	bulletBody->setDynamic(false);
	//bulletBody->setCollisionBitmask(BULLET_COLLISION_BITMASK);
	//bulletBody->setCategoryBitmask(ENEMY_COLLISION_BITMASK);
	bulletBody->setContactTestBitmask(0xFFFFFFFF);

	this->setPhysicsBody(bulletBody);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(CBullet::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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
	
	moveVec->x += (CCRANDOM_0_1() * moveVec->x - moveVec->x / 2);
	moveVec->y += (CCRANDOM_0_1() * moveVec->y - moveVec->y / 2);

	this->moveVec = moveVec;
	float angleToRot = atan2(moveVec->y, moveVec->x);
	angleToRot = -angleToRot * (180 / 3.14159);

	if (angleToRot < 0)
	{
		angleToRot = 360 - (-angleToRot);
	}

	this->setRotation(angleToRot);

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
	//if (this->bounds.intersectsRect(enemy->getSprite()->getBoundingBox())){
	//	enemy->decreaseHP(damage);
	//	return true;
	//}
	//else
	//	return false;
	return false;
}

void CBullet::MoveForward()
{
	float time = 1000 / bulletSpeed;
	Vec2 targetPos = this->getPosition() + this->GetMoveVec()->getNormalized() * 1000;
	auto actionMove = MoveTo::create(time, targetPos);
	Sequence* seq = Sequence::create(actionMove, RemoveSelf::create(), NULL);
	this->runAction(seq);
}

bool CBullet::onContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == BULLET_TAG && nodeB->getTag() == ENEMY_TAG)
		{
			nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeB->getTag() == BULLET_TAG && nodeA->getTag() == ENEMY_TAG)
		{
			nodeB->removeFromParentAndCleanup(true);
		}
	}
	return true;
}

void CBullet::Update(float dt)
{
}