#include "enemyHandler.h"
#pragma once

enemyHandler::enemyHandler()
{
	m_numberOfEnemies = 0;
	m_numberOfDesiredEnemies = 0;
	/*imageEnemies[0] = "plane1_new.png";
	imageEnemies[1] = "plane3_new.png";
	imageEnemies[2] = "plane4_new.png";*/
}

enemyHandler::~enemyHandler()
{
}

bool enemyHandler::init()
{
	return false;
}

void enemyHandler::update()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	if (m_numberOfEnemies < m_numberOfDesiredEnemies) {
		//int imageIndex = rand() % 3;
		Enemies* newEnemy = Enemies::create("plane5_new.png",ENEMY_HEALTH);
		enemies.pushBack(newEnemy);
		newEnemy->setTag(11);
		newEnemy->init();
		CCDirector::sharedDirector()->getRunningScene()->addChild(newEnemy);
		m_numberOfEnemies++;
	}
}
void enemyHandler::reduceEnemies() {
	m_numberOfEnemies--;
}

void enemyHandler::setNumberOfEnemies(int l)
{
	m_numberOfDesiredEnemies = l;
}
