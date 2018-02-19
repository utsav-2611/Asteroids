#include "LevelTransitionScene.h"

using namespace std;
LevelTransitionScene::LevelTransitionScene()
{
}

bool LevelTransitionScene::init() {
	levelString = "Level " + std::to_string(m_level);
	plabel = Label::createWithTTF(levelString, "fonts/Marker Felt.ttf", 100);
	plabel->setPosition(500,500);
	for (int i = 0; i < m_lives; i++) {
		auto life1 = CCSprite::create("life.png");
		life1->setPosition(430 + i * 60, 400);
		this->addChild(life1);
	}
	auto callback = CallFunc::create([this]() {
		GamePlayScene* pScene = new GamePlayScene(m_level, m_lives, m_score);
		if (pScene)
		{
			pScene->runThisTest(m_level,m_lives,m_score);
			//pScene->release();
		}
	});
	auto fadingOut = CCFadeOut::create(2.0f);
	auto mySequence = Sequence::create(fadingOut,RemoveSelf::create(true),callback,nullptr);
	plabel->runAction(mySequence);
	this->addChild(plabel);
	return true;
}
void LevelTransitionScene::runThisTest(int l,int remainigLife,int presentScore)
{
	CCDirector::sharedDirector()->replaceScene(this);
	m_level = l;
	m_lives = remainigLife;
	m_score = presentScore;
	this->init();
}

void LevelTransitionScene::setLevel(int l){
	m_level = l;
	if (m_level >= 3) {
		m_lives = 3;
	}
	else {
		m_lives = m_level;
	}
}
