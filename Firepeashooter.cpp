#include "Firepeashooter.h"
#include <iostream>
#include "bullets.h"


using namespace std;

extern bullets firebullset[20];


Firepeashooter::Firepeashooter(int sc, int bl)
	:CPlants(sc,bl,9),count5(0),shoot(0)
{

}


void Firepeashooter::attack(zombies& zm)
{
	int zcol = (zm.getx() - 330) / 67;
	int zrow = (zm.gety() - 90) / 78;
	if (!(zrow != row || zcol <= col)&&zcol<=7)
	{
		shoot = 1;
	}
	
}


void Firepeashooter::draw()
{
	count5++;
	if (count5 >= 18)
	{
		count5 = 0;
		if (shoot)
		{
			int k = 0;
			for (; k < 20 && firebullset[k].used == true; k++);
			if (k < 20)
			{
				firebullset[k].used = true;
				firebullset[k].y = row * 78 + 164 + 15;  //lvlture size is 30x30,thus left-up corner y should be 15 to make center y equal 30
				firebullset[k].x = 430 + (col + 1) * 67 - 15;
				firebullset[k].speed = 24;
				firebullset[k].blast = 0;
			}
			shoot = 0;
		}
	}
	
}