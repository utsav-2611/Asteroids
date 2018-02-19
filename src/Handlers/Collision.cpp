#include "Collision.h"

using namespace std;

CollisionDetector::CollisionDetector(void)
{
}


CollisionDetector::~CollisionDetector(void)
{
}

Vec2* getVertices(CCNode* sprite) {
	Vec2 center = sprite->getPosition();
	Vec2* vertices = new Vec2[4];
	vertices[0] = Vec2(sprite->getContentSize().width/2, sprite->getContentSize().height / 2);
	vertices[1] = Vec2(sprite->getContentSize().width / 2, (-1)*sprite->getContentSize().height / 2);
	vertices[2] = Vec2((-1)*sprite->getContentSize().width / 2, (-1)*sprite->getContentSize().height / 2);
	vertices[3] = Vec2((-1)*sprite->getContentSize().width / 2, sprite->getContentSize().height / 2);
	vertices[0].rotate(Vec2(0, 0), (-1)*sprite->getRotation()*PI_BY_180);
	vertices[1].rotate(Vec2(0, 0), (-1)*sprite->getRotation()*PI_BY_180);
	vertices[2].rotate(Vec2(0, 0), (-1)*sprite->getRotation()*PI_BY_180);
	vertices[3].rotate(Vec2(0, 0), (-1)*sprite->getRotation()*PI_BY_180);

	vertices[0] = vertices[0] + center;
	vertices[1] = vertices[1] + center;
	vertices[2] = vertices[2] + center;
	vertices[3] = vertices[3] + center;

	return vertices;
}

Vec2* getSeparatingAxes(Vec2* vertices) {
	//Vec2* vertices = getVertices(sprite);

	Vec2* axes = new Vec2[2];
	axes[0] = vertices[0] - vertices[1];
	axes[1] = vertices[1] - vertices[2];

	float temp = axes[0].y;
	axes[0].y = (-1)*axes[0].x;
	axes[0].x = temp;

	axes[0].normalize();

	temp = axes[1].y;
	axes[1].y = (-1)*axes[1].x;
	axes[1].x = temp;

	axes[1].normalize();

	return axes;

}

projection getProjection(Vec2* vertices, Vec2 axis) {
	float min = vertices[0].dot(axis);
	float max = min;
	for (int i = 1; i < 4; i++) {
		float temp = vertices[i].dot(axis);
		if (temp < min) {
			min = temp;
		}
		else if (temp > max) {
			max = temp;
		}
	}
	projection ansProjection(min, max);
	return ansProjection;
}

int CollisionDetector::collisionDetected(CCNode* sprite1, CCNode* sprite2) {
	Vec2* vertices1 = getVertices(sprite1);
	Vec2* vertices2 = getVertices(sprite2);
	
	Vec2* separatingAxes1 = getSeparatingAxes(vertices1);
	Vec2* separatingAxes2 = getSeparatingAxes(vertices2);

	float check1 = separatingAxes1[1].length();
	float check2 = separatingAxes1[1].dot(vertices1[1]-vertices1[2]);

	for (int i = 0; i < 2; i++) {
		projection projection1 = getProjection(vertices1, separatingAxes1[i]);
		projection projection2 = getProjection(vertices2, separatingAxes1[i]);
		if (projection1.min > projection2.max || projection1.max < projection2.min) {
			return false;
		}
	}
	for (int i = 0; i < 2; i++) {
		projection projection1 = getProjection(vertices1, separatingAxes2[i]);
		projection projection2 = getProjection(vertices2, separatingAxes2[i]);
		if (projection1.min > projection2.max || projection1.max < projection2.min) {
			return false;
		}
	}
	return true;

}
	/*const CCPoint centre1 = sprite1->getPosition();
	const CCPoint centre2 = sprite2->getPosition();
	float radius1 = max(sprite1->getContentSize().width / 2, sprite1->getContentSize().height / 2);
	float radius2 = max(sprite2->getContentSize().width / 2, sprite2->getContentSize().height / 2);
	float distanceBetweenCentres=centre1.getDistance(centre2);

	if (distanceBetweenCentres < (radius1 + radius2) / 2) {
		return true;
	}
	else {
		return false;
	}

	
}*/

/**
returns 1 if enemy bullet and player collides
returns 2 if enemy and player collides
returns 3 if players' bullet and enemy collides
return 0 in all other case
*/

int CollisionDetector::getCollision(GamePlayer * player, Vector<Bullets*> playerBullets, Vector<Bullets*> enemyBullets, Vector<Enemies*> enemies)
{
	for (int i = 0; i < enemyBullets.size(); i++) {
		if (collisionDetected(player, enemyBullets.at(i))) {
			enemyBullets.at(i)->destroy();
			player->reduceHealthBy(enemyBullets.at(i)->getBulletPower());
			return COLLISION_PLAYER_ENEMYBULLET;
		}
	}
	for (int i = 0; i < enemies.size(); i++) {
		if (collisionDetected(player, enemies.at(i))) {
			enemies.at(i)->destroy();
			player->destroy();
			return COLLISION_PLAYER_ENEMY;
		}
	}
	for (int i = 0; i < playerBullets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			if (collisionDetected(playerBullets.at(i), enemies.at(j))) {
				enemies.at(j)->reduceHealthBy(playerBullets.at(i)->getBulletPower());
				playerBullets.at(i)->destroy();
				if (enemies.at(j)->getHealth() <= 0)
					return COLLISION_PLAYERBULLET_ENEMY;
				else
					return NO_REQUIRED_COLLISION;
			}
		}
	}

}

