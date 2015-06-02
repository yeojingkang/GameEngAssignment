#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Rendering.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Rendering.h"

#include "Wave.h"
#include "touchPad.h"

using namespace std;

class GameWorld : public cocos2d::Layer
{
private:
	CPlayer *player;
	Rendering *background;
	vector<CEnemy*> theEnemies;

	vector<CBullet*> theBullets;
	CCLabelTTF* waveNum;

	vector<CWave*> theWaves;
	int currWaveNum;

	CCLabelTTF* waveNumLabel;

	void createWaves();
	
	CTouchPad* movePad = new CTouchPad();
	CTouchPad* shootPad = new CTouchPad();


public:

	Rendering *r;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//handler for keyboard events
	void keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//handler for mouse events
	void mouseDown(cocos2d::Event *event);
	void mouseUp(cocos2d::Event *event);
	void mouseMove(cocos2d::Event *event);
	void mouseScroll(cocos2d::Event *event);

	//handler for touch events
	bool touchBegan(cocos2d::Touch*, cocos2d::Event*);
	void touchEnded(cocos2d::Touch*, cocos2d::Event*);
	void touchMoved(cocos2d::Touch*, cocos2d::Event*);
	void touchCancelled(cocos2d::Touch*, cocos2d::Event*);

	//handler for multi touch events
	void touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

	virtual void update(float);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(GameWorld);
};

#endif // __GAME_SCENE_H__
