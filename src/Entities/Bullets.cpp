#include "Bullets.h"

Bullets::Bullets(void)
{
	destroyed=false;
	this->scheduleUpdate();
}


Bullets::~Bullets(void)
{
}
Bullets* Bullets::create(const char *pszFileName)
{
    Bullets *pobSprite = new Bullets();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
Bullets * Bullets::create1(const char *pszFileName, CCPoint location, float rotation,int tag,int _bulletPower,int speedFactor)
{
	Bullets *pobSprite = new Bullets();
	if (pobSprite && pobSprite->initWithFile(pszFileName))
	{
		//pobSprite->autorelease();
		pobSprite->setPosition(location);
		pobSprite->setRotation(rotation);
		pobSprite->setTag(tag);
		pobSprite->speed = speedFactor*UNIT_MOVEMENT;
		pobSprite->bulletPower = _bulletPower;
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

bool Bullets::init(){
	
	return true;
}
void Bullets::update(float dt)
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
void Bullets::releasingBullets(float dt){
	//CCDirector::sharedDirector()->getRunningScene()->removeChild(this);
}

void Bullets::fire()
{
	CCActionInterval* movementOfBullet = CCMoveBy::create(1.0f, ccp(this->speed * cos((this->getRotation())*PI), (-this->speed)*sin((this->getRotation())*PI)));
	CCActionInterval* fadingMovementOfBullet = CCMoveBy::create(0.17f, ccp(this->speed * 0.17 * cos((this->getRotation())*PI), (-this->speed * 0.17)*sin((this->getRotation())*PI)));
	CCActionInterval* fadingOut = CCFadeOut::create(0.17f);
	this->runAction(CCSequence::create(movementOfBullet, CCSpawn::create(fadingMovementOfBullet, fadingOut), RemoveSelf::create(true), nullptr));
	this->init();
	CCDirector::sharedDirector()->getRunningScene()->addChild(this);
}

int Bullets::getBulletPower()
{
	return bulletPower;
}

void Bullets::destroy()
{
	CCDirector::sharedDirector()->getRunningScene()->removeChild(this);
}
