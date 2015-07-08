#include "EnemyType.h"


CEnemyType::CEnemyType() :
name(""),
hp(0),
bounty(0),
speed(0.f)
{
}
CEnemyType::~CEnemyType()
{
}

void CEnemyType::Init(string name, int hp, int bounty, float speed){
	this->name = name;
	this->hp = hp;
	this->bounty = bounty;
	this->speed = speed;
}
void CEnemyType::Overwrite(int hp, int bounty, float speed){
	this->hp = hp;
	this->bounty = bounty;
	this->speed = speed;
}