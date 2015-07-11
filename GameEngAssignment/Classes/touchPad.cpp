#include "touchPad.h"

USING_NS_CC;

CTouchPad::CTouchPad()
{
	xPos = 0;
	yPos = 0;
	maxDist = 0;
	touch = NULL;
	active = false;
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
	directionVector.x = 0;
	directionVector.y = 0;
	touch = NULL;
	active = false;
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

void CTouchPad::SetActive(bool active)
{
	this->active = active;
}

bool CTouchPad::GetActive()
{
	return this->active;
}

Vec2 CTouchPad::GetDirectionVector()
{
	return this->directionVector;
}

void CTouchPad::Update(Vec2 pos, float dt)
{
	directionVector = touchPadSprite->getPosition() - baseSprite->getPosition();
}