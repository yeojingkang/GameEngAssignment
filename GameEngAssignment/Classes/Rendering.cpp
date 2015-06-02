#include "Rendering.h"

USING_NS_CC;

Rendering::Rendering()
{
	xPos = 0;
	yPos = 0;
	backgroundSprite = NULL;

	m_Sprite = NULL;
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

void Rendering::Init(float x, float y)
{
	//initialise new gem type by giving it a sprite
	//m_Sprite = Sprite::create(g_scTextureFileName[newType]);
	m_Sprite = Sprite::create("HelloWorld.png");
	//Render(x, y);
	m_Sprite->setScale(0.5f);
	m_Sprite->setPosition(0.0f, 0.0f);
}

void Rendering::Render(float x, float y)
{
	//calculate and setting position of sprite based on screen's position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float f_posX = (x + 1) * 64;
	float f_posY = visibleSize.height / 2 - (y - 4) * 64 + 32;
	m_Sprite->setPosition(Point(f_posX, f_posY));
}

void Rendering::Update()
{

}