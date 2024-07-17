#pragma once
#include "CPlants.h"

class Fan:public CPlants
{
public:
	// 78 is fixed becaus we need to ensure harmony of y coordinate<->3.9s--not having to be 78! 60<->3s
	//160<->8s
	Fan(int=250,int=300,int=0,int=78);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
	bool affecting();
	int get_lasting() { return lasting; };
private:
	int rest;
	int lasting;
	int loop;
};

