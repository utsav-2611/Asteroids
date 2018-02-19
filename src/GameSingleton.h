#pragma once
#include <iostream>
#include "GameMacros.h"
using namespace std;

struct fighterPlane {
	std::string name;
	int bulletPower;
	int health;
	int speed;
};

class Singleton
{
private:
	
	fighterPlane planeA;
	fighterPlane planeB;
	fighterPlane planeC;
	static bool instanceFlag;
	static Singleton *single;
	
	Singleton()
	{
		//private constructor

	}
public:
	static int m_fighterIndex;
	static void set_fighterIndex(int);
	static int get_fighterIndex();
	void initialise();
	static Singleton* getInstance();
	fighterPlane getPlane(int);
	~Singleton()
	{
		instanceFlag = false;
	}
};