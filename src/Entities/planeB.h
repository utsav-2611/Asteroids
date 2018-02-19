#pragma once
#include "cocos2d.h"
#include "GamePlay.h"
#include "GameMacros.h"

USING_NS_CC;

class planeB :public GamePlayer {
public:
	planeB();
	static planeB* create();
};