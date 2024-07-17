#include "Repeater.h"
#include <iostream>
#include "bullets.h"

using namespace std;

extern bullets bullset[40];

Repeater::Repeater(int sc, int bl)
	:CPlants(sc,bl,15),count(0),count5(0),shoot(0)
{

}



void Repeater::attack(zombies& zm)
{
	int zcol = (zm.getx() - 330) / 67;
	int zrow = (zm.gety() - 90) / 78;
	if (!(zrow != row || zcol <= col)&&zcol<=7)
	{
		shoot = true;
	}
}

void Repeater::draw()
{
	count5++;
	if (count5 >= 18)
	{
		count5 = 0;
		if (shoot)
		{
			for (int k = 0; k < 40; k++)
			{
				if (!bullset[k].used && count < 2)
				{
					bullset[k].delay = 2 * count;
					count++;
					bullset[k].used = true;
					bullset[k].y = row * 78 + 164 + 15;  //lvlture size is 30x30,thus left-up corner y should be 15 to make center y equal 30
					bullset[k].x = 430 + (col + 1) * 67 - 15;
					bullset[k].speed = 24;
					bullset[k].blast = 0;
				}
				if (count == 2)
					break;
			}
			shoot = 0;
		}
		
	}

}