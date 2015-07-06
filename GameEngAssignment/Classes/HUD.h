#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include <string>

#include "ui\UIImageView.h"

using namespace cocos2d;
using namespace std;
using namespace ui;

class CHUD : public cocos2d::LayerColor
{
public:
	CHUD();
	~CHUD();

	CHUD* createLayer(const string& message);
	void initOptions(const string& message);

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated);

	CREATE_FUNC(CHUD);
private:
	LabelBMFont* messageLabel;
};

#endif // __HUD_H__