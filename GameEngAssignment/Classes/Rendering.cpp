#include "Rendering.h"

USING_NS_CC;

Rendering::Rendering()
{
	xPos = 0;
	yPos = 0;
	backgroundSprite = NULL;
}

Rendering::~Rendering()
{

}

void Rendering::Init()
{
	setBackgroundSprite("background.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;
	backgroundSprite->setPosition(xPos, yPos);
}

void Rendering::setBackgroundSprite(string filename)
{
	this->backgroundSprite = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSprite()
{
	return backgroundSprite;
}