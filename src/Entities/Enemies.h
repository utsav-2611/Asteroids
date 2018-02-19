#pragma once
#include "cocos2d.h"
#include "Bullets.h"
#include <cmath>
#include <string>
#include <iostream>
#include <vector>

USING_NS_CC;
using namespace std;

class Enemies : public CCSprite	
{
private:
	std::vector<CCSprite*> bullets;
	void randomEnemyMovements(CCActionInterval*,CCActionInterval*,CCPoint,float,int);
	void Enemies::generateBullets(float dt);
protected:
	bool state;
	int m_health;
public:
	Enemies(void);
	~Enemies(void);
	void update(float);
	static Enemies* create(const char*,int);
	std::vector<CCSprite*> getBulletList();
	bool init() override;
	void reduceHealthBy(int);
	void destroy();
	int getHealth();
};

