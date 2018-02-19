#include "GameOverScene.h"

bool GameOverScene::init()
{
	CCNode* plabel = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 50);
	plabel->setPosition(500, 500);

	CCNode* scoreLabel=Label::createWithTTF("Score : " + m_score, "fonts/Marker Felt.ttf", 50);
	scoreLabel->setPosition(500,400);

	CCLabelTTF* label = CCLabelTTF::create("Play Again", "Arial", 24);
	CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(GameOverScene::menuCallback));
	pMenuItem->setPosition(500,300);
	CCMenu* pMenu1 = CCMenu::create(pMenuItem, NULL);
	pMenu1->setPosition(Vec2::ZERO);

	this->addChild(plabel);
	this->addChild(scoreLabel);
	this->addChild(pMenu1);
	return true;
}

void GameOverScene::runThisTest(int s)
{
	m_score = std::to_string(s);
	CCDirector::sharedDirector()->replaceScene(this);
	this->init();
}
void GameOverScene::menuCallback(Ref* pSender)
{
	// create the Game Play Scene scene and run it
	LevelTransitionScene* pScene = new LevelTransitionScene();
	if (pScene)
	{
		pScene->runThisTest(1, 3, 0);
		//pScene->release();
	}

}
