#include "EnemyType.h"


CEnemyType::CEnemyType() :
name(""),
hp(0),
bounty(0),
speed(0.f),
color(cocos2d::Color3B(1.0f, 1.0f, 1.0f))
{
}
CEnemyType::~CEnemyType()
{
}

void CEnemyType::Init(string name, int hp, int bounty, float speed, cocos2d::Color3B color){
	this->name = name;
	this->hp = hp;
	this->bounty = bounty;
	this->speed = speed;
	this->color = color;
}
void CEnemyType::Overwrite(int hp, int bounty, float speed, cocos2d::Color3B color){
	this->hp = hp;
	this->bounty = bounty;
	this->speed = speed;
	this->color = color;
}