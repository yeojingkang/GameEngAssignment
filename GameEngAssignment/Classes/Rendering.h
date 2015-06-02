#pragma once
#ifndef __RENDERING_H__
#define __RENDERING_H__

#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

//enum gem types
enum E_TEXTURE_IMAGES
{
	E_BLUE,
	E_TOTAL
};

//gem file names to access textures
static const char* const g_scTextureFileName[E_TOTAL] =
{ "Blue.png" };

class Rendering
{
private:
	Sprite* m_Sprite;

public:
	Rendering();
	~Rendering();

	void Init(float x, float y);
	void Render(float x, float y);
	Sprite* getSprite(void)
	{ 
		return m_Sprite; 
	};

	void Update(void);
	void ChangeTexture(E_TEXTURE_IMAGES);
};

#endif