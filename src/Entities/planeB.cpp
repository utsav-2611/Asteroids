#include "planeB.h"

using namespace std;
planeB::planeB()
{
	m_bulletPower = BULLET_POWER_LOW;
	m_health = HEALTH_HIGH;
	m_speed = SPEED_LOW;
	planeName = "plane2_new.png";
}

planeB * planeB::create()
{
	planeB *pobSprite = new planeB();
	if (pobSprite && pobSprite->initWithFile(pobSprite->planeName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}

