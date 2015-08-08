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

#include "HUD.h"
#include "Weapon.h"
#include "GameOverScene.h"
#include <fstream>
#include <stdio.h>

#include "SimpleAudioEngine.h"

using namespace std;

class GameWorld : public cocos2d::Layer
{
private:
	
	Rendering *background;
	vector<CEnemy*> theEnemies;

	vector<CBullet*> theBullets;

	vector<CEnemyType> theTypes;
	vector<CWave*> theWaves;
	unsigned int currWaveNum;
	float waveChangeTimer;

	CPlayer *player;
	void createEnemyTypes();
	void createWaves();
	
	CWeapon *theWeapon;
public:

	Rendering *r;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	//go to game over scene
	void GoToGameOverScene(cocos2d::Ref *pSender);

	virtual void update(float);

	int getNumberOfActiveMonsters();
	int getWaveNum(){ return currWaveNum; }
	float getWaveChangeTimer(){ return waveChangeTimer; }

	void createNewType(string, int, int, float, cocos2d::Color3B);
	void createNewType(CEnemyType);

	int getEnemyTypeIndex(string name);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
	CREATE_FUNC(GameWorld);
};

#endif // __GAME_SCENE_H__
