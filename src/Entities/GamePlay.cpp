#pragma once
#include "GamePlay.h"
#include "AppMacros.h"
using namespace std;

GamePlayer::GamePlayer(void)
{
	Singleton* myInstance = Singleton::getInstance();
	m_bulletPower = myInstance->getPlane(Singleton::get_fighterIndex()).bulletPower;
	m_health = myInstance->getPlane(Singleton::get_fighterIndex()).health;
	m_speed = myInstance->getPlane(Singleton::get_fighterIndex()).speed;
}

GamePlayer::~GamePlayer(void)
{
}
GamePlayer* GamePlayer::create(int fighterIndex)
{
	GamePlayer *pobSprite = new GamePlayer();
	Singleton* myInstance = Singleton::getInstance();
	if (pobSprite && pobSprite->initWithFile(myInstance->getPlane(fighterIndex).name))
	{
		//pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
bool GamePlayer::initPlayer() {
	
	return true;
}
void GamePlayer::update(float dt)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	auto position =this->getPosition();
	if (position.x  > origin.x+visibleSize.width)
		position.x =0;
	else if(position.x < 0 )
		position.x = origin.x+visibleSize.width;
	else if(position.y > origin.y + visibleSize.height)
		position.y=0;
	else if(position.y < 0)
		position.y = origin.y + visibleSize.height;
	this->setPosition(position);
}

void GamePlayer::reduceHealthBy(int hittingBulletPower)
{
	m_health -= hittingBulletPower;
	if (m_health <= 0)
		this->destroy();
	else {
		
		CCAction* myShakeAnimation = Sequence::create(
			MoveBy::create(0.1, ccp(5, 0)),
			MoveBy::create(0.1, ccp(0, -5)),
			MoveBy::create(0.1, ccp(0, 5)),
			MoveBy::create(0.1, ccp(-5, 0)),nullptr
		);
		this->runAction(myShakeAnimation);
	}
}

int GamePlayer::getHealth()
{
	return m_health;
}

int GamePlayer::getSpeed()
{
	return m_speed;
}

void GamePlayer::fire()
{
	CCPoint positionOfBullet = ccp((this->getPositionX()) + (((this->getContentSize()).width) / 2)*cos((this->getRotation())*PI), (this->getPositionY()) - (((this->getContentSize()).width) / 2)*sin((this->getRotation())*PI));
	Bullets* newBullet1 = Bullets::create1("bullet3_new.png",positionOfBullet,this->getRotation(),PLAYER_BULLET_TAG,m_bulletPower,m_speed);
	playerBullets.pushBack(newBullet1);
	newBullet1->fire();
}

void GamePlayer::destroy() {
	CCSprite* bangSprite = CCSprite::create("blast.png");
	bangSprite->setPosition(this->getPosition());
	auto fadingOut = CCFadeOut::create(1.5f);
	bangSprite->runAction(Sequence::create(fadingOut,RemoveSelf::create(true),nullptr));
	CCDirector::sharedDirector()->getRunningScene()->addChild(bangSprite);
}



