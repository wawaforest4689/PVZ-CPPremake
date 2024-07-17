#include "Ice_pea_shooter.h"
#include "Ice_bullets.h"
#include <iostream>

using namespace std;

extern Ice_bullets ice_bullset[20];

Ice_pea_shooter::Ice_pea_shooter(int sc, int bl)
	:CPlants(sc, bl,8),count5(0),shoot(0)
{

}


void Ice_pea_shooter::attack(zombies& zm)
{
		int zcol = (zm.getx() - 330) / 67;
		int zrow = (zm.gety() - 90) / 78;
		if (!(zrow != row || zcol <= col)&&zcol<=7)
		{
			shoot = true;
		}
}

void Ice_pea_shooter::draw()
{
	count5++;
	if (count5 >= 18)
	{
		count5 = 0;
		if (shoot)
		{
			int k = 0;
			for (; k < 40 && ice_bullset[k].used == true || ice_bullset[k].delay != 0; k++);
			if (k < 40)
			{
				cout << "k: " << k << endl;
				ice_bullset[k].used = true;
				ice_bullset[k].y = row * 78 + 164 + 15;  //lvlture size is 30x30,thus left-up corner y should be 15 to make center y equal 30
				ice_bullset[k].x = 430 + (col + 1) * 67 - 15;
				ice_bullset[k].speed = 24;
				ice_bullset[k].blast = 0;
			}
			shoot = false;//"intelligence" of peashooters!
		}
	}
}









