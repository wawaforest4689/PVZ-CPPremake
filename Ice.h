#pragma once
#include "zombies.h"
#include <graphics.h>

class Ice
{
public:
	Ice();
	bool ice_effect(zombies&);
	void ice_recover(zombies&);
	void count();
	int gets();
	int getb();
	double getspeed_cut();
	void re_small();
	void re_big();
private:
	static int big_trigger;
	int small_recover;
	int big_recover;//should have the same length as small_recover?
	double speed_cut;
};

