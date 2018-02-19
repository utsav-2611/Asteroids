#pragma once
#include "cocos2d.h"
#include "Enemies.h"

USING_NS_CC;
using namespace std;


class enemyHandler {
	int m_numberOfEnemies;
	int m_numberOfDesiredEnemies;

public:
	enemyHandler();
	~enemyHandler();
	bool init();
	void update();
	void reduceEnemies();
	void setNumberOfEnemies(int);
	Vector<Enemies*> enemies;
};