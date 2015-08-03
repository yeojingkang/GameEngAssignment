#pragma once
#ifndef __RENDERING_H__
#define __RENDERING_H__

#include <iostream>
#include "cocos2d.h"
#include <string>

using namespace std;
using namespace cocos2d;

class Rendering
{
private:
	Sprite* backgroundSprite;
	Sprite* backgroundSpriteTop;
	Sprite* backgroundSpriteTopLeft;
	Sprite* backgroundSpriteTopRight;
	Sprite* backgroundSpriteBottom;
	Sprite* backgroundSpriteBottomLeft;
	Sprite* backgroundSpriteBottomRight;
	Sprite* backgroundSpriteLeft;
	Sprite* backgroundSpriteRight;

	float xPos;
	float yPos;

public:
	Rendering();
	~Rendering();

	void Init(); 
	void setBackgroundSprite(string filename);
	Sprite* getBackgroundSprite();

	void setBackgroundSpriteTop(string filename);
	Sprite* getBackgroundSpriteTop();

	void setBackgroundSpriteTopRight(string filename);
	Sprite* getBackgroundSpriteTopRight();

	void setBackgroundSpriteTopLeft(string filename);
	Sprite* getBackgroundSpriteTopLeft();

	void setBackgroundSpriteBottom(string filename);
	Sprite* getBackgroundSpriteBottom();

	void setBackgroundSpriteBottomRight(string filename);
	Sprite* getBackgroundSpriteBottomRight();

	void setBackgroundSpriteBottomLeft(string filename);
	Sprite* getBackgroundSpriteBottomLeft();

	void setBackgroundSpriteLeft(string filename);
	Sprite* getBackgroundSpriteLeft();

	void setBackgroundSpriteRight(string filename);
	Sprite* getBackgroundSpriteRight();
};

#endif