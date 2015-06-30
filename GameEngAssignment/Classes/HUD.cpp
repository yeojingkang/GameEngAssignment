#include "HUD.h"

CHUD::CHUD(){}
CHUD::~CHUD(){}

CHUD* CHUD::createLayer()
{
	CHUD* h = new CHUD();
	h->create();
	h->setColor(cocos2d::Color3B(0, 0, 0));

	h->setContentSize(cocos2d::Size::Size(1, 1));
	h->setAnchorPoint(cocos2d::Vec2(0, 0));


	return h;
}

void CHUD::initOptions()
{

}

void CHUD::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
}