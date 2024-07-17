#include "Threepeater.h"
#include <iostream>
#include "bullets.h"

using namespace std;

extern bullets trbullset[30];

Threepeater::Threepeater(int sc, int bl)
	:CPlants(sc,bl,14),count2(0),count5(0),shoot(0)
{

}


void Threepeater::attack(zombies& zm)
{
	int zcol = (zm.getx() - 330) / 67;
	int zrow = (zm.gety() - 90) / 78;
	if (!(zrow != row || zcol <= col)&&zcol<=7) {
		shoot = 1;
	}
	
}


void Threepeater::draw()
{
	count5++;
	if (count5 >= 18)
	{
		count5 = 0;
		if (shoot)
		{
			for (int k = 0; k < 30; k++)
			{
				if (!trbullset[k].used && count2 < 3)
				{
					trbullset[k].delay = 2 * count2;
					count2++;
					trbullset[k].used = true;
					trbullset[k].y = row * 78 + 164 + 15;  //lvlture size is 30x30,thus left-up corner y should be 15 to make center y equal 30
					trbullset[k].x = 430 + (col + 1) * 67 - 15;
					trbullset[k].speed = 24;
					trbullset[k].blast = 0;
				}
				if (count2 == 3)
					break;
			}
			shoot = 0;
		}

	}
}





