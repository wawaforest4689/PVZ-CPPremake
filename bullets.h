#pragma once
#include "zombies.h"

class bullets
{
public:
	bullets(int = 0, int = 0, int = 0, int = 0, bool = 0, bool = 0,int=0);
	void collide(zombies&,int);
	int x;
	int y;
	int speed;
	int frame;
	bool used;
	bool blast;  //×Óµ¯ËéÁÑÆìÖÄ
	int delay;
};

