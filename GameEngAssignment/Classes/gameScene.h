#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
<<<<<<< HEAD
#include "Player.h"
=======
#include "Enemy.h"

using namespace std;
>>>>>>> origin/master

class GameWorld : public cocos2d::Layer
{
private:
	CPlayer *player;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
<<<<<<< HEAD
	
	virtual void update(float dt);

	//handler for keyboard events
	void keyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
	void keyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event *event);

	//handler for mouse events
	void mouseDown(cocos2d::Event *event);
	void mouseUp(cocos2d::Event *event);
	void mouseMove(cocos2d::Event *event);
	void mouseScroll(cocos2d::Event *event);

=======
	virtual void update(float);
    
>>>>>>> origin/master
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(GameWorld);

private:
	vector<CEnemy*> theEnemies;
};

#endif // __GAME_SCENE_H__
