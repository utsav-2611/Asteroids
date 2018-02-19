#pragma once
#include "cocos2d.h"
//#include "Enemies.h"
#include <stdlib.h>
#include <unordered_map>
#include <list>
#include "GameSingleton.h"
#include "Bullets.h"

#define PI 0.0174532925
//#include "Collision.h"

USING_NS_CC;

using namespace std;

class GamePlayer:public CCSprite
{
protected:
	int m_bulletPower;
	int m_health;
	int m_speed;
	std::string planeName;

public:
	Vector<Bullets*> playerBullets;
	GamePlayer(void);
	~GamePlayer(void);
	bool initPlayer();
	static GamePlayer* create(int);
	void update(float) override;
	virtual void reduceHealthBy(int);
	int getHealth();
	int getSpeed();
	virtual void fire();
	virtual void destroy();
	int a;
};


