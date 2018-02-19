#pragma once
#include "cocos2d.h"
#include "LevelTransitionScene.h"

USING_NS_CC;
using namespace std;

class GameOverScene : public CCScene
{
private:
	std::string m_score;
public:
	bool init();
	void runThisTest(int);
	void menuCallback(Ref*);
};
