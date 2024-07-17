#pragma once
#include "CPlants.h"

class Ice_pea_shooter:public CPlants
{
public:
	Ice_pea_shooter(int = 175, int = 300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
private:
	int count5;
	bool shoot;
};

