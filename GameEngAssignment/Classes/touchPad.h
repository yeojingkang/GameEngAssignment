#ifndef __TOUCHPAD_H__
#define __TOUCHPAD_H__

#include "cocos2d.h"
#include <string>

#if defined(CC_TARGET_OS_IPHONE)
	#include "UIImageView.h"
#else
	#include"ui\UIImageView.h" 
#endif

using namespace cocos2d;
using namespace std;
using namespace ui;

class CTouchPad
{
public:

	CTouchPad();
	~CTouchPad();

	void Init();
	void SetSprite(string filename);
	ImageView* GetSprite();

	void SetBaseSprite(string filename);
	ImageView* GetBaseSprite();

	void SetOriginalPos(Vec2);
	Vec2 GetOriginalPos();

	void SetTouch(Touch*);
	Touch* GetTouch();

	void SetActive(bool);
	bool GetActive();

	Vec2 GetDirectionVector();

	void Update(Vec2 pos, float dt);

private:
	
	ImageView* touchPadSprite;
	ImageView* baseSprite;

	float xPos;
	float yPos;

	Vec2 originalPos;

	float maxDist;

	Touch* touch;

	bool active;

	Vec2 directionVector;
};

#endif // __TOUCHPAD_H__