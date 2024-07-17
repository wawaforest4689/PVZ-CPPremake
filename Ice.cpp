#include "Ice.h"
#include <iostream>


using namespace std;

int Ice::big_trigger = 0;

Ice::Ice()
	:small_recover(50),speed_cut(0.5),big_recover(0)
{
}

bool Ice::ice_effect(zombies& zm)
{
	big_trigger++;	
	if (big_trigger % 16 == 0 && big_trigger != 0)
	{
		zm.setspeed(0);
		zm.setfrozen(1);
		zm.setcolor(2);
		zm.zeroharm();
		big_trigger = 0;
		return true;
	}
	else {
		if (!zm.getfrozen())
		{
			zm.setfrozen(0);
			zm.setcolor(2);
			zm.harmcut();
			zm.setspeed(zm.recoverspeed() * speed_cut);
			return false;
		}
	}
	/*if (big_recover == 0)
	{
		if (big_trigger % 16 == 0 && big_trigger != 0)
		{
			small_recover = 0;

			re_big();

			big_trigger = 0;
		}
		else
		{
			re_small();
			zm.setfrozen(0);
			zm.setspeed(zm.recoverspeed() * speed_cut);
			big_recover = 0;
		}
		if (small_recover != 0)
		{
			//if (!zm.get_iresist())
			{
				zm.setspeed(zm.recoverspeed() * speed_cut);
				zm.setcolor(2);
				zm.harmcut();
			}
		return false;
		}
	}

	
	else
	{
		//big_recover--;
		//cout << "big_recover: " << big_recover << endl;
		//if (!zm.get_iresist())
		zm.setspeed(0);
		zm.setfrozen(1);
		zm.setcolor(2);
		zm.zeroharm();
		return true;
	}*/
}

//about 3s
void Ice::re_small()
{
	small_recover = 50;
}

//about 10.5s
void Ice::re_big()
{
	big_recover = 100;
}

void Ice::ice_recover(zombies& zm)
{
	if (small_recover == 0 && big_recover == 0)
	{
		zm.setfrozen(0);
		zm.recoverspeed();
		zm.setcolor(1);
		zm.harmrecover();
	}
}

void Ice::count()
{
	if (small_recover != 0)
	{
		cout << "small_recover: " << small_recover << endl;
		small_recover--;
	}
	if (big_recover != 0)
	{
		cout << "big_recover: " << big_recover << endl;
		big_recover--;
	}
}


double Ice::getspeed_cut()
{
	return speed_cut;
}

int Ice::gets()
{
	return small_recover;
}

int Ice::getb()
{
	return big_recover;
}

