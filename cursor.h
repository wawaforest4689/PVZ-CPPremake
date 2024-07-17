#pragma once
#include <graphics.h>
#include <easyx.h>

class cursor
{
public:
	cursor(int,int,int,int);
	void draw();
	void setxy(int,int);
	//bool count();
private:
	int show_timer;
	int x;
	int y;
	int width;
	int height;
};

