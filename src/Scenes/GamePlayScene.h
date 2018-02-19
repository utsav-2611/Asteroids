#pragma once
#include "cocos2d.h"
#include "GamePlay.h"
#include "Bullets.h"
#include "enemyHandler.h"
#include "Collision.h"
//#include "BackgroundController.h"
#include "LevelTransitionScene.h"
#include "GameOverScene.h"
#include "HelloWorldScene.h"
#include"GameSingleton.h"
#include "planeC.h"
#include "planeB.h"
#include "planeA.h"
#include <algorithm>
#include <vector>

#define PI 0.0174532925

USING_NS_CC;
using namespace std;
class GamePlayScene: public CCScene
{
protected:
	std::vector<cocos2d::EventKeyboard::KeyCode> keys;
	enemyHandler* m_handler;
	GamePlayer* m_player;
	CollisionDetector* m_collisionDetector;
	int m_level;
	int m_lives;
	int m_score;
	Label* m_scoreLabel;
	Label* m_healthLabel;
	MenuItemImage* m_pPauseImage;
	MenuItemImage* m_exitImage;
public:
	
	GamePlayScene::GamePlayScene(int,int,int);
	bool isKeyPressed(EventKeyboard::KeyCode);
	//double keyPressedDuration(EventKeyboard::KeyCode);
	bool init();
	enemyHandler* getEnemyHandler();
	virtual void runThisTest(int, int, int);
	
	void update(float);
	void pauseCallBack(Ref*);
	void resumeCallBack(Ref*);
	void exitCallBack(Ref*);
	void initHUD();
	void initGamePlayer();
	void initEventListener();
	void updateScore();
	void updatePositionAndRotation();
	void updateEndWallPosition();
	void updateGameOver();
	void updateCollisionEffects();
};

