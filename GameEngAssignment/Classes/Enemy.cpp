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
	position = Vec2(CCRANDOM_0_1() * 300, CCRANDOM_0_1() * 300);
	direction = (playerPos - position).getNormalized();

	theSprite = cocos2d::Sprite::create("CloseNormal.png");

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