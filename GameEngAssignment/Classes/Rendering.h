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

	float xPos;
	float yPos;

public:
	Rendering();
	~Rendering();

	void Init(); 
	void setBackgroundSprite(string filename);
	Sprite* getBackgroundSprite();

};

#endif