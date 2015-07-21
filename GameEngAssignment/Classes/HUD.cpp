#include "HUD.h"
#include "gameScene.h"

USING_NS_CC;

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

bool CHUD::init()
{
	//super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//multitouch listener
	auto multiTouchListener = EventListenerTouchAllAtOnce::create();
	multiTouchListener->onTouchesBegan = CC_CALLBACK_2(CHUD::touchesBegan, this);
	multiTouchListener->onTouchesMoved = CC_CALLBACK_2(CHUD::touchesMoved, this);
	multiTouchListener->onTouchesEnded = CC_CALLBACK_2(CHUD::touchesEnded, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(multiTouchListener, this);

	player = CPlayer::getInstance();
	theWeapon = CWeapon::getInstance();

	//movement touchpad
	movePad = new CTouchPad();
	movePad->Init();
	movePad->GetSprite()->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 4));
	movePad->GetBaseSprite()->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 4));
	movePad->SetOriginalPos(movePad->GetBaseSprite()->getPosition());
	this->addChild(movePad->GetBaseSprite(), 0);
	this->addChild(movePad->GetSprite(), 0);

	//shooting touchpad
	shootPad = new CTouchPad();
	shootPad->Init();
	shootPad->GetSprite()->setPosition(Vec2(origin.x + 4 * (visibleSize.width / 5), origin.y + visibleSize.height / 4));
	shootPad->GetBaseSprite()->setPosition(Vec2(origin.x + 4 * (visibleSize.width / 5), origin.y + visibleSize.height / 4));
	shootPad->SetOriginalPos(shootPad->GetBaseSprite()->getPosition());
	this->addChild(shootPad->GetBaseSprite(), 0);
	this->addChild(shootPad->GetSprite(), 0);

	//scheduling update
	this->scheduleUpdate();

	return true;
}

void CHUD::touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch began");

	for (auto touch : touches)
	{
		if (touch != nullptr)
		{
			auto tap = touch->getLocation();
			if (movePad->GetSprite()->getBoundingBox().containsPoint(tap))
			{
				movePad->SetTouch(touch);
				movePad->SetActive(true);
			}
			if (shootPad->GetSprite()->getBoundingBox().containsPoint(tap))
			{
				shootPad->SetTouch(touch);
				shootPad->SetActive(true);
			}
		}
	}
}

void CHUD::touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch ended");
	for (auto touch : touches)
	{
		if (movePad->GetTouch() != nullptr && movePad->GetTouch() == touch)
		{
			movePad->SetTouch(nullptr);
			movePad->GetSprite()->setPosition(movePad->GetOriginalPos());
			player->SetVelocity(0, 0);
			movePad->SetActive(false);
		}
		if (shootPad->GetTouch() != nullptr && shootPad->GetTouch() == touch)
		{
			shootPad->SetTouch(nullptr);
			shootPad->GetSprite()->setPosition(shootPad->GetOriginalPos());
			shootPad->SetActive(false);

			//set weapon to false
			theWeapon->SetActive(false);
		}
	}
}

void CHUD::touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("Multitouch Moved Began");

	for (auto touch : touches)
	{
		if (touch != nullptr)
		{
			auto tap = touch->getLocation();

			if (movePad->GetTouch() != nullptr && movePad->GetTouch() == touch)
			{
				Point nextPos = tap;
				movePad->GetSprite()->setPosition(tap);

				float moveDirX = movePad->GetSprite()->getPositionX() - movePad->GetOriginalPos().x;
				float moveDirY = movePad->GetSprite()->getPositionY() - movePad->GetOriginalPos().y;

				Vec2* moveDir = new Vec2(moveDirX, moveDirY);
				moveDir->normalize();
				player->SetVelocity(moveDir->x * CPlayer::getInstance()->GetMoveSpeed(), moveDir->y * CPlayer::getInstance()->GetMoveSpeed());
			}

			if (shootPad->GetTouch() != nullptr && shootPad->GetTouch() == touch)
			{

				//sets weapon to active
				theWeapon->SetActive(true);

				Point nextPos = tap;
				shootPad->GetSprite()->setPosition(tap);

				float shootDirX = shootPad->GetSprite()->getPositionX() - shootPad->GetOriginalPos().x;
				float shootDirY = shootPad->GetSprite()->getPositionY() - shootPad->GetOriginalPos().y;

				Vec2* shootPos = new Vec2(shootDirX, shootDirY);

				float angleToRot = atan2(shootPos->y, shootPos->x);
				angleToRot = -angleToRot * (180 / 3.14159);

				if (angleToRot < 0)
				{
					angleToRot = 360 - (-angleToRot);
				}

				player->getPlayerSprite()->setRotation(angleToRot);
				player->SetShootVec(shootPos);
			}
		}
	}
}

void CHUD::update(float dt)
{
	GameWorld* gameScene = (GameWorld*)(this->getParent()->getChildByName("GameScene"));

	//Update text
	char text[256];
	sprintf(text, "Gold: %d", player->GetGold());
	goldNumLabel->setString(text);
	sprintf(text, "HP: %d", player->GetHP());
	hpNumLabel->setString(text);
	sprintf(text, "Monsters: %d", gameScene->getNumberOfActiveMonsters());
	monsterNumLabel->setString(text);
	sprintf(text, "Wave %d", gameScene->getWaveNum() + 1);
	waveNumLabel->setString(text);

	if (gameScene->getWaveChangeTimer() < 10.0f){
		sprintf(text, "Next wave start in: %i", (int)gameScene->getWaveChangeTimer());
		waveChangeTimerLabel->setString(text);
	}
	else
		waveChangeTimerLabel->setString("");

}

void CHUD::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CHUD::initOptions(const string& message)
{
	messageLabel = LabelTTF::create(message, "fonts/Marker Felt.ttf", 24);

	addChild(messageLabel, 1);

	messageLabel->setPosition(cocos2d::Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2));

	//Create text
	waveNumLabel = CCLabelTTF::create("Wave 1", "fonts/Marker Felt.ttf", 24);
	waveNumLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height - waveNumLabel->getContentSize().height));

	goldNumLabel = CCLabelTTF::create("Gold: ", "fonts/Marker Felt.ttf", 24);
	goldNumLabel->setPosition(Vec2(20 + goldNumLabel->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4));

	hpNumLabel = CCLabelTTF::create("HP: ", "fonts/Marker Felt.ttf", 24);
	hpNumLabel->setPosition(Vec2(20 + hpNumLabel->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4 - hpNumLabel->getContentSize().height));
	
	monsterNumLabel = CCLabelTTF::create("Monsters: ", "fonts/Marker Felt.ttf", 24);
	monsterNumLabel->setPosition(Vec2(20 + monsterNumLabel->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4 - monsterNumLabel->getContentSize().height * 2));
	
	waveChangeTimerLabel = CCLabelTTF::create("", "fonts/Marker Felt.ttf", 48);
	waveChangeTimerLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4));

	this->addChild(waveNumLabel, 1);
	this->addChild(goldNumLabel, 1);
	this->addChild(hpNumLabel, 1);
	this->addChild(monsterNumLabel, 1);
	this->addChild(waveChangeTimerLabel, 1);

}

void CHUD::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
}