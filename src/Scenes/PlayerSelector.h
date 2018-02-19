#pragma once
#include "cocos2d.h"
#include "LevelTransitionScene.h"
#include "GameSingleton.h"

USING_NS_CC;
using namespace std;

class PlayerSelectorScene : public CCScene
{
private:
	int shooterIndex;
public:
	void runThisTest(int);
	bool init();
	void nextCallBack(Ref*);
	void previousCallBack(Ref*);
	void playCallBack(Ref*);
};
