#pragma once
#include "bullets.h"
#include "Ice.h"


class Ice_bullets :public bullets, public Ice
{
public:
	Ice_bullets();
	bool collide(zombies&);
};

