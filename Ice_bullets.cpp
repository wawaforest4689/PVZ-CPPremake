#include "Ice_bullets.h"
#include <iostream>

using namespace std;

Ice_bullets::Ice_bullets()
	:bullets(),Ice()
{

}

bool Ice_bullets::collide(zombies& zm)
{
	bool flag = 0;
		//int brow = (y - 164 - 15) / 78;
		//int zrow = (zm.gety() - 90) / 78; //90 is based on tests
		//if (x > x1 && x < x2)
		{
			//cout << "brow" << brow << "zrow" << zrow << endl;
			cout << "Collision!" << endl;
			blast = true;
			speed = 0;
			zm.setblood(zm.getblood() - 20);
			if (!zm.get_iresist()) {
				flag = ice_effect(zm);
				mciSendString("pause 75", 0, 0, 0);
				mciSendString("play materials1/music/111.mp3", 0, 0, 0);
				mciSendString("resume 75", 0, 0, 0);
			}
			//cout << zrow << zm.getx() << "blood:" << zm.getblood();
			if (zm.getblood() <= 0)
			{
				cout << "zm blood:" << zm.getblood() << endl;
				zm.setdead(true);
				zm.setframe(0);
				zm.setfrozen(0);
			}
		}
		return flag;
}
