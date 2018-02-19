#include "planeA.h"

using namespace std;
planeA::planeA()
{
	m_bulletPower = BULLET_POWER_HIGH;
	m_health = HEALTH_LOW;
	m_speed = SPEED_LOW;
	planeName = "plane1_new.png";
}

planeA * planeA::create()
{
	planeA *pobSprite = new planeA();
	if (pobSprite && pobSprite->initWithFile(pobSprite->planeName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


