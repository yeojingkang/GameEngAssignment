#include "Enemy.h"

USING_NS_CC;

CEnemy::CEnemy() :
typeName(""),
hp(0),
bounty(0),
thePlayer(NULL),
active(false)
{
}
CEnemy::~CEnemy()
{
}

void CEnemy::Init(cocos2d::Vec2 playerPos, CEnemyType type, CPlayer* player){
	
	if (CCRANDOM_0_1() > 0.5f)
		position = Vec2(round(CCRANDOM_0_1()) * 1280, CCRANDOM_0_1() * 720);
	else
		position = Vec2(CCRANDOM_0_1() * 1280, round(CCRANDOM_0_1()) * 720);
	
	//position = Vec2(0, -720);

	direction = (playerPos - position).getNormalized();

	theSprite = cocos2d::Sprite::create("enemy.png");

	theSprite->setScale(1.0f);

	theSprite->setTag(ENEMY_TAG);

	auto enemyBody = PhysicsBody::createBox(theSprite->getContentSize());

	//enemyBody->setDynamic(false);
	enemyBody->setGravityEnable(false);
	//enemyBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	//enemyBody->setCategoryBitmask(BULLET_COLLISION_BITMASK);
	enemyBody->setContactTestBitmask(0xFFFFFFFF);

	theSprite->setPhysicsBody(enemyBody);

	this->typeName = type.getName();
	this->thePlayer = player;

	this->hp = type.getHP();
	this->bounty = type.getBounty();
	this->speed = type.getSpeed();

	active = true;
}

void CEnemy::Update(float dt, cocos2d::Vec2 playerPos){
	if (hp <= 0){
		Die();
	}
}

void CEnemy::finishedMoving(Object *pSender){
	Sprite *sprite = (Sprite *)pSender;
	this->MoveToPlayer(sprite);
}
void CEnemy::MoveToPlayer(Sprite* sprite)
{
	//float distance = thePlayer->getPlayerSprite()->getPosition().distance(theSprite->getPosition());
	float time = 10 / speed;
	Vec2 targetPosition = theSprite->getPosition() + (thePlayer->getPlayerSprite()->getPosition() - theSprite->getPosition()).getNormalized() * 10;

	auto actionMove = MoveTo::create(time, targetPosition);
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(CEnemy::finishedMoving, this));
	sprite->runAction(Sequence::create(actionMove, actionMoveDone, NULL));
}

void CEnemy::Die(){
	thePlayer->AddGold(bounty);
	active = false;
}