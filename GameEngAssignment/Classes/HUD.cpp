#include "HUD.h"

CHUD::CHUD(){}
CHUD::~CHUD(){}

CHUD* CHUD::createLayer(const string& message)
{
	CHUD* h = new CHUD();
	h->create();
	h->setColor(cocos2d::Color3B(0, 0, 0));

	h->setContentSize(cocos2d::Size::Size(1, 1));
	h->setAnchorPoint(cocos2d::Vec2(0, 0));

	h->initOptions(message);

	return h;
}

void CHUD::initOptions(const string& message)
{
	messageLabel = LabelBMFont::create(message.c_str(), "font/Arial.fnt");
	messageLabel->setColor(Color3B(255, 215, 0));

	addChild(messageLabel, 1);

	messageLabel->setPosition(cocos2d::Vec2(Director::getInstance()->getVisibleSize().width,
		Director::getInstance()->getVisibleSize().height));

}

void CHUD::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
}