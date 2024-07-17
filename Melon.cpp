#include "Melon.h"

extern IMAGE Squeeze[20];



Melon::Melon(int sc, int bl)
	:CPlants(sc, bl, 5),detect(0),land(0),check(0)
{

}

void Melon::attack(zombies& zm)
{
	int zrow = (zm.gety() - 90) / 78;
	int zcol = (zm.getx() - 430 + 100) / 67;

	if (!(zrow != row || zcol<col || zcol>col + 2))
	{
		if (!action)
		{
			frame = 0;
		}
		action = true;
		if (land)
		{
			zm.setdead(1);
			zm.setframe(0);
			sacrify = 1;
			action = false;	//can be omitted here
		}
	}

	//return land;
}

/*void Melon::restore()
{
	detect = land = 0;
}


bool Melon::getland()
{
	return land;
}*/

void Melon::draw()
{
	if (action)
	{
		if (!land) {
			if (!detect) {
				mciSendString("pause 75", 0, 0, 0);
				mciSendString("setaudio materials1/music/115.mp3 volume to 300", 0, 0, 0);
				mciSendString("play materials1/music/115.mp3", 0, 0, 0);
				mciSendString("resume 75", 0, 0, 0);
				detect = true;
			}
			int x = col * 67 + 430;
			int y = (row + 1) * 78 + 164;
			display_enhance5(x, y - 156, 160, 156, Squeeze[frame]);
			check++;
			if (frame < 12 && check>0) {
				frame++;
				check = 0;
			}

			else {
				mciSendString("pause 75", 0, 0, 0);
				mciSendString("setaudio materials1/music/117.mp3 volume to 300", 0, 0, 0);
				mciSendString("play materials1/music/117.mp3", 0, 0, 0);
				mciSendString("resume 75", 0, 0, 0);
				land = true;
				frame = 0;
			}
		}
	}
}