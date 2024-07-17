#include "bullets.h"
#include "iostream"

using namespace std;

bullets::bullets(int xx,int yy,int sp,int fr,bool us, bool bl,int de)
	:x(xx),y(yy),speed(sp),frame(fr),used(us),blast(bl),delay(de)
{

}


void bullets::collide(zombies& zm,int harm)
{
	//if (used == 0 || blast) return false;
	//if (zm.getstate() || zm.getdead()) return false;
	// range is necessary because of program random execution state,whether it is zombies' speed or bullets' speed;
	int x1 = zm.getx() + 80;
	int x2 = x1 + 40;
	int brow = (y - 164 - 15) / 78;
	int zrow = (zm.gety() - 90) / 78; //90 is based on tests
	if (brow == zrow && x > x1 && x < x2)
	{
		cout << "brow" << brow << "zrow" << zrow << endl;
		cout << "Collision!" << endl;
		blast = true;
		//speed = 0;
		zm.setblood(zm.getblood() - harm);
		cout << zrow << zm.getx() << "blood:" << zm.getblood();
		if (zm.getblood() <= 0)
		{
			cout << "zm blood:" << zm.getblood() << endl;
			zm.setdead(true);
			zm.setframe(0);
		}
	}
}