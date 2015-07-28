#include "gameScene.h"

USING_NS_CC;

#define WAVETIME 10.0f

Scene* GameWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = GameWorld::create();
	layer->setName("GameScene");

	//create hud
	CHUD *theHUD = CHUD::createLayer("");
	theHUD->init();

	// add layer as a child to scene
	scene->addChild(layer);

	scene->addChild(theHUD, 2);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
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
	/*auto multiTouchListener = EventListenerTouchAllAtOnce::create();
	multiTouchListener->onTouchesBegan = CC_CALLBACK_2(GameWorld::touchesBegan, this);
	multiTouchListener->onTouchesMoved = CC_CALLBACK_2(GameWorld::touchesMoved, this);
	multiTouchListener->onTouchesEnded = CC_CALLBACK_2(GameWorld::touchesEnded, this);*/

	//add event listeners with scene graph priority
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(multiTouchListener, this);

	//Create Background
	background = new Rendering();
	background->Init();

	this->addChild(background->getBackgroundSprite());

	//Create Player
	player = CPlayer::getInstance();
	player->Init();
	this->addChild(player->getPlayerSprite());

	this->runAction(Follow::create(player->getPlayerSprite()));

	theWeapon = CWeapon::getInstance();
	theWeapon->Init();

	//goldNumLabel->runAction(Follow::create(this));

	//Create the enemy types
	createEnemyTypes();
	//Create the waves
	createWaves();

	//following camera
	this->runAction(Follow::create(player->getPlayerSprite()));

	//listener for onContactBegin
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameWorld::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

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

//void GameWorld::touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
//{
//	log("multitouch began");
//
//	for (auto touch : touches)
//	{
//		if (touch != nullptr)
//		{
//			auto tap = touch->getLocation();
//			if (movePad->GetSprite()->getBoundingBox().containsPoint(tap))
//			{
//				movePad->SetTouch(touch);
//				movePad->SetActive(true);
//			}
//			if (shootPad->GetSprite()->getBoundingBox().containsPoint(tap))
//			{
//				shootPad->SetTouch(touch);
//				shootPad->SetActive(true);
//			}
//		}
//	}
//}
//
//void GameWorld::touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
//{
//	log("multitouch ended");
//	for (auto touch : touches)
//	{
//		if (movePad->GetTouch() != nullptr && movePad->GetTouch() == touch)
//		{
//			movePad->SetTouch(nullptr);
//			movePad->GetSprite()->setPosition(movePad->GetOriginalPos());
//			player->SetVelocity(0, 0);
//			movePad->SetActive(false);
//		}
//		if (shootPad->GetTouch() != nullptr && shootPad->GetTouch() == touch)
//		{
//			shootPad->SetTouch(nullptr);
//			shootPad->GetSprite()->setPosition(shootPad->GetOriginalPos());
//			shootPad->SetActive(false);
//		}
//	}
//}
//
//void GameWorld::touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
//{
//	log("multitouch moved");
//
//	for (auto touch : touches)
//	{
//		if (touch != nullptr)
//		{
//			auto tap = touch->getLocation();
//
//			if (movePad->GetTouch() != nullptr && movePad->GetTouch() == touch)
//			{
//				Point nextPos = tap;
//				movePad->GetSprite()->setPosition(tap);
//
//				float moveDirX = movePad->GetSprite()->getPositionX() - movePad->GetOriginalPos().x;
//				float moveDirY = movePad->GetSprite()->getPositionY() - movePad->GetOriginalPos().y;
//
//				Vec2* moveDir = new Vec2(moveDirX, moveDirY);
//				moveDir->normalize();
//				player->SetVelocity(moveDir->x * player->GetMoveSpeed(), moveDir->y * player->GetMoveSpeed());
//			}
//
//			if (shootPad->GetTouch() != nullptr && shootPad->GetTouch() == touch)
//			{
//				Point nextPos = tap;
//				shootPad->GetSprite()->setPosition(tap);
//
//				float shootDirX = shootPad->GetSprite()->getPositionX() - shootPad->GetOriginalPos().x;
//				float shootDirY = shootPad->GetSprite()->getPositionY() - shootPad->GetOriginalPos().y;
//
//				Vec2* shootPos = new Vec2(shootDirX, shootDirY);
//
//				float angleToRot = atan2(shootPos->y, shootPos->x);
//				angleToRot = -angleToRot * (180 / 3.14159);
//
//				if (angleToRot < 0)
//				{
//					angleToRot = 360 - (-angleToRot);
//				}
//
//				player->getPlayerSprite()->setRotation(angleToRot);
//			}
//		}
//	}
//}

bool GameWorld::onContactBegin(PhysicsContact &contact)
{
	return true;
}

void GameWorld::update(float dt)
{
	player->update(dt);
	theWeapon->update(dt);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//shoot bullet if weapon is true (if user is touching the shootpad)
	if (theWeapon->GetActive() == true)
	{
		if (theWeapon->GetFirerate() <= 0.0f)
		{
			if (theWeapon->GetWeaponType() == weaponType::MACHINE_GUN)
			{
				//adds machine gun type shooting
				theWeapon->SetFirerate(MACHINEGUN_FIRE_RATE);
				CBullet* b = CBullet::create();
				b->setPosition(player->getPlayerSprite()->getPosition());
				b->SetMoveVec(player->GetShootVec());
				b->SetActive(true);
				b->MoveForward();
				theBullets.push_back(b);
				this->addChild(b, 0);
			}
			else if (theWeapon->GetWeaponType() == weaponType::SHOTGUN)
			{
				//adds shotgun type shooting
				theWeapon->SetFirerate(SHOTGUN_FIRE_RATE);

				for (int i = 0; i < 5; ++i)
				{
					CBullet* b = CBullet::create();
					b->setPosition(player->getPlayerSprite()->getPosition());
					b->SetMoveVec(player->GetShootVec());
					b->SetActive(true);
					b->MoveForward();
					theBullets.push_back(b);
					this->addChild(b, 0);
				}
			}
		}
	}

	//Update the bullets
	for (vector<CBullet*>::iterator itr = theBullets.begin(); itr != theBullets.end(); ++itr)
	{
		if ((*itr)->GetActive() == true)
		{
			(*itr)->Update(dt);
		}
	}

	//Cleanup theEnemies
	theEnemies.erase(
		std::remove_if(theEnemies.begin(), theEnemies.end(), [](CEnemy* enemy){return !enemy->getParent(); }),
		theEnemies.end()
		);

	//Update the wave
	if (currWaveNum < theWaves.size()){
		//If there are no more monster to spawn or are alive
		if (theWaves[currWaveNum]->getTotalMonsters() <= 0 && getNumberOfActiveMonsters() <= 0){
			//When wave has finished spawning all enemies
			//Wait for timer before going to next wave
			waveChangeTimer -= dt;

			if (waveChangeTimer <= 0.0f && currWaveNum + 1 < theWaves.size()){
				++currWaveNum;
				waveChangeTimer = WAVETIME;
			}
		}
		else{
			//Get list of monsters to spawn and add them to theEnemies
			vector<int> spawnList = theWaves[currWaveNum]->update(dt, player->getPlayerSprite()->getPosition());

			if (spawnList.size() > 0){
				for (vector<int>::iterator itr = spawnList.begin(); itr != spawnList.end(); ++itr){
					int index = std::distance(spawnList.begin(), itr);

					//If an enemy is being spawned where it's type isn't defined, remove all monsters of that type then break
					if (index + 1 > theTypes.size()){
						theWaves[currWaveNum]->typeNotDefined(index);
						break;
					}

					//Spawn number of enemies for each enemy type
					for (int i = 0; i < spawnList[index]; ++i){

						CEnemy* newEnemy = CEnemy::create();

						newEnemy->Init(newEnemy, player->getPlayerSprite()->getPosition(), theTypes[index], player);
						newEnemy->MoveToPlayer(newEnemy);

						theEnemies.push_back(newEnemy);
						this->addChild(newEnemy, 1);
					}
				}
			}
		}
	}
}

void GameWorld::menuCloseCallback(Ref* pSender)
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

void GameWorld::createEnemyTypes(){
	ifstream file;
	file.open("enemytypes.txt");

	if (file.is_open()){
		string line;
		while (!file.eof()){
			getline(file, line);

			//Line isn't empty
			if (!line.empty()){
				istringstream tmp(line);

				string name;
				unsigned int hp, bounty;
				float speed;
				unsigned int r, g, b;

				getline(tmp, name, ',');
				tmp >> hp;
				tmp.get();
				tmp >> bounty;
				tmp.get();
				tmp >> speed;
				tmp.get();
				tmp >> r;
				tmp.get();
				tmp >> g;
				tmp.get();
				tmp >> b;

				createNewType(name, hp, bounty, speed, cocos2d::Color3B(r, g, b));
			}
		}
	}

	file.close();
}
void GameWorld::createWaves(){
	ifstream file;
	file.open("waves.txt");

	if (file.is_open()){
		int waveSetNum = 0;
		string line;

		while (!file.eof()){
			getline(file, line);

			if (line.empty()){
				//Line is empty
				waveSetNum = 0;
			}
			else{
				istringstream tmp(line);
				char inputCatcher;//To catch unnecessary inputs

				if (waveSetNum > 0){
					//Currently setting a subwave for any waves
					float activateTime;
					int monsterNum;

					tmp >> activateTime;

					//Get number of each enemy type and place into subwave
					vector<int> enemies;
					int enemyCount = 0;
					do{
						tmp >> enemyCount;
						enemies.push_back(enemyCount);
						tmp.get(inputCatcher);
						if (tmp.eof())
							break;
					} while (inputCatcher == ',');

					//Create subwave
					theWaves[waveSetNum - 1]->setSubwave(activateTime, enemies);
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

	file.close();

	currWaveNum = 0;
	waveChangeTimer = WAVETIME;
}

int GameWorld::getNumberOfActiveMonsters(){
	int num = 0;

	for (vector<CEnemy*>::iterator itr = theEnemies.begin(); itr != theEnemies.end(); ++itr){
		if ((*itr)->getParent() != NULL)
			++num;
	}

	return num;
}

void GameWorld::createNewType(string name, int hp, int bounty, float speed, cocos2d::Color3B color){
	//If a new type of enemy is created that has the same name as an existing type, overwrite existing type instead
	for (vector<CEnemyType>::iterator itr = theTypes.begin(); itr != theTypes.end(); ++itr){
		if ((*itr).getName() == name){
			(*itr).Overwrite(hp, bounty, speed, color);
			return;
		}
	}

	CEnemyType newType;
	newType.Init(name, hp, bounty, speed, color);

	theTypes.push_back(newType);
}
void GameWorld::createNewType(CEnemyType newType){
	//If a new type of enemy is created that has the same name as an existing type, overwrite existing type instead
	for (vector<CEnemyType>::iterator itr = theTypes.begin(); itr != theTypes.end(); ++itr){
		if ((*itr).getName() == newType.getName()){
			(*itr).Overwrite(newType.getHP(), newType.getBounty(), newType.getSpeed(), newType.getColor());
			return;
		}
	}

	theTypes.push_back(newType);
}

int GameWorld::getEnemyTypeIndex(string name){
	for (vector<CEnemyType>::iterator itr = theTypes.begin(); itr != theTypes.end(); ++itr){
		if ((*itr).getName() == name)
			return std::distance(theTypes.begin(), itr);
	}

	return -1;
}