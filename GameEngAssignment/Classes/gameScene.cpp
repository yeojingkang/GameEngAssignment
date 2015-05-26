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

	srand(time(NULL));

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameWorld::keyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameWorld::keyReleased, this);

	auto mouseListener = EventListenerMouse::create();
	mouseListener->onMouseDown = CC_CALLBACK_1(GameWorld::mouseDown, this);
	mouseListener->onMouseUp = CC_CALLBACK_1(GameWorld::mouseUp, this);
	mouseListener->onMouseMove = CC_CALLBACK_1(GameWorld::mouseMove, this);
	mouseListener->onMouseScroll = CC_CALLBACK_1(GameWorld::mouseScroll, this);
	
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

	player = new CPlayer();
	player->Init();

	this->addChild(player->getPlayerSprite());
	//Create enemies
	CEnemy* newEnemy;
	for (int i = 0; i < 5; ++i){
		newEnemy = new CEnemy();
		newEnemy->Init(player->getPlayerSprite()->getPosition());
		this->addChild(newEnemy->getSprite(), 0);

		theEnemies.push_back(newEnemy);
	}

	//Create text
	waveNum = CCLabelTTF::create("Hello World", "Helvetica", 12, CCSizeMake(245, 32), kCCTextAlignmentCenter);

	this->scheduleUpdate();

    return true;
}

void GameWorld::keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_W)
	{
		player->MoveUpDown(true, 200);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
	{
		player->MoveUpDown(false, 200);
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_A)
	{
		player->MoveLeftRight(true, 200);
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
	{
		player->MoveLeftRight(false, 200);
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
	EventMouse* e = (EventMouse*)event;

	auto mousePosX = e->getLocationInView().x;
	auto mousePosY = Director::getInstance()->getWinSize().height + e->getLocationInView().y;

	auto test = new CPlayer();
	test->Init();
	test->getPlayerSprite()->setPosition(mousePosX, mousePosY);
	this->addChild(test->getPlayerSprite());
}

void GameWorld::mouseUp(Event *event)
{
}

void GameWorld::mouseMove(Event *event)
{
	EventMouse* e = (EventMouse*)event;

	Vec2 MousePos = Vec2(e->getLocationInView().x, Director::getInstance()->getWinSize().height + e->getLocationInView().y);

	float angleToRot = atan2(MousePos.y - player->getPlayerSprite()->getPositionY(), MousePos.x - player->getPlayerSprite()->getPositionX());
	angleToRot = -angleToRot * (180 / 3.14159);

	if (angleToRot < 0)
	{
		angleToRot = 360 - (-angleToRot);
	}

	player->getPlayerSprite()->setRotation(angleToRot);
}

void GameWorld::mouseScroll(Event *event)
{
}

void GameWorld::update(float dt)
{
	player->update(dt);

	//update the enemies
	for (vector<CEnemy*>::iterator itr = theEnemies.begin(); itr != theEnemies.end(); ++itr){
		(*itr)->Update(dt, player->getPlayerSprite()->getPosition());
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
