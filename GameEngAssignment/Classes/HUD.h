#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include <string>

#include "touchPad.h"
#include "Player.h"

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

	//function for multitouchListeners
	void touchesBegan(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesMoved(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);
	void touchesEnded(const vector<cocos2d::Touch*> &touches, cocos2d::Event *event);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(CHUD);

private:
	LabelTTF* messageLabel;

	CTouchPad* movePad;
	CTouchPad* shootPad;

	CPlayer* player;
};

#endif // __HUD_H__