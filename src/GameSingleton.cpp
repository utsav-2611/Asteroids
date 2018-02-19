#include "GameSingleton.h"

bool Singleton::instanceFlag = false;
int Singleton::m_fighterIndex = 0;
Singleton* Singleton::single = NULL;
void Singleton::set_fighterIndex(int l)
{
	m_fighterIndex = l;
}
int Singleton::get_fighterIndex()
{
	return m_fighterIndex;
}
void Singleton::initialise()
{
	planeA.name = "plane1_new.png";
	planeB.name = "plane2_new.png";
	planeC.name = "plane3_new.png";

	planeA.bulletPower = BULLET_POWER_HIGH;
	planeB.bulletPower = BULLET_POWER_LOW;
	planeC.bulletPower = BULLET_POWER_LOW;

	planeA.health = HEALTH_LOW;
	planeB.health = HEALTH_HIGH;
	planeC.health = HEALTH_LOW;

	planeA.speed = SPEED_LOW;
	planeB.speed = SPEED_LOW;
	planeC.speed = SPEED_HIGH;
}
Singleton* Singleton::getInstance()
{
	if (!instanceFlag)
	{
		single = new Singleton();
		instanceFlag = true;
		return single;
	}
	else
	{
		return single;
	}
}

fighterPlane Singleton::getPlane(int index)
{
	switch (index) {
	case 0:
		return planeA;
		break;
	case 1:
		return planeB;
		break;
	case 2:
		return planeC;
		break;
	}
		
}
