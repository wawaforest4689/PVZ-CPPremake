#pragma once
#include "CPlants.h"

class Melon:public CPlants
{
public:
	Melon(int sc = 50, int bl = 300);
	virtual void attack(zombies& zm) override;
	virtual void draw() override;
	//void restore();
	//bool getland();
private:
	bool detect;
	bool land;
	int check;
};

