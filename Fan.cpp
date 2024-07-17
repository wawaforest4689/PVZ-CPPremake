#include "Fan.h"
#include <iostream>

using namespace std;

extern IMAGE Drag[4];

Fan::Fan(int sc, int bl, int re,int la)
	:CPlants(sc,bl,6),rest(re),lasting(la),loop(3)
{
	std::cout << "A fan object is initialized!" << std::endl;
}


void Fan::attack(zombies& zm)
{
	if (row < 1 || row>3 || col == 0 || col >= 6)	return;
	int zrow = (zm.gety() - 90) / 78;
	int zcol = (zm.getx() - 430 + 100) / 67;
	if (!(zrow < row - 1 || zrow>row + 1 || zcol > col + 1 || zcol < col - 1)) {
		// dynamic binding and single zm object parameter also supports intelligence of fan!2024.7.4
		// intelligence ability and strength attribute can be adjusted and "enhanced"
		cout << "within range!" << endl;
		cout << "lasting: " << lasting << "rest: "<<rest<<endl;
		action = true;
		if (rest==0)
		{
			if (affecting())
			{
				cout << "within range2!" << endl;
				//if (!zm.getdead() && !zm.getstate()) {
					zm.add_fantag(row, col);
					zm.shift(row, col + 1);
				//}
			}
		}
		else {
			//if (!zm.getdead() && !zm.getstate())
				zm.fantag_reverse(row);
				cout <<"eat: "<< zm.geteat() << "speed: " << zm.getspeed() << endl;
				cout << "col: " << (zm.getx() - 330) / 67 << "row: " << (zm.gety() - 90) / 78 << endl;
		}
	}


}

void Fan::draw()
{
	if (action)
	{
		if (loop == 0)
		{
			loop = 3;
			action = false;
			return;
		}
		if (lasting > 0&&rest==0)
		{
			lasting--;
			int x = 430 + col * 67 - 44;
			int y = 164 + row * 78 - 37;
			std::cout << "frame: " << frame << std::endl;
			display_enhance5(x, y, 157, 160, Drag[frame]);
			frame = (frame + 1) % 3;
		}
		if (lasting == 0) {
			rest = 208;
			lasting = 78;
		}
		if (rest > 0)
		{
			int x = 430 + col * 67;
			int y = 164 + row * 78;
			display_enhance5(x, y, 70, 80, Drag[3]);
			rest--;
		}
		// later appearing than the second if thus only valid when a turn is finished
		if (lasting==78&&rest==0) {
			loop--;
		}
	}
}


bool Fan::affecting()
{
	if (lasting % 9 == 1)
		return true;
	else {
		return false;
	}
}



