#include "touchPad.h"

USING_NS_CC;

CTouchPad::CTouchPad()
{
	xPos = 0;
	yPos = 0;
	maxDist = 0;
	touch = NULL;
}

void CTouchPad::Init()
{
	SetSprite("touchPad.png");
	SetBaseSprite("touchPadBase.png");
	xPos = 0;
	yPos = 0;
	maxDist = 10;
	touchPadSprite->setPosition(Vec2(xPos, yPos));
	baseSprite->setPosition(Vec2(xPos, yPos));
	originalPos = touchPadSprite->getPosition();
	touch = NULL;
}

void CTouchPad::SetSprite(string filename)
{
	this->touchPadSprite = ImageView::create(filename);
}

ImageView* CTouchPad::GetSprite()
{
	return this->touchPadSprite;
}

void CTouchPad::SetBaseSprite(string filename)
{
	this->baseSprite = ImageView::create(filename);
}

ImageView* CTouchPad::GetBaseSprite()
{
	return this->baseSprite;
}

void CTouchPad::SetOriginalPos(Vec2 v)
{
	this->originalPos = v;
}

Vec2 CTouchPad::GetOriginalPos()
{
	return this->originalPos;
}

void CTouchPad::SetTouch(Touch* touch)
{
	this->touch = touch;
}

Touch* CTouchPad::GetTouch()
{
	return this->touch;
}

void CTouchPad::Update(float dt)
{
	/*if ((this->touchPadSprite->getPosition() - this->baseSprite->getPosition()).length() > this->baseSprite->getBoundingBox().getMaxX())
	{
	}*/
}