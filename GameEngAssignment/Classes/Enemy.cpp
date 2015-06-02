#include "Enemy.h"

USING_NS_CC;

CEnemy::CEnemy()
{
}
CEnemy::~CEnemy()
{
}

void CEnemy::Init(cocos2d::Vec2 playerPos){
	speed = 25.0f;
	
	if (CCRANDOM_0_1() > 0.5f)
		position = Vec2(round(CCRANDOM_0_1()) * 1280, CCRANDOM_0_1() * 720);
	else
		position = Vec2(CCRANDOM_0_1() * 1280, round(CCRANDOM_0_1()) * 720);
	
	direction = (playerPos - position).getNormalized();

	theSprite = cocos2d::Sprite::create("enemy.png");

	theSprite->setScale(1.0f);

	updateSpritePosition();
}

void CEnemy::Update(float dt, cocos2d::Vec2 playerPos){
	direction = (playerPos - position).getNormalized();
	position += speed * direction * dt;
	
	updateSpritePosition();
}

void CEnemy::updateSpritePosition(){
	theSprite->setPosition(position);
}