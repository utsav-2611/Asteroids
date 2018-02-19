#pragma once
#include "cocos2d.h"
#include "GamePlay.h"
#include "GameMacros.h"


USING_NS_CC;

class planeC :public GamePlayer {
public:
	planeC();
	static planeC* create();
};