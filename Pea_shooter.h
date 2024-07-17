#pragma once
#include "CPlants.h"


class Pea_shooter:public CPlants
{
public:
	Pea_shooter(int sc=100,int bl=300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
private:
	int count5;
	bool shoot;
};

