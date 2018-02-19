#pragma once
#include "cocos2d.h"
#include "GamePlay.h"
#include "Enemies.h"
#include <cmath>
#include <vector>

#define PI_BY_180 0.017451

USING_NS_CC;

struct projection {
	float min;
	float max;

	projection(float m, float M) {
		min = m;
		max = M;
	}
};
class CollisionDetector
{
public:
	CollisionDetector(void);
	~CollisionDetector(void);
	int collisionDetected(CCNode*,CCNode*);
	int getCollision(GamePlayer*, Vector<Bullets*>, Vector<Bullets*>, Vector<Enemies*>);
};

