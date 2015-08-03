#include "Rendering.h"

USING_NS_CC;

Rendering::Rendering()
{
	xPos = 0;
	yPos = 0;
	backgroundSprite = NULL;
	backgroundSpriteTop = NULL;
	backgroundSpriteTopLeft = NULL;
	backgroundSpriteTopRight = NULL;
	backgroundSpriteBottom = NULL;
	backgroundSpriteBottomLeft = NULL;
	backgroundSpriteBottomRight = NULL;
	backgroundSpriteLeft = NULL;
	backgroundSpriteRight = NULL;
}

Rendering::~Rendering()
{

}

void Rendering::Init()
{
	setBackgroundSprite("background.png");
	setBackgroundSpriteTop("background_outside_top.png");
	setBackgroundSpriteTopLeft("background_outside.png");
	setBackgroundSpriteTopRight("background_outside.png");
	setBackgroundSpriteBottom("background_outside_bottom.png");
	setBackgroundSpriteBottomLeft("background_outside.png");
	setBackgroundSpriteBottomRight("background_outside.png");
	setBackgroundSpriteLeft("background_outside_left.png");
	setBackgroundSpriteRight("background_outside_right.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	xPos = origin.x + visibleSize.width / 2;
	yPos = origin.y + visibleSize.height / 2;

	backgroundSprite->setPosition(xPos, yPos);
	backgroundSpriteTop->setPosition(xPos, yPos + 1066);
	backgroundSpriteTopLeft->setPosition(xPos - 1600, yPos + 1066);
	backgroundSpriteTopRight->setPosition(xPos + 1600, yPos + 1066);
	backgroundSpriteBottom->setPosition(xPos, yPos - 1066);
	backgroundSpriteBottomLeft->setPosition(xPos - 1600, yPos - 1066);
	backgroundSpriteBottomRight->setPosition(xPos + 1600, yPos - 1066);
	backgroundSpriteLeft->setPosition(xPos - 1600, yPos);
	backgroundSpriteRight->setPosition(xPos + 1600, yPos);

	//physics body
	//background top
	auto bgTopBody = PhysicsBody::createBox(backgroundSpriteTop->getContentSize());
	bgTopBody->setDynamic(false);
	bgTopBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteTop->setPhysicsBody(bgTopBody);

	//background top left
	auto bgTopLeftBody = PhysicsBody::createBox(backgroundSpriteTopLeft->getContentSize());
	bgTopLeftBody->setDynamic(false);
	bgTopLeftBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteTopLeft->setPhysicsBody(bgTopLeftBody);

	//background top right
	auto bgTopRightBody = PhysicsBody::createBox(backgroundSpriteTopRight->getContentSize());
	bgTopRightBody->setDynamic(false);
	bgTopRightBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteTopRight->setPhysicsBody(bgTopRightBody);

	//background bottom
	auto bgBtmBody = PhysicsBody::createBox(backgroundSpriteBottom->getContentSize());
	bgBtmBody->setDynamic(false);
	bgBtmBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteBottom->setPhysicsBody(bgBtmBody);

	//background bottom left
	auto bgBtmLeftBody = PhysicsBody::createBox(backgroundSpriteBottomLeft->getContentSize());
	bgBtmLeftBody->setDynamic(false);
	bgBtmLeftBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteBottomLeft->setPhysicsBody(bgBtmLeftBody);

	//background bottom right
	auto bgBtmRightBody = PhysicsBody::createBox(backgroundSpriteBottomRight->getContentSize());
	bgBtmRightBody->setDynamic(false);
	bgBtmRightBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteBottomRight->setPhysicsBody(bgBtmRightBody);

	//background left
	auto bgLeftBody = PhysicsBody::createBox(backgroundSpriteLeft->getContentSize());
	bgLeftBody->setDynamic(false);
	bgLeftBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteLeft->setPhysicsBody(bgLeftBody);

	//background right
	auto bgRightBody = PhysicsBody::createBox(backgroundSpriteRight->getContentSize());
	bgRightBody->setDynamic(false);
	bgRightBody->setContactTestBitmask(0xFFFFFFFF);
	backgroundSpriteRight->setPhysicsBody(bgRightBody);
}

void Rendering::setBackgroundSprite(string filename)
{
	this->backgroundSprite = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSprite()
{
	return backgroundSprite;
}

void Rendering::setBackgroundSpriteTop(string filename)
{
	this->backgroundSpriteTop = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteTop()
{
	return backgroundSpriteTop;
}

void Rendering::setBackgroundSpriteTopLeft(string filename)
{
	this->backgroundSpriteTopLeft = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteTopLeft()
{
	return backgroundSpriteTopLeft;
}

void Rendering::setBackgroundSpriteTopRight(string filename)
{
	this->backgroundSpriteTopRight = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteTopRight()
{
	return backgroundSpriteTopRight;
}

void Rendering::setBackgroundSpriteBottom(string filename)
{
	this->backgroundSpriteBottom = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteBottom()
{
	return backgroundSpriteBottom;
}

void Rendering::setBackgroundSpriteBottomLeft(string filename)
{
	this->backgroundSpriteBottomLeft = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteBottomLeft()
{
	return backgroundSpriteBottomLeft;
}

void Rendering::setBackgroundSpriteBottomRight(string filename)
{
	this->backgroundSpriteBottomRight = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteBottomRight()
{
	return backgroundSpriteBottomRight;
}

void Rendering::setBackgroundSpriteLeft(string filename)
{
	this->backgroundSpriteLeft = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteLeft()
{
	return backgroundSpriteLeft;
}

void Rendering::setBackgroundSpriteRight(string filename)
{
	this->backgroundSpriteRight = Sprite::create(filename);
}

Sprite* Rendering::getBackgroundSpriteRight()
{
	return backgroundSpriteRight;
}