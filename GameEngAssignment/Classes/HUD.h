#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include <string>

#include "touchPad.h"
#include "Player.h"
#include "Weapon.h"
#include "MainMenuScene.h"

using namespace cocos2d;
using namespace std;
using namespace ui;

class CHUD : public cocos2d::Layer
{
public:
	CHUD();
	~CHUD();

	static CHUD* createLayer(const string& message);
	void initOptions(const string& message);

	virtual bool init();

	virtual void update(float);

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated);

	//go to main menu scene
	void GoToMainMenuScene(cocos2d::Ref *pSender);

	//function for multitouchListeners
	void touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	//statically create function
	CREATE_FUNC(CHUD);

private:
	LabelTTF* messageLabel;
	ImageView* changeWeaponLabel;
	ImageView* pauseButton;

	ImageView* continueButton;
	ImageView* mainMenuButton;

	cocos2d::LabelTTF* waveNumLabel;
	cocos2d::LabelTTF* goldNumLabel;
	cocos2d::LabelTTF* hpNumLabel;
	cocos2d::LabelTTF* monsterNumLabel;
	cocos2d::LabelTTF* waveChangeTimerLabel;

	CTouchPad* movePad;
	CTouchPad* shootPad;

	CPlayer* player;
	CWeapon* theWeapon;
};

#endif // __HUD_H__