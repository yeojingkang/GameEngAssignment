#include "MainMenuScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	//multitouch listener
	auto multiTouchListener = EventListenerTouchAllAtOnce::create();
	multiTouchListener->onTouchesBegan = CC_CALLBACK_2(MainMenu::touchesBegan, this);
	multiTouchListener->onTouchesMoved = CC_CALLBACK_2(MainMenu::touchesMoved, this);
	multiTouchListener->onTouchesEnded = CC_CALLBACK_2(MainMenu::touchesEnded, this);

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
										   CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + visibleSize.height / 2 - closeItem->getContentSize().height));

	//start
	auto startItem = MenuItemImage::create(
		"StartNormal.png",
		"StartSelected.png",
		CC_CALLBACK_1(MainMenu::GoToGameScene, this));

	startItem->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 + closeItem->getContentSize().height));

	// create menu, it's an autorelease object
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

    // create menu, it's an autorelease object
    auto menu2 = Menu::create(closeItem, NULL);
	menu2->setPosition(Vec2::ZERO);
	this->addChild(menu2, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Main Menu", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

	//play main menu bgm
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();

	// set the background music and continuously play it.
	audio->playBackgroundMusic("MainMenu.mp3", false);

    return true;
}

void MainMenu::menuCloseCallback(Ref* pSender)
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

void MainMenu::touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
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

void MainMenu::touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
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

void MainMenu::touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event)
{
	log("multitouch ended");
	for (auto touch : touches)
	{
		//ends touch
	}
}

void MainMenu::GoToGameScene(Ref* pSender)
{
	auto scene = GameWorld::createScene();
	Director::getInstance()->replaceScene(scene);
}