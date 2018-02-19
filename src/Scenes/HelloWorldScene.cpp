#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "AppMacros.h"

USING_NS_CC;
using namespace std;
Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto plabel = Label::createWithTTF("Asteroids", "fonts/Marker Felt.ttf", 70);
    
    // position the label on the center of the screen
    plabel->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - plabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(plabel, 1);

    // add "HelloWorld" splash screen"
	 CCLabelTTF* label = CCLabelTTF::create("Play Game", "Arial", 40);
     CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloWorld::menuCallback));
	 pMenuItem->setPosition(CCPointMake((visibleSize.width)/2,(visibleSize.height)/2));
	 CCMenu* pMenu1 = CCMenu::create(pMenuItem, NULL);
     pMenu1->setPosition(Vec2::ZERO);
     this->addChild(pMenu1, 0);    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
void HelloWorld::menuCallback(Ref* pSender)
{
	// create the Game Play Scene scene and run it
	PlayerSelectorScene* pScene = new PlayerSelectorScene();
	if (pScene)
	{
		CCDirector::sharedDirector()->replaceScene(TransitionFade::create(1.0f, pScene));
		pScene->runThisTest(0);
		//pScene->release();
	}

}

