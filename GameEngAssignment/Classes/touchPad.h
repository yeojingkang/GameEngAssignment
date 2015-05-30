#ifndef __TOUCHPAD_H__
#define __TOUCHPAD_H__

#include "cocos2d.h"
#include "ui\UIImageView.h"
#include <string>

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
	
	void SetActive(bool);
	bool GetActive();

	void SetOriginalPos(Vec2);
	Vec2 GetOriginalPos();

	void Update(float dt);

private:
	
	ImageView* touchPadSprite;
	ImageView* baseSprite;

	float xPos;
	float yPos;

	bool active;
	Vec2 originalPos;

	float maxDist;
};

#endif // __TOUCHPAD_H__