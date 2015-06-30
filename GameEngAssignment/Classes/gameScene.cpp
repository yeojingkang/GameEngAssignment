#include "gameScene.h"

USING_NS_CC;

Scene* GameWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//r = new Rendering();
	//r->Init(1, 1);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//this->addChild(r->getSprite(), 1);

	//srand(time(NULL));

	//keyboard listener
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameWorld::keyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameWorld::keyReleased, this);

	//mouse listener
	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameWorld::mouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(GameWorld::mouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(GameWorld::mouseMove, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(GameWorld::mouseScroll, this);
	
	////touch listener
	//auto touchListener = EventListenerTouchOneByOne::create();
	//touchListener->onTouchBegan = CC_CALLBACK_2(GameWorld::touchBegan, this);
	//touchListener->onTouchEnded = CC_CALLBACK_2(GameWorld::touchEnded, this);
	//touchListener->onTouchMoved = CC_CALLBACK_2(GameWorld::touchMoved, this);
	//touchListener->onTouchCancelled = CC_CALLBACK_2(GameWorld::touchCancelled, this);

	//multitouch listener
	auto multiTouchListener = EventListenerTouchAllAtOnce::create();
	multiTouchListener->onTouchesBegan = CC_CALLBACK_2(GameWorld::touchesBegan, this);
	multiTouchListener->onTouchesMoved = CC_CALLBACK_2(GameWorld::touchesMoved, this);
	multiTouchListener->onTouchesEnded = CC_CALLBACK_2(GameWorld::touchesEnded, this);

	//add event listeners with scene graph priority
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(multiTouchListener, this);

	//Create Background
	background = new Rendering();
	background->Init();

	this->addChild(background->getBackgroundSprite());

	//Create Player
	player = new CPlayer();
	player->Init();
	this->addChild(player->getPlayerSprite());

	this->runAction(Follow::create(player->getPlayerSprite()));

	//Create enemies
	//CEnemy* newEnemy;
	//for (int i = 0; i < 5; ++i){
	//	newEnemy = new CEnemy();
	//	newEnemy->Init(player->getPlayerSprite()->getPosition());
	//	this->addChild(newEnemy->getSprite(), 0);

	//	theEnemies.push_back(newEnemy);
	//}

	//Create text
	waveNumLabel = CCLabelTTF::create("Wave 1", "fonts/Marker Felt.ttf", 24);
	waveNumLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - waveNumLabel->getContentSize().height));
	this->addChild(waveNumLabel, 1);
	
	//Create the waves
	createWaves();

	//Create movement touchPad
	movePad = new CTouchPad();
	movePad->Init();
	movePad->GetSprite()->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 4));
	movePad->GetBaseSprite()->setPosition(Vec2(origin.x + visibleSize.width / 5, origin.y + visibleSize.height / 4));
	movePad->SetOriginalPos(movePad->GetBaseSprite()->getPosition());
	this->addChild(movePad->GetBaseSprite(), 0);
	this->addChild(movePad->GetSprite(), 0);

	//Create shooting touchPad
	shootPad = new CTouchPad();
	shootPad->Init();
	shootPad->GetSprite()->setPosition(Vec2(origin.x + 4 * (visibleSize.width / 5), origin.y + visibleSize.height / 4));
	shootPad->GetBaseSprite()->setPosition(Vec2(origin.x + 4 * (visibleSize.width / 5), origin.y + visibleSize.height / 4));
	shootPad->SetOriginalPos(shootPad->GetBaseSprite()->getPosition());
	this->addChild(shootPad->GetBaseSprite(), 0);
	this->addChild(shootPad->GetSprite(), 0);

	//following camera
	this->runAction(Follow::create(player->getPlayerSprite()));

	//create hud
	CHUD* theHUD = CHUD::createLayer();
	//this->addChild(theHUD);

	//scheduling update
	this->scheduleUpdate();

    return true;
}

void GameWorld::keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		player->MoveUpDown(true, player->GetMoveSpeed());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		player->MoveUpDown(false, player->GetMoveSpeed());
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		player->MoveLeftRight(true, player->GetMoveSpeed());
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		player->MoveLeftRight(false, player->GetMoveSpeed());
	}
}

void GameWorld::keyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		player->SetVelocity(player->GetVelocity()->x, 0);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		player->SetVelocity(player->GetVelocity()->x, 0);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		player->SetVelocity(0, player->GetVelocity()->y);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		player->SetVelocity(0, player->GetVelocity()->y);
	}
}

void GameWorld::mouseDown(Event *event)
{
	/*EventMouse* e = (EventMouse*)event;

	auto mousePosX = e->getLocationInView().x;
	auto mousePosY = Director::getInstance()->getWinSize().height + e->getLocationInView().y;

	CBullet* b = new CBullet();
	b->Init();
	float dirX = mousePosX - player->getPlayerSprite()->getPositionX();
	float dirY = mousePosY - player->getPlayerSprite()->getPositionY();

	Vec2* direction = new Vec2(dirX, dirY);
	direction->normalize();
	b->SetMoveVec(direction);
	
	theBullets.push_back(b);
	this->addChild(b->GetSprite(), 0);

	for (vector<CBullet*>::iterator itr = theBullets.begin(); itr != theBullets.end(); ++itr){
		if ((*itr)->GetActive() == false)
		{
			(*itr)->SetActive(true);
			(*itr)->GetSprite()->setRotation(player->getPlayerSprite()->getRotation());
			(*itr)->GetSprite()->setPosition(player->getPlayerSprite()->getPosition());
		}
	}*/
}

void GameWorld::mouseUp(Event *event)
{
}

void GameWorld::mouseMove(Event *event)
{
	/*EventMouse* e = (EventMouse*)event;

	Vec2 MousePos = Vec2(e->getLocationInView().x, Director::getInstance()->getWinSize().height + e->getLocationInView().y);

	float angleToRot = atan2(MousePos.y - player->getPlayerSprite()->getPositionY(), MousePos.x - player->getPlayerSprite()->getPositionX());
	angleToRot = -angleToRot * (180 / 3.14159);

	if (angleToRot < 0)
	{
		angleToRot = 360 - (-angleToRot);
	}

	player->getPlayerSprite()->setRotation(angleToRot);*/
}

void GameWorld::mouseScroll(Event *event)
{
}

//bool GameWorld::touchBegan(Touch* touch, Event* event)
//{
//	cocos2d::log("touch began");
//
//	auto touchPos = touch->getLocation();
//
//	if (movePad->GetSprite()->getBoundingBox().containsPoint(touchPos))
//	{
//		movePad->SetActive(true);
//	}
//
//	if (shootPad->GetSprite()->getBoundingBox().containsPoint(touchPos))
//	{
//		shootPad->SetActive(true);
//	}
//
//	return true;
//}
//
//void GameWorld::touchEnded(Touch* touch, Event* event)
//{
//	cocos2d::log("touch ended");
//
//	auto touchPos = touch->getLocation();
//
//	if (movePad->GetSprite()->getBoundingBox().containsPoint(touchPos))
//	{
//		movePad->SetActive(false);
//		movePad->GetSprite()->setPosition(movePad->GetOriginalPos());
//		player->SetVelocity(0, 0);
//	}
//
//	if (shootPad->GetSprite()->getBoundingBox().containsPoint(touchPos))
//	{
//		shootPad->SetActive(false);
//		shootPad->GetSprite()->setPosition(movePad->GetOriginalPos());
//	}
//}
//
//void GameWorld::touchMoved(Touch* touch, Event* event)
//{
//	cocos2d::log("touch moved");
//
//	auto touchPos = touch->getLocation();
//
//	//moving player based on direction of movement touch pad
//	if (movePad->GetActive() == true)
//	{
//		movePad->GetSprite()->setPosition(touchPos);
//		float moveDirX = movePad->GetSprite()->getPositionX() - movePad->GetOriginalPos().x;
//		float moveDirY = movePad->GetSprite()->getPositionY() - movePad->GetOriginalPos().y;
//
//		Vec2* moveDir = new Vec2(moveDirX, moveDirY);
//		moveDir->normalize();
//		player->SetVelocity(moveDir->x * player->GetMoveSpeed(), moveDir->y * player->GetMoveSpeed());
//	}
//
//	//rotating player based on shooting touch pad
//	if (shootPad->GetActive() == true)
//	{
//		
//	}
//}
//
//void GameWorld::touchCancelled(Touch* touch, Event* event)
//{
//	cocos2d::log("touch cancelled");
//}

void GameWorld::touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
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

void GameWorld::touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
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
		}
	}
}

void GameWorld::touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch moved");

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
				player->SetVelocity(moveDir->x * player->GetMoveSpeed(), moveDir->y * player->GetMoveSpeed());
			}

			if (shootPad->GetTouch() != nullptr && shootPad->GetTouch() == touch)
			{
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
			}
		}
	}
}

void GameWorld::update(float dt)
{
	player->update(dt);

	if (shootPad->GetActive() == true)
	{
		CBullet* b = new CBullet();
		b->Init();

		float shootDirX = shootPad->GetSprite()->getPositionX() - shootPad->GetOriginalPos().x;
		float shootDirY = shootPad->GetSprite()->getPositionY() - shootPad->GetOriginalPos().y;

		Vec2* shootPos = new Vec2(shootDirX, shootDirY);

		Vec2* direction = new Vec2(shootDirX, shootDirY);
		direction->normalize();
		b->SetMoveVec(direction);

		theBullets.push_back(b);
		this->addChild(b->GetSprite(), 0);

		for (vector<CBullet*>::iterator itr = theBullets.begin(); itr != theBullets.end(); ++itr){
			if ((*itr)->GetActive() == false)
			{
				(*itr)->SetActive(true);
				(*itr)->GetSprite()->setRotation(player->getPlayerSprite()->getRotation());
				(*itr)->GetSprite()->setPosition(player->getPlayerSprite()->getPosition());
			}
		}
	}
	//update the enemies
	for (vector<CEnemy*>::iterator itr = theEnemies.begin(); itr != theEnemies.end(); ++itr){
		(*itr)->Update(dt, player->getPlayerSprite()->getPosition());
	}

	for (vector<CBullet*>::iterator itr = theBullets.begin(); itr != theBullets.end(); ++itr){
		if ((*itr)->GetActive() == true)
		{
			(*itr)->Update(dt);
		}	
	}

	//Update the wave
	if (currWaveNum < theWaves.size()){
		if (theWaves[currWaveNum]->getTotalMonsters() <= 0){
			//When wave has finished spawning all enemies
			//Wait for timer before going to next wave
			static float waveChangeTimer = 0.0f;
			waveChangeTimer += dt;

			if (waveChangeTimer > 10.0f && currWaveNum + 1 < theWaves.size()){
				++currWaveNum;
				waveChangeTimer = 0.0f;
				char text[256];
				sprintf(text, "Wave %d", currWaveNum+1);
				waveNumLabel->setString(text);
			}
		}
		else{
			//static float enemySpawnTimer = 0.0f;
			//enemySpawnTimer += dt;

			//if (enemySpawnTimer > 1.0f){
			//	enemySpawnTimer = 0.0f;
			//	//Spawn new enemy
			//	CEnemy *newEnemy = new CEnemy();
			//	newEnemy->Init(player->getPlayerSprite()->getPosition());
			//	this->addChild(newEnemy->getSprite(), 0);
			//	theEnemies.push_back(newEnemy);
			//	theWaves[currWaveNum]->spawnedNormalMonster();
			//}
			if (vector<CEnemy*>* newEnemies = theWaves[currWaveNum]->update(dt, player->getPlayerSprite()->getPosition())){
				//Add enemies to the scene
				for (vector<CEnemy*>::iterator itr = newEnemies->begin(); itr != newEnemies->end(); ++itr){
					this->addChild((*itr)->getSprite(), 0);
				}
				//Add enemies to theEnemies to update them
				theEnemies.insert(theEnemies.end(), newEnemies->begin(), newEnemies->end());
			}
		}
	}
}

void GameWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameWorld::createWaves(){
	ifstream file;
	file.open("waves.txt");

	if (file.is_open()){
		int waveSetNum = 0;
		while (!file.eof()){
			string line;
			getline(file, line);

			if (line.empty()){
				//Line is empty
				waveSetNum = 0;
			}
			else{
				istringstream tmp(line);
				string inputCatcher;//To catch unnecessary inputs

				if (waveSetNum > 0){
					//Currently setting a subwave for any waves
					float activateTime;
					int normalMonsters;

					tmp >> activateTime;
					tmp >> normalMonsters;
					//getline(tmp, inputCatcher, ',');

					//Create subwave
					theWaves[waveSetNum - 1]->setSubwave(activateTime, normalMonsters);
				}
				else{
					//Currently not setting subwave for any waves
					//Get number to set a new wave
					tmp >> waveSetNum;

					//If wave don't exist
					if (waveSetNum > theWaves.size()){
						CWave* newWave = new CWave();
						theWaves.push_back(newWave);
					}
				}
			}
		}
	}

	//Design waves here

	//for (int i = 0; i < 3; ++i){
	//	CWave* newWave = new CWave();

	//	switch (i){
	//	case 0:
	//		newWave->setWave(5);
	//		break;

	//	case 1:
	//		newWave->setWave(10);
	//		break;

	//	case 2:
	//		newWave->setWave(18);
	//		break;

	//	default:
	//		break;
	//	}

	//	theWaves.push_back(newWave);
	//}

	currWaveNum = 0;
}
