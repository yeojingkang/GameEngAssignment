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

	//Create Background
	background = new Rendering();
	background->Init();

	this->addChild(background->getBackgroundSprite());
	
	//background for seamless stuffs
	this->addChild(background->getBackgroundSpriteTop());
	this->addChild(background->getBackgroundSpriteTopLeft());
	this->addChild(background->getBackgroundSpriteTopRight());
	this->addChild(background->getBackgroundSpriteBottom());
	this->addChild(background->getBackgroundSpriteBottomLeft());
	this->addChild(background->getBackgroundSpriteBottomRight());
	this->addChild(background->getBackgroundSpriteLeft());
	this->addChild(background->getBackgroundSpriteRight());

	//Create Player
	player = CPlayer::getInstance();
	this->addChild(player);

	this->runAction(Follow::create(player));

	theWeapon = CWeapon::getInstance();
	theWeapon->Init();

	//goldNumLabel->runAction(Follow::create(this));

	//Create the enemy types
	createEnemyTypes();
	//Create the waves
	createWaves();

	//listener for onContactBegin
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameWorld::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	//play bgm sound
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	audio->playBackgroundMusic("Game.mp3", true);

	//scheduling update
	this->scheduleUpdate();

	return true;
}

bool GameWorld::onContactBegin(PhysicsContact &contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		if (nodeA->getTag() == PLAYER_TAG && nodeB->getTag() == ENEMY_TAG)
		{
			//player die
			//GoToGameOverScene(this);
			//nodeA->removeFromParentAndCleanup(true);
		}
		else if (nodeB->getTag() == PLAYER_TAG && nodeA->getTag() == ENEMY_TAG)
		{
			//player die
			//GoToGameOverScene(this);
			//nodeB->removeFromParentAndCleanup(true);
		}
	}
	return true;
}

void GameWorld::update(float dt)
{
	theWeapon->update(dt);

	if (player->GetActive() == false)
	{
		GoToGameOverScene(this);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//shoot bullet if weapon is true (if user is touching the shootpad)
	if (theWeapon->GetActive() == true)
	{
		//play machine gun sound
		auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

		if (theWeapon->GetFirerate() <= 0.0f)
		{
			if (theWeapon->GetWeaponType() == weaponType::MACHINE_GUN)
			{
				//adds machine gun type shooting
				theWeapon->SetFirerate(MACHINEGUN_FIRE_RATE);
				CBullet* b = CBullet::create();
				b->setPosition(player->getPosition());
				b->SetMoveVec(player->GetShootVec());
				b->SetActive(true);
				b->MoveForward();
				theBullets.push_back(b);
				this->addChild(b, 0);

				// play a sound effect, just once.
				audio->playEffect("Rifle.mp3", false, 1.0f, 1.0f, 1.0f);
			}
			else if (theWeapon->GetWeaponType() == weaponType::SHOTGUN)
			{
				//adds shotgun type shooting
				theWeapon->SetFirerate(SHOTGUN_FIRE_RATE);

				for (int i = 0; i < 5; ++i)
				{
					CBullet* b = CBullet::create();
					b->setPosition(player->getPosition());
					b->SetMoveVec(player->GetShootVec());
					b->SetActive(true);
					b->MoveForward();
					theBullets.push_back(b);
					this->addChild(b, 0);

					// play a sound effect, just once.
					audio->playEffect("Shotgun.mp3", false, 1.0f, 1.0f, 1.0f);
				}
			}
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
			vector<int> spawnList = theWaves[currWaveNum]->update(dt, player->getPosition());

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

						newEnemy->Init(newEnemy, player->getPosition(), theTypes[index], player);
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
	auto fileUtils = FileUtils::getInstance();
	string fullPath = fileUtils->fullPathForFilename("enemytypes.txt");

	FILE* file;
	file = fopen(fullPath.c_str(), "r");

	if (!file){
		log("file opening failed");
		return;
	}

	char buf[1000];
	while (fgets(buf, 1000, file) != NULL){
		char name[1000];
		unsigned int hp, bounty;
		float speed;
		unsigned int r, g, b;

		sscanf(buf, "%s %u,%u,%f,%u,%u,%u", name, &hp, &bounty, &speed, &r, &g, &b);
		createNewType(name, hp, bounty, speed, cocos2d::Color3B(r, g, b));
	}

	fclose(file);
}
void GameWorld::createWaves(){
	auto fileUtils = FileUtils::getInstance();
	string fullPath = fileUtils->fullPathForFilename("waves.txt");

	FILE* file;
	file = fopen(fullPath.c_str(), "r");

	if (!file){
		log("file opening failed");
		return;
	}

	unsigned int waveSetNum = 0;
	char buf[1000];

	while (!feof(file)){
		if (fgets(buf, 1000, file) != NULL){
			if (waveSetNum > 0){
				//Currently setting a subwave for a wave
				float activateTime;
				vector<int> enemies;
				
				sscanf(buf, "%f", &activateTime);

				char* parameter = strtok(buf, " ,");
				parameter = strtok(NULL, " ,");
				while (parameter != NULL){
					enemies.push_back(atoi(parameter));
					parameter = strtok(NULL, " ,");
				}

				//Create subwave
				theWaves[waveSetNum - 1]->setSubwave(activateTime, enemies);
			}
			else{
				//Currently not setting subwave for any wave
				//Get number to set a new wave
				sscanf(buf, "%u", &waveSetNum);
				if (waveSetNum > theWaves.size()){
					CWave* newWave = new CWave();
					theWaves.push_back(newWave);
				}
			}
		}
		else{
			//Line is empty
			waveSetNum = 0;
		}
	}

	fclose(file);

	//ifstream file;
	//file.open("waves.txt");

	//if (file.is_open()){
	//	int waveSetNum = 0;
	//	string line;

	//	while (!file.eof()){
	//		getline(file, line);

	//		if (line.empty()){
	//			//Line is empty
	//			waveSetNum = 0;
	//		}
	//		else{
	//			istringstream tmp(line);
	//			char inputCatcher;//To catch unnecessary inputs

	//			if (waveSetNum > 0){
	//				//Currently setting a subwave for any waves
	//				float activateTime;
	//				int monsterNum;

	//				tmp >> activateTime;

	//				//Get number of each enemy type and place into subwave
	//				vector<int> enemies;
	//				int enemyCount = 0;
	//				do{
	//					tmp >> enemyCount;
	//					enemies.push_back(enemyCount);
	//					tmp.get(inputCatcher);
	//					if (tmp.eof())
	//						break;
	//				} while (inputCatcher == ',');

	//				//Create subwave
	//				theWaves[waveSetNum - 1]->setSubwave(activateTime, enemies);
	//			}
	//			else{
	//				//Currently not setting subwave for any waves
	//				//Get number to set a new wave
	//				tmp >> waveSetNum;

	//				//If wave don't exist
	//				if (waveSetNum > theWaves.size()){
	//					CWave* newWave = new CWave();
	//					theWaves.push_back(newWave);
	//				}
	//			}
	//		}
	//	}
	//}

	//file.close();

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

void GameWorld::GoToGameOverScene(Ref* pSender)
{
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(scene);
}

int GameWorld::getEnemyTypeIndex(string name){
	for (vector<CEnemyType>::iterator itr = theTypes.begin(); itr != theTypes.end(); ++itr){
		if ((*itr).getName() == name)
			return std::distance(theTypes.begin(), itr);
	}

	return -1;
}