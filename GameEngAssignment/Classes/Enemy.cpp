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
	
	/*if (CCRANDOM_0_1() > 0.5f)
		position = Vec2(round(CCRANDOM_0_1()) * 1280, CCRANDOM_0_1() * 720);
	else
		position = Vec2(CCRANDOM_0_1() * 1280, round(CCRANDOM_0_1()) * 720);*/
	
	position = Vec2(0, -720);

	direction = (playerPos - position).getNormalized();

	theSprite = cocos2d::Sprite::create("enemy.png");

	theSprite->setScale(1.0f);

	updateSpritePosition();

	auto enemyBody = PhysicsBody::createBox(theSprite->getContentSize());

	//enemyBody->setDynamic(false);
	enemyBody->setGravityEnable(false);
	enemyBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	enemyBody->setCategoryBitmask(BULLET_COLLISION_BITMASK);
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

	direction = (playerPos - position).getNormalized();
	position += speed * direction * dt;

	updateSpritePosition();
}

void CEnemy::MoveToPlayer()
{
	theSprite->runAction(MoveTo::create(100, position));
}

void CEnemy::updateSpritePosition(){
}

void CEnemy::Die(){
	thePlayer->AddGold(bounty);
	active = false;
}