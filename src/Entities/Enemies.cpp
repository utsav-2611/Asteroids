#include "Enemies.h"

Enemies::Enemies(void)
{
	state=1;
	this->scheduleUpdate();
}
Enemies* Enemies::create(const char *pszFileName,int health)
{
    Enemies *pobSprite = new Enemies();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        //pobSprite->autorelease();
		pobSprite->m_health = health;
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

Enemies::~Enemies(void)
{
}
bool Enemies::init(){
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	int newPositionX=rand() % (int)(visibleSize.width);
	int newPositionY=rand() % (int)(visibleSize.height);
	/*int newPositionX=(visibleSize.width)/2 + 50;
	int newPositionY=(visibleSize.height)/2 + 50;*/
	int randomAngle=rand()%180;
	CCPoint initialPoint;
	if(newPositionX < visibleSize.width/2){
		if(newPositionY < visibleSize.height/2){
			initialPoint=ccp(newPositionX,20);
			CCActionInterval* movement=CCMoveBy::create(2.0f,ccp((-150)*cos(randomAngle*PI),150*sin(randomAngle*PI)));
			CCActionInterval* rotate=CCRotateBy::create(2.0f,rand()%360);
			randomEnemyMovements(movement,rotate,initialPoint,180.0f,randomAngle);
		}
		else{
			initialPoint=ccp(20,newPositionY);
			CCActionInterval* movement=CCMoveBy::create(2.0f,ccp(150*sin(((float)randomAngle)*PI),150*cos(((float)randomAngle)*PI)));
			CCActionInterval* rotate=CCRotateBy::create(2.0f,rand()%360);
			randomEnemyMovements(movement,rotate,initialPoint,-90.0f,randomAngle);
		}
	}
	else{
		if(newPositionY < visibleSize.height/2){
			initialPoint=ccp(origin.x+visibleSize.width-20,newPositionY);
			CCActionInterval* movement=CCMoveBy::create(2.0f,ccp((-150)*sin(((float)randomAngle)*PI),(-150)*cos(((float)randomAngle)*PI)));
			CCActionInterval* rotate=CCRotateBy::create(2.0f,rand()%360);
			randomEnemyMovements(movement,rotate,initialPoint,90.0f,randomAngle);
		}
		else{
			initialPoint=ccp(newPositionX,visibleSize.height-20);
			CCActionInterval* movement=CCMoveBy::create(2.0f,ccp(150*cos(((float)randomAngle)*PI),(-150)*sin(((float)randomAngle)*PI)));
			CCActionInterval* rotate=CCRotateBy::create(2.0f,rand()%360);
			randomEnemyMovements(movement,rotate,initialPoint,0,randomAngle);
		}
	}
	this->schedule(schedule_selector(Enemies::generateBullets),4);
	return true;
}

void Enemies::randomEnemyMovements(CCActionInterval* movement,CCActionInterval* rotate,CCPoint initialPoint,float offsetAngle,int randomAngle){
	this->setPosition(initialPoint);
	CCActionInterval* rotatingAction=CCRotateBy::create(0.5f,(float)randomAngle+offsetAngle);
	this->runAction(rotatingAction);
	CCActionInterval* actionSequence=CCSequence::create(movement,movement,CCSpawn::create(movement,rotate),nullptr);
	this->runAction(CCRepeatForever::create(actionSequence));
}

void Enemies::generateBullets(float dt){
		CCPoint positionOfBullet=ccp((this->getPositionX())+(((this->getContentSize()).width)/2)*cos((this->getRotation())*PI),(this->getPositionY())-(((this->getContentSize()).width)/2)*sin((this->getRotation())*PI));
		Bullets* newBullet1=Bullets::create1(ENEMY_BULLET,positionOfBullet,this->getRotation(),ENEMY_BULLET_TAG,BULLET_POWER_LOW,1);
		
		newBullet1 -> fire();
}

void Enemies::update(float dt)
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

std::vector<CCSprite*> Enemies::getBulletList(){
	return bullets;
}
void Enemies::reduceHealthBy(int hittingBulletpower) {
	m_health -= hittingBulletpower;
	if (m_health <= 0) {
		this->destroy();
	}
}
void Enemies::destroy() {
	CCSprite* bangSprite = CCSprite::create("blast.png");
	bangSprite->setPosition(this->getPosition());
	CCDirector::sharedDirector()->getRunningScene()->removeChild(this);
	auto fadingOut = CCFadeOut::create(1.5f);
	bangSprite->runAction(Sequence::create(fadingOut, RemoveSelf::create(true), nullptr));
	CCDirector::sharedDirector()->getRunningScene()->addChild(bangSprite);
}
int Enemies::getHealth() {
	return m_health;
}