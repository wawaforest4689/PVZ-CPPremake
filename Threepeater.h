#pragma once
#include "CPlants.h"


class Threepeater:public CPlants
{
public:
	Threepeater(int = 300, int = 300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
private:
	int count2;
	int count5;
	bool shoot;
};

