#pragma once
#include "cocos2d.h"
#include "GamePlayScene.h"
#include "GameSingleton.h"

USING_NS_CC;
using namespace std;

class LevelTransitionScene : public CCScene
{
private:
	std::string levelString;
	int m_level;
	Label* plabel;
	int m_lives;
	int m_score;
public:
	LevelTransitionScene();
	bool init();
	void setLevel(int);
	void runThisTest(int,int,int);
};
