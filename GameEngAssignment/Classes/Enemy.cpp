#include "Enemy.h"

USING_NS_CC;

CEnemy::CEnemy()
{
}
CEnemy::~CEnemy()
{
}

void CEnemy::Init(cocos2d::Vec2 playerPos, enemyType type, CPlayer* player){
	
	if (CCRANDOM_0_1() > 0.5f)
		position = Vec2(round(CCRANDOM_0_1()) * 1280, CCRANDOM_0_1() * 720);
	else
		position = Vec2(CCRANDOM_0_1() * 1280, round(CCRANDOM_0_1()) * 720);
	
	direction = (playerPos - position).getNormalized();

	theSprite = cocos2d::Sprite::create("enemy.png");

	theSprite->setScale(1.0f);

	updateSpritePosition();

	auto enemyBody = PhysicsBody::createBox(theSprite->getContentSize());

	enemyBody->setDynamic(false);
	enemyBody->setCollisionBitmask(ENEMY_COLLISION_BITMASK);
	enemyBody->setContactTestBitmask(true);

	theSprite->setPhysicsBody(enemyBody);

	this->type = type;
	this->thePlayer = player;

	if (this->type == ENEMYTYPE_NORMAL){
		hp = 100;
		bounty = 10;
		speed = 25.0f;
	}
}

void CEnemy::Update(float dt, cocos2d::Vec2 playerPos){
	if (hp <= 0){
		Die();
	}

	direction = (playerPos - position).getNormalized();
	position += speed * direction * dt;

	updateSpritePosition();
}

void CEnemy::updateSpritePosition(){
	theSprite->setPosition(position);
}

void CEnemy::Die(){
	thePlayer->AddGold(bounty);
	delete this;
}