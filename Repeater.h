#pragma once
#include "CPlants.h"


class Repeater:public CPlants
{
public:
	Repeater(int sc = 200, int bl = 300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
private:
	int count;
	int count5;
	bool shoot;
};
