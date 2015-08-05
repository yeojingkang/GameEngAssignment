#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"
#include "gameScene.h"
#include "SimpleAudioEngine.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class GameOver : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	//handler for multi touch events
	void touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

	void GoToGameScene(cocos2d::Ref *pSender);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameOver);
};

#endif // __MAINMENU_SCENE_H__
