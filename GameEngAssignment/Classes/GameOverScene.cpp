#include "GameOverScene.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = GameOver::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//multitouch listener
	auto multiTouchListener = EventListenerTouchAllAtOnce::create();
	multiTouchListener->onTouchesBegan = CC_CALLBACK_2(GameOver::touchesBegan, this);
	multiTouchListener->onTouchesMoved = CC_CALLBACK_2(GameOver::touchesMoved, this);
	multiTouchListener->onTouchesEnded = CC_CALLBACK_2(GameOver::touchesEnded, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
	
	//exit
    auto closeItem = MenuItemImage::create(
                                           "ExitNormal.png",
                                           "ExitSelected.png",
										   CC_CALLBACK_1(GameOver::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height / 2 - closeItem->getContentSize().height));

	//play again
	auto startItem = MenuItemImage::create(
		"PlayAgainNormal.png",
		"PlayAgainSelected.png",
		CC_CALLBACK_1(GameOver::GoToGameScene, this));
	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
								origin.y + visibleSize.height / 2 + closeItem->getContentSize().height));

	// create menu, it's an autorelease object
	auto gameover = Menu::create(startItem, NULL);
	gameover->setPosition(Vec2::ZERO);
	this->addChild(gameover, 1);

    // create menu, it's an autorelease object
	auto gameover2 = Menu::create(closeItem, NULL);
	gameover2->setPosition(Vec2::ZERO);
	this->addChild(gameover2, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	//play game over bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	audio->playBackgroundMusic("Sounds/GameOver.mp3", false);

    return true;
}

void GameOver::menuCloseCallback(Ref* pSender)
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

void GameOver::touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch began");

	for (auto touch : touches)
	{
		if (touch != nullptr)
		{
			auto tap = touch->getLocation();
			//insert codes here to check for touch pos
			
		}
	}
}

void GameOver::touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch moved");
	for (auto touch : touches)
	{
		if (touch != nullptr)
		{
			auto tap = touch->getLocation();
			//insert codes here to move objects based on touch pos
		}
	}
}

void GameOver::touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch ended");
	for (auto touch : touches)
	{
		//ends touch
	}
}

void GameOver::GoToGameScene(Ref* pSender)
{
	auto scene = GameWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}