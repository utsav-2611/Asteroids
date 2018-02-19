#include "PlayerSelector.h"
using namespace std;
bool PlayerSelectorScene::init()
{
	Singleton* mySingleton = Singleton::getInstance();
	mySingleton->initialise();
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	CCSpawn* actionSpawn = CCSpawn::create(CCMoveTo::create(1.0f, ccp(300, visibleSize.height / 2)), CCRotateTo::create(1.0f, 270), CCScaleBy::create(1.0f, 2.0f), nullptr);
	FadeIn* fadingIn1 = FadeIn::create(2.0f);
	FadeIn* fadingIn2 = fadingIn1->clone();
	FadeIn* fadingIn3 = fadingIn1->clone();

	Label* headLabel = Label::createWithTTF("Select Spaceship", "fonts/Marker Felt.ttf", 60);
	headLabel->setPosition(ccp(origin.x + visibleSize.width / 2 , visibleSize.height -200));
	headLabel->runAction(fadingIn1);

	CCSprite* shooter = CCSprite::create(mySingleton->getPlane(shooterIndex).name);
	shooter->setPosition(visibleSize.width / 2 + 200, visibleSize.height / 2);
	shooter->runAction(actionSpawn);

	Label* bulletLabel = Label::createWithTTF("Bullet Power : "+ std::to_string(mySingleton->getPlane(shooterIndex).bulletPower), "fonts/Marker Felt.ttf", 40);
	bulletLabel->setPosition(ccp(origin.x + visibleSize.width/2 + 200, visibleSize.height/2));
	bulletLabel->runAction(fadingIn1);

	Label* healthLabel = Label::createWithTTF("Health : " + std::to_string(mySingleton->getPlane(shooterIndex).health), "fonts/Marker Felt.ttf", 40);
	healthLabel->setPosition(ccp(origin.x + visibleSize.width /2 + 200, visibleSize.height / 2 - 100));
	bulletLabel->runAction(fadingIn2);

	Label* speedLabel = Label::createWithTTF("Speed : " + std::to_string(mySingleton->getPlane(shooterIndex).speed) + "x", "fonts/Marker Felt.ttf", 40);
	speedLabel->setPosition(ccp(origin.x + visibleSize.width /2 + 200, visibleSize.height / 2 + 100));
	bulletLabel->runAction(fadingIn3);
	if (shooterIndex < 2) {
		MenuItemImage* nextImage = MenuItemImage::create(
			"next.png",
			"next.png",
			CC_CALLBACK_1(PlayerSelectorScene::nextCallBack, this));
		nextImage->setPosition(ccp(visibleSize.width - 100, visibleSize.height / 2));
		CCMenu* pMenu1 = CCMenu::create(nextImage, NULL);
		pMenu1->setPosition(Vec2::ZERO);
		this->addChild(pMenu1);
	}
	if (shooterIndex > 0) {
		MenuItemImage* previousImage = MenuItemImage::create(
			"previous.png",
			"previous.png",
			CC_CALLBACK_1(PlayerSelectorScene::previousCallBack, this));
		previousImage->setPosition(ccp(origin.x+50, visibleSize.height / 2));
		CCMenu* pMenu2 = CCMenu::create(previousImage, NULL);
		pMenu2->setPosition(Vec2::ZERO);
		this->addChild(pMenu2);
	}

	MenuItemImage* playImage = MenuItemImage::create(
		"play_button.png",
		"play_button.png",
		CC_CALLBACK_1(PlayerSelectorScene::playCallBack, this));
	playImage->setPosition(ccp(visibleSize.width/2 , 150));
	CCMenu* pMenu3 = CCMenu::create(playImage, NULL);
	pMenu3->setPosition(Vec2::ZERO);
	this->addChild(pMenu3);
	
	this->addChild(shooter);
	this->addChild(bulletLabel);
	this->addChild(healthLabel);
	this->addChild(speedLabel);
	this->addChild(headLabel);
	return true;
}

void PlayerSelectorScene::nextCallBack(Ref* pSender)
{
	auto scene = new PlayerSelectorScene();
	CCDirector::sharedDirector()->replaceScene(TransitionSlideInR::create(1, scene));
	scene->runThisTest(shooterIndex + 1);
}
void PlayerSelectorScene::previousCallBack(Ref* pSender)
{
	auto scene = new PlayerSelectorScene();
	CCDirector::sharedDirector()->replaceScene(TransitionSlideInL::create(1, scene));
	scene->runThisTest(shooterIndex - 1);
}
void PlayerSelectorScene::playCallBack(Ref *)
{
	auto scene = new LevelTransitionScene();
	Singleton::set_fighterIndex(shooterIndex);
	scene->runThisTest(1,3,0);
}
void PlayerSelectorScene::runThisTest(int player)
{
	shooterIndex = player;
	this->init();
}
