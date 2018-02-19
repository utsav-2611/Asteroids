#include "GamePlayScene.h"

using namespace std;
GamePlayScene::GamePlayScene(int l, int lf, int scr) {
	m_level = l;
	m_lives = lf;
	m_score = scr;
	m_handler = new enemyHandler;
	m_collisionDetector = new CollisionDetector;
	this->keys.clear();
	m_handler->setNumberOfEnemies(m_level);
}

void GamePlayScene::initHUD() {
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//initialising the score display
	m_scoreLabel = Label::createWithTTF("Score : " + std::to_string(m_score), "fonts/Marker Felt.ttf", 24);
	m_scoreLabel->setPosition(ccp(origin.x + 50, visibleSize.height - 20));
	this->addChild(m_scoreLabel, 4);

	m_healthLabel = Label::createWithTTF("Health : " + std::to_string(0), "fonts/Marker Felt.ttf", 24);
	m_healthLabel->setPosition(ccp(origin.x + 50, visibleSize.height - 50));
	this->addChild(m_healthLabel, 4);

	//initialising the play-pause button 
	m_pPauseImage = MenuItemImage::create(
		"play_pause.png",
		"play_pause.png",
		CC_CALLBACK_1(GamePlayScene::pauseCallBack, this));
	m_pPauseImage->setPosition(ccp(origin.x + 40, visibleSize.height - 80));
	CCMenu* pMenu1 = CCMenu::create(m_pPauseImage, NULL);
	pMenu1->setPosition(Vec2::ZERO);
	this->addChild(pMenu1);

	//initialising the exit button
	m_exitImage = MenuItemImage::create(
		"exit.png",
		"exit.png",
		CC_CALLBACK_1(GamePlayScene::exitCallBack, this));
	m_exitImage->setPosition(ccp(origin.x + visibleSize.width - 40, visibleSize.height - 80));
	CCMenu* pMenu2 = CCMenu::create(m_exitImage, NULL);
	pMenu2->setPosition(Vec2::ZERO);
	this->addChild(pMenu2);
}

void GamePlayScene::initGamePlayer() {
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	switch (Singleton::get_fighterIndex()) {
	case 0:
		m_player = planeA::create();
		break;
	case 1:
		m_player = planeB::create();
		break;
	case 2:
		m_player = planeC::create();
		break;
	}

	m_player->setPosition(ccp(origin.x + visibleSize.width / 2, visibleSize.height / 2));
	m_player->setTag(1);
	this->addChild(m_player, 0);
}

void GamePlayScene::initEventListener() {
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
		if (find(this->keys.begin(),this->keys.end(),keyCode) == this->keys.end()) {
			this->keys.push_back(keyCode);
		}  
	};
	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if(find(this->keys.begin(), this->keys.end(), keyCode) != this->keys.end())
			this->keys.erase(find(this->keys.begin(),this->keys.end(),keyCode));
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, m_player);
}

void GamePlayScene::updateScore()
{
	m_scoreLabel->setString("Score : " + std::to_string(m_score));
	if (m_score >= m_level*(m_level + 1) * 5) {
		LevelTransitionScene* pScene = new LevelTransitionScene();
		if (pScene)
		{
			pScene->runThisTest(m_level + 1, m_lives, m_score);
			pScene->release();
		}
	}
	m_healthLabel->setString("Health : " + std::to_string(m_player->getHealth()));
}

void GamePlayScene::updatePositionAndRotation()
{
	Vec2 loc = m_player->getPosition();
	float rotation = m_player->getRotation();
	float delta_x = 2 *m_player->getSpeed()* cos(rotation*PI);
	float delta_y = (-2)*m_player->getSpeed()*sin(rotation*PI);
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW)) {
		m_player->setRotation(m_player->getRotation() - 1* m_player->getSpeed());
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW)) {
		m_player->setRotation(m_player->getRotation() + 1* m_player->getSpeed());
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_UP_ARROW)){	// && this->keys.find(EventKeyboard::KeyCode::KEY_UP_ARROW) != this->keys.end()) {
		m_player->setPosition(loc.x + delta_x, loc.y + delta_y);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW)) {
		m_player->setPosition(loc.x - delta_x, loc.y - delta_y);
	}
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE)) {
		m_player->fire();
	}
}

void GamePlayScene::updateEndWallPosition() {
	CCSize visibleSize = CCDirector::sharedDirector()->getWinSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	auto position = m_player->getPosition();
	if (position.x  > origin.x + visibleSize.width)
		position.x = 0;
	else if (position.x < 0)
		position.x = origin.x + visibleSize.width;
	else if (position.y > origin.y + visibleSize.height)
		position.y = 0;
	else if (position.y < 0)
		position.y = origin.y + visibleSize.height;
	m_player->setPosition(position);
}

void GamePlayScene::updateGameOver()
{
	if (m_lives == 0) {
		GameOverScene* pScene = new GameOverScene();
		if (pScene)
		{
			pScene->runThisTest(m_score);
			//pScene->release();
		}
	}
}

void GamePlayScene::updateCollisionEffects()
{
	Vector<Node*> allNodes = this->getChildren();
	Vector<Bullets*> enemyBullets;
	Vector<Bullets*> playerBullets;
	Vector<Enemies*> enemies;

	for (int i = 0; i < allNodes.size(); i++) {
		switch (allNodes.at(i)->getTag()) {
		case ENEMY_TAG:
			enemies.pushBack((Enemies*)allNodes.at(i));
			break;
		case ENEMY_BULLET_TAG:
			enemyBullets.pushBack((Bullets*)allNodes.at(i));
			break;
		case PLAYER_BULLET_TAG:
			playerBullets.pushBack((Bullets*)allNodes.at(i));
			break;
		}
	}

	int collisionState = m_collisionDetector->getCollision(m_player,playerBullets,enemyBullets,enemies);
	CCLOG("%i", m_player->getHealth());
	switch (collisionState) {
		case COLLISION_PLAYER_ENEMYBULLET:
			{
				if (m_player->getHealth() <= 0) {
					m_lives--;
					auto callback = CallFunc::create([this]() {
						LevelTransitionScene* pScene = new LevelTransitionScene();
						if (pScene)
						{
							pScene->runThisTest(m_level, m_lives, m_score);
							//pScene->release();
						}
					});
					this->runAction(Sequence::create(callback, nullptr));
				}
				break;
			}
			
		case COLLISION_PLAYER_ENEMY:
			{
				m_lives--;
				LevelTransitionScene* pScene = new LevelTransitionScene();
				if (pScene)
				{
					pScene->runThisTest(m_level, m_lives, m_score);
					//pScene->release();
				}
				break;
			}
			
		case COLLISION_PLAYERBULLET_ENEMY:
			m_handler->reduceEnemies();
			m_score += 10;
			break;
	}
}

bool GamePlayScene::init() {
	initHUD();
	initGamePlayer();
	initEventListener();
	this->scheduleUpdate();
	return true;
}

enemyHandler * GamePlayScene::getEnemyHandler()
{
	return this->m_handler;
}

void GamePlayScene::pauseCallBack(Ref* pSender)
{
	m_pPauseImage->setCallback(CC_CALLBACK_1(GamePlayScene::resumeCallBack, this));
	Director::getInstance()->pause();
}
void GamePlayScene::resumeCallBack(Ref* pSender)
{
	m_pPauseImage->setCallback(CC_CALLBACK_1(GamePlayScene::pauseCallBack, this));
	Director::getInstance()->resume();
}

void GamePlayScene::exitCallBack(Ref * pSender)
{
	auto scene = HelloWorld::createScene();
	// run
	auto director = Director::getInstance();
	director->replaceScene(scene);
}

bool GamePlayScene::isKeyPressed(EventKeyboard::KeyCode code) {
	if (find(this->keys.begin(), this->keys.end(), code) != this->keys.end() && code == EventKeyboard::KeyCode::KEY_SPACE) {
		this->keys.erase(find(this->keys.begin(), this->keys.end(), EventKeyboard::KeyCode::KEY_SPACE));
		return true;
	}
	else if (find(this->keys.begin(), this->keys.end(), code) != this->keys.end()) {
		return true;
	}
	return false;
}

//double GamePlayScene::keyPressedDuration(EventKeyboard::KeyCode code) {
//	/*if (!isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE))
//		return 0;
//	return std::chrono::duration_cast<std::chrono::milliseconds>
//		(std::chrono::high_resolution_clock::now() - this->keys[code]).count();*/
//}

void GamePlayScene::runThisTest(int l,int remainingLife,int presentm_score)
{
	m_level = l;
	m_lives = remainingLife;
	m_score = presentm_score;
    CCDirector::sharedDirector()->replaceScene(this);
	this->init();
}

void GamePlayScene::update(float delta) {
	Node::update(delta);
	updateScore();
	updatePositionAndRotation();
	updateEndWallPosition();
	updateGameOver();
	updateCollisionEffects();
	CCLOG("%i", m_player->getHealth());
	m_handler->update();
	
}
//std::map<cocos2d::EventKeyboard::KeyCode,
//	std::chrono::high_resolution_clock::time_point> GamePlayScene::this->keys;


