#include "Pea_shooter.h"
#include "bullets.h"
#include <iostream>


using namespace std;

extern bullets bullset[40];

Pea_shooter::Pea_shooter(int sc,int bl)
	:CPlants(sc,bl,2),count5(0),shoot(0)
{

}


void Pea_shooter::attack(zombies& zm)
{
	int zcol = (zm.getx() - 330) / 67;
	int zrow = (zm.gety() - 90) / 78;
	if (!(zrow != row || zcol <= col)&&zcol<=7)
	{
		shoot = true;
	}
}

void Pea_shooter::draw()
{
	count5++;
	if (count5 >= 18)
	{
		count5 = 0;
		if (shoot)
		{
			int k = 0;
			for (; k < 40 && bullset[k].used == true || bullset[k].delay != 0; k++);
			if (k < 40)
			{
				cout << "k: " << k << endl;
				bullset[k].used = true;
				bullset[k].y = row * 78 + 164 + 15;  //lvlture size is 30x30,thus left-up corner y should be 15 to make center y equal 30
				bullset[k].x = 430 + (col + 1) * 67 - 15;
				bullset[k].speed = 24;
				bullset[k].blast = 0;
			}
			shoot = false;
		}
	}
}