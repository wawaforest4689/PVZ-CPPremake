#include "rect.h"


using namespace std;

rect::rect(int x1, int y1, int w, int h,COLORREF in_color)
	:x(x1),y(y1),width(w),height(h),color(in_color)
{

}


void rect::restorecolor()
{
	color = RGB(238, 238, 238);
	setcolor(color);
	setlinecolor(BLACK);
	fillrectangle(x, y, x + width, y + height);
}

void rect::setcolor(COLORREF in_color)
{
	color = in_color;
}

void rect::draw()
{
	setfillcolor(color);
	setlinecolor(BLACK);
	fillrectangle(x, y, x + width, y + height);
}

void rect::setxy(int x2, int y2)
{
	x = x2;
	y = y2;
}

bool rect::in_edit(ExMessage &msg)
{
	if (msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height)
	{
		setcolor(WHITE);
		draw();
		return true;
	}
	return false;
}


