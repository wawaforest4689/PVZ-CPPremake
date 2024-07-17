#pragma once
#include "CPlants.h"
#include <string>

class Eater:public CPlants
{
public:
	Eater(int sc = 150, int bl = 300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
private:
	bool eeat;
	bool ddigest;
	int loop;
};

