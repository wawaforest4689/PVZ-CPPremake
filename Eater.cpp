#include "Eater.h"
#include <iostream>

extern IMAGE eat[28];
extern IMAGE bite[20];
extern IMAGE digest[20];
#define znum 60

using namespace std;


Eater::Eater(int sc, int bl)
	:CPlants(sc,bl,4),eeat(0),ddigest(0),loop(0)
{
	std::cout << "Eater object initialized!" << std::endl;
}

void Eater::attack(zombies& zm)
{


	/*if (ty == 1)
	{
		std::cout << "the zombie is eaten! " << row << "  " << col << std::endl;
		zm.setstate(true);
		display_enhance5(x, y, 105, 90, eat[frame]);
	}
	else {
		if (ty == 2)
		{
			zm.setblood(zm.getblood() - 40);
			display_enhance5(x, y, 105, 90, bite[frame]);
			if (zm.getblood() <= 0)
			{
				std::cout << "the zombie is dead! " << row << "  " << col << std::endl;
				zm.setdead(true);
				zm.setframe(0);
			}
		}
		else {
			//std::cout << "Digesting... " << row << "  " << col << std::endl;
			display_enhance5(x, y, 105, 90, digest[frame]);
		}
	}
	*/

		int zrow = (zm.gety() - 90) / 78;
		int zcol = (zm.getx() - 430 + 100) / 67;
		// eaters can eat enemies at most a grid away(whether there is laziness in bits or?)
		if (!(zrow != row || zcol<col || zcol>col + 1) && !(eeat || ddigest)) {
			if (!action)
				frame = 0;
			action = true;
			if (zm.gettype() != 8 && zm.gettype() != 9)
			{
				zm.setstate(1);
				eeat = true;
				frame = 0;

			}
			else
			{
				zm.setblood(zm.getblood() - 40);
				//display_enhance5(x, y, 105, 90, bite[frame]);
				//if (zm.getblood() > 0)
				{
					//frame = (frame + 1) % 20;
				}
				if (zm.getblood()<=0)
				{
					std::cout << "the zombie is dead! " << row << "  " << col << std::endl;
					zm.setdead(true);
					zm.setframe(0);
					//if (frame < 19)
					{
						//frame++;
					}
					if (frame>=19)
					{
						frame = 0;
						action = false;
					}
				}
			}
		}
}

		


void Eater::draw()
{
	if (action)
	{
		int x = col * 67 + 430;
		int y = row * 78 + 164;
		if (!digest&&!eeat)
		{
			display_enhance5(x, y, 105, 90, bite[frame]);
			frame = (frame + 1) % 20;
		}
		else {
			if (eeat) {
				display_enhance5(x, y, 105, 90, eat[frame]);
				std::cout << "the zombie is eaten! " << row << "  " << col << std::endl;
				//display_enhance5(x, y, 105, 90, eat[frame]);
				if (frame < 28)
					frame++;
				else
				{
					frame = 0;
					eeat = false;
					ddigest = true;
				}
			}
			else {
				if (ddigest)
				{
					display_enhance5(x, y, 105, 90, digest[frame]);
					if (loop < 50)
					{
						//display_enhance5(x, y, 105, 90, digest[frame]);
						frame = (frame + 1) % 20;
						if (frame == 19) {
							loop++;
							cout << "digestion loop adds 1!" << endl;
						}
					}
					else {
						loop = 0;
						ddigest = 0;
						action = false;
						frame = 0;
					}
				}
			}
		}

	}
}

