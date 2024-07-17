#include "cursor.h"


using namespace std;

int getdelay2()
{
	static unsigned long long int lasttime = 0;
	unsigned long long int currenttime = GetTickCount();
	if (lasttime == 0)
	{
		lasttime = currenttime;
		return 0;
	}

	else
	{
		int interval = currenttime - lasttime;
		lasttime = currenttime;
		return interval;
	}
}

cursor::cursor(int x1, int y1, int w, int h)
	:x(x1),y(y1),width(w),height(h),show_timer(0)
{
	
}

/*bool cursor::count()
{
	static int stimer = 0;
	int ttimer = clock();
	if (ttimer - stimer > 20)
	{
		stimer = ttimer;
		return true;
	}
	return false;
}*/

void cursor::draw()
{
	
	//if (count())
	{
		show_timer=(show_timer+getdelay2())%1200;
	}
	if (show_timer < 600)
	{
		setfillcolor(BLACK);
		rectangle(x, y, x + width, y + height);
	}
	if (show_timer>=30)
	{
		//clearrectangle(x, y, x + width, y + height);
		//setfillcolor(WHITE);
		//rectangle(x, y, x + width, y + height);
	}

}

void cursor::setxy(int x2,int y2)
{
	x = x2;
	y = y2;
}


