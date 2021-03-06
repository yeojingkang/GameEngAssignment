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

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	for (auto touch : touches)
	{
		if (touch != nullptr)
		{
			auto tap = touch->getLocation();
			if (movePad->GetSprite()->getBoundingBox().containsPoint(tap))
			{
				movePad->SetTouch(touch);
				movePad->SetActive(true);
				player->Movement();
			}
			if (shootPad->GetSprite()->getBoundingBox().containsPoint(tap))
			{
				shootPad->SetTouch(touch);
				shootPad->SetActive(true);
			}

			//if touch is on the changeWeaponLabel
			if (changeWeaponLabel->getBoundingBox().containsPoint(tap))
			{
				//change weapon type				
				if(theWeapon->getInstance()->GetWeaponType() == weaponType::MACHINE_GUN)
				{
					theWeapon->getInstance()->SetWeaponType(weaponType::SHOTGUN);
					changeWeaponLabel->loadTexture("shotgun.png");
				}
				else if (theWeapon->getInstance()->GetWeaponType() == weaponType::SHOTGUN)
				{
					theWeapon->getInstance()->SetWeaponType(weaponType::MACHINE_GUN);
					changeWeaponLabel->loadTexture("machinegun.png");
				}
				changeWeaponLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
					origin.y + visibleSize.height / 3 - changeWeaponLabel->getContentSize().height));
			}

			//if touch is on the pause button
			if (pauseButton->getBoundingBox().containsPoint(tap) && pauseButton->isVisible() == true)
			{
				//pauses the game
				mainMenuButton->setVisible(true);
				continueButton->setVisible(true);
				pauseButton->setVisible(false);
				Director::getInstance()->pause();
			}

			//if touch is on the continue button
			if (continueButton->getBoundingBox().containsPoint(tap) && continueButton->isVisible() == true)
			{
				//un-pauses the game
				Director::getInstance()->resume();
				mainMenuButton->setVisible(false);
				continueButton->setVisible(false);
				pauseButton->setVisible(true);
			}

			//if touch is on the main menu button
			if (mainMenuButton->getBoundingBox().containsPoint(tap) && mainMenuButton->isVisible() == true)
			{
				//goes to main menu scene
				player->setNull();
				Director::getInstance()->resume();
				GoToMainMenuScene(this);
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
			player->stopAllActions();
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

			//moves the player based on the direction gotten from the movement touchPad
			if (movePad->GetTouch() != nullptr && movePad->GetTouch() == touch)
			{
				Point nextPos = tap;
				movePad->GetSprite()->setPosition(tap);

				float moveDirX = movePad->GetSprite()->getPositionX() - movePad->GetOriginalPos().x;
				float moveDirY = movePad->GetSprite()->getPositionY() - movePad->GetOriginalPos().y;

				Vec2* moveDir = new Vec2(moveDirX, moveDirY);
				moveDir->normalize();
				player->SetVelocity(moveDir->x * player->GetMoveSpeed(), moveDir->y * player->GetMoveSpeed());
			}

			//shoots in the direction provided by the shooting touchPad
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

				player->setRotation(angleToRot);
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

	if (gameScene->AllWavesCleared()){
		sprintf(text, "Finished!");
		waveChangeTimerLabel->setString(text);
	}
	else if (gameScene->getWaveChangeTimer() < 10.0f){
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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	messageLabel = LabelTTF::create(message, "fonts/Marker Felt.ttf", 24);

	addChild(messageLabel, 1);

	messageLabel->setPosition(cocos2d::Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height / 2));

	//Create text
	waveNumLabel = LabelTTF::create("Wave 1", "fonts/Marker Felt.ttf", 24);
	waveNumLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height - waveNumLabel->getContentSize().height));

	goldNumLabel = LabelTTF::create("Score: ", "fonts/Marker Felt.ttf", 24);
	goldNumLabel->setPosition(Vec2(20 + goldNumLabel->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4));

	hpNumLabel = LabelTTF::create("HP: ", "fonts/Marker Felt.ttf", 24);
	hpNumLabel->setPosition(Vec2(20 + hpNumLabel->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4 - hpNumLabel->getContentSize().height));
	
	monsterNumLabel = LabelTTF::create("Monsters: ", "fonts/Marker Felt.ttf", 24);
	monsterNumLabel->setPosition(Vec2(20 + monsterNumLabel->getContentSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4 - monsterNumLabel->getContentSize().height * 2));
	
	//create label for switching weapons
	changeWeaponLabel = ImageView::create("machinegun.png");
	changeWeaponLabel->setPosition(Vec2(origin.x + visibleSize.width / 2, 
		origin.y + visibleSize.height / 3 - changeWeaponLabel->getContentSize().height));
	

	//wave change timer label
	waveChangeTimerLabel = LabelTTF::create("", "fonts/Marker Felt.ttf", 48);
	waveChangeTimerLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2,
		Director::getInstance()->getVisibleSize().height * 3 / 4));

	//pause button
	pauseButton = ImageView::create("pauseBtn.png");
	pauseButton->setVisible(true);
	pauseButton->setPosition(Vec2(visibleSize.width - pauseButton->getContentSize().width, 
		visibleSize.height - pauseButton->getContentSize().height
		));

	//continue button
	continueButton = ImageView::create("continueBtn.png");
	continueButton->setVisible(false);
	continueButton->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2));

	//main menu button
	mainMenuButton = ImageView::create("mainMenuBtn.png");
	mainMenuButton->setVisible(false);
	mainMenuButton->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 3));

	this->addChild(waveNumLabel, 1);
	this->addChild(goldNumLabel, 1);
	this->addChild(hpNumLabel, 1);
	this->addChild(monsterNumLabel, 1);
	this->addChild(waveChangeTimerLabel, 1);
	this->addChild(changeWeaponLabel, 1);
	this->addChild(pauseButton, 1);
	this->addChild(continueButton, 1);
	this->addChild(mainMenuButton, 1);

}

void CHUD::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated)
{
}

void CHUD::GoToMainMenuScene(Ref* pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}