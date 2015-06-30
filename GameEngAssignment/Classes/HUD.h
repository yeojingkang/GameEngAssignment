#ifndef __HUD_H__
#define __HUD_H__

#include "cocos2d.h"
#include <string>

using namespace cocos2d;
using namespace std;

class CHUD : public cocos2d::LayerColor
{
public:
	CHUD();
	~CHUD();

	static CHUD* createLayer();
	void initOptions();

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4 &transform, bool transformUpdated);

	CREATE_FUNC(CHUD);
private:
};

#endif // __HUD_H__