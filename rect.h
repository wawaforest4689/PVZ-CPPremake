#pragma once
#include <graphics.h>

#define bar_width 200
#define bar_height 25

class rect
{
	friend class UI;
public:
	rect(int x1=0, int y1=0, int w=bar_width, int h=bar_height, COLORREF in_color=RGB(238,238,238));
	void draw();
	void restorecolor();
	void setcolor(COLORREF);
	void setxy(int, int);
	bool in_edit(ExMessage&);
private:
	int x;
	int y;
	int width;
	int height;
	COLORREF color;
};

