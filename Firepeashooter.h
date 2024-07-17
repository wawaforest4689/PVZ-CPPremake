#pragma once
#include "CPlants.h"


class Firepeashooter:public CPlants
{
public:
	Firepeashooter(int = 175, int = 300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
private:
	int count5;
	bool shoot;
};

