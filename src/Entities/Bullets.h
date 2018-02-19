#pragma once
#include "cocos2d.h"
#include "GameMacros.h"

USING_NS_CC;

using namespace std;
class Bullets :
	public CCSprite
{
private:
	bool destroyed;
	int bulletPower;
	int speed;
public:
	Bullets(void);
	~Bullets(void);
	bool init() override;
	static Bullets* create(const char*);
	static Bullets* create1(const char*,CCPoint, float, int, int, int);
	void update(float);
	void releasingBullets(float);
	void fire();
	int getBulletPower();
	void destroy();
};
