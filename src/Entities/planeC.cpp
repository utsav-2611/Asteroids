#include "planeC.h"

using namespace std;
planeC::planeC()
{
	m_bulletPower = BULLET_POWER_LOW;
	m_health = HEALTH_LOW;
	m_speed = SPEED_HIGH;
	planeName = "plane3_new.png";
}

planeC * planeC::create()
{
	planeC *pobSprite = new planeC();
	if (pobSprite && pobSprite->initWithFile(pobSprite->planeName))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}


	
