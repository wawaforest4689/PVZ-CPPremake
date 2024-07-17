#include "zombies.h"
#include <stdio.h>
#include <iostream>

using namespace std;

extern IMAGE ptr[32][25];
extern IMAGE ptrb[16][20];
extern IMAGE ptrp[16][20];

// tackle with black bg problem
void display_enhance2(int n, int m, int a, int b, IMAGE input)
{
	DWORD* pmem_input = GetImageBuffer(&input);
	IMAGE temp(a, b);
	DWORD* pmem_temp = GetImageBuffer(&temp);
	for (int i = 0; i < a * b; i++)
	{
		if (pmem_input[i] >= 0 && pmem_input[i] < 0x555555)
			pmem_temp[i] = WHITE;
		else
			pmem_temp[i] = BLACK;
	}
	putimage(n, m, &temp, SRCAND);
	putimage(n, m, &input, SRCPAINT);
}



zombies::zombies(int n)
	:type(n),frame(0),x(1010),y(0),dx(0),dy(0),speed(0),unused(true),tiny_diff2(0),dead(0),eating(0),color(1),frozen(false),fan_tag(0)
{
	// parameters correction		(2024.6.16)
	const int bl_comp[8] = {200,560,200,1300,1300,1600,1160,3600};
	// zm7=zm1x20, zm8=zm1x24
	const int ha_comp[8] = {9,9,9,9,9,9,180,216};
	const bool ice_tag[8] = { 0,0,0,1,0,0,1,0 };
	const bool tempt_tag[8] = { 0,0,0,0,0,0,1,1 };
	const bool weight[8] = { 0,0,0,0,0,0,1,1 };
	blood = bl_comp[type - 1];
	harm = ha_comp[type - 1];
	ice_resist = ice_tag[type - 1];
	tempt_resist = tempt_tag[type - 1];
	heavy = weight[type - 1];
	cout << "a zombie is initialized!" << endl;
}

/*zombies::zombies()
	:type(1),frame(0),x(1010),y(0),speed(0),unused(1), tiny_diff2(0),blood(100),dead(0),eating(0),harm(2),color(1)
{
	for (int i = 0; i < 5; i++)
	{
		record2[i] = 0;
	}
	// questions about the usage of nullptr and NULL in C++
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 40; j++)
		{
			ptr[i][j] = NULL;
		}
	}*/
	//char name[128];
	// assume that the most probable maximum maybe five motions
	/*for (int i = 0; i < 5; i++)
	{
		sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%d/zm_%d_%d_0.gif", 1, 1, i + 1, 1, i + 1);
		if (file2(name))
		{
			record2[0]++;
			cout << record2[0] << endl;
			for (int j = 0; j < 40; j++)
			{
				sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%d/zm_%d_%d_%d.gif", 1, 1, i + 1, 1, i + 1, j);
				if (file2(name))
				{
					record2[i + 1]++;
				}
				else {
					cout << record2[i+1];
					break;
				}
			}
		}
	}
	//cout << "1111";
	for (int i = 0; i < record2[0]; i++)
	{
		//cout <<i<<endl;
		for (int j = 0; j < record2[i + 1]; j++)
		{
			cout << j << " ";
			//cout << i << " ";
			sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%d/zm_%d_%d_%d.gif", 1, 1, i + 1, 1, i + 1, j);
			loadimage(&ptr[i][j], name, 160, 160);
			cout << "common color......" << endl;
			if (i < 2)
			{
				sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%db/zm_%d_%d_%d.jpg", 1, 1, i + 1, 1, i + 1, j);
				loadimage(&ptrb[i][j], name, 160, 160);
				cout << "blue color......" << endl;
				sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%dp/zm_%d_%d_%d.jpg", 1, 1, i + 1, 1, i + 1, j);
				loadimage(&ptrp[i][j], name, 160, 160);
				cout << "purple color......" << endl;
			}
		}
	}
	cout << "Finish initializing!" << endl;
}*/

zombies::zombies(const zombies& input)
	:type(input.type),x(input.x),y(input.y),dx(input.dx),dy(input.dy),frame(input.frame),speed(input.speed),unused(input.unused), tiny_diff2(input.tiny_diff2),blood(input.blood),dead(0),eating(0),harm(input.harm),color(input.color),frozen(input.frozen),tempt_resist(input.tempt_resist),ice_resist(input.ice_resist),
	heavy(input.heavy),fan_tag(input.fan_tag)
{

}


int zombies::getx()
{
	return x;
}

int zombies::gety() const
{
	return y;
}

int zombies::getframe()
{
	return frame;
}

int zombies::getspeed() const
{
	return speed;
}


bool zombies::getstate() const
{
	return unused;
}

void zombies::setx(int n)
{
	x = n;
}


void zombies::sety(int n)
{
	y = n;
}

void zombies::setframe(int n)
{
	frame = n;
}

void zombies::setspeed(int n)
{
	speed = n;
}

void zombies::setstate(bool n)
{
	unused = n;
}

void zombies::walk()
{
	switch (color)
	{
	case 1:
		display_enhance2(x, y, 160, 160, ptr[4*type-4][frame]);
		break;
	case 2:
		//if (ptrb != nullptr)
		if (!ice_resist)
		{
			display_enhance2(x, y, 160, 160, ptrb[2*type-2][frame]);
			//cout << "Blue color coming into effect..." << endl;
		}
		else {
			display_enhance2(x, y, 160, 160, ptr[4*type-4][frame]);
		}
		break;
	case 3:
		//if (ptrp != nullptr)
		if (!tempt_resist)
		{
			display_enhance2(x, y, 160, 160, ptrp[2*type-2][frame]);
		}
		else
		{
			display_enhance2(x, y, 160, 160, ptr[4*type-4][frame]);
		}
		break;
	default:
		break;
	}
}

void zombies::eat()
{
	switch (color)
	{
	case 1:
		display_enhance2(x, y, 160, 160, ptr[4*type-3][frame]);
		break;
	case 2:
		//if (ptrb!=nullptr)
		if (!ice_resist)
			display_enhance2(x, y, 160, 160, ptrb[2*type-1][frame]);
		else
		{
			display_enhance2(x, y, 160, 160, ptr[4 * type - 3][frame]);
		}
		break;
	case 3:
		//if (ptrp!=nullptr)
		if (!tempt_resist)
			display_enhance2(x, y, 160, 160, ptrp[2*type-1][frame]);
		else
		{
			display_enhance2(x, y, 160, 160, ptr[4 * type - 3][frame]);
		}
		break;
	default:
		break;
	}
}

/*void zombies::idle()
{
	display_enhance2(x, y, 160, 160, ptr[3][frame]); 
}*/

void zombies::die()
{
	display_enhance2(x, y, 160, 160, ptr[4*type-2][frame]);
}

/*void zombies::superdie()
{
	display_enhance2(x, y, 160, 160, ptr[4][frame]);
}
*/

void zombies::setdiff(int n)
{
	tiny_diff2 = n;
}

int zombies::getdiff()
{
	return tiny_diff2;
}


//2024.05.23
void zombies::setblood(int n)
{
	blood = n;
}

int zombies::getblood()
{
	return blood;
}


//2024.05.24
bool zombies::getdead()
{
	return dead;
}

void zombies::setdead(bool n)
{
	dead = n;
}


bool zombies::geteat()
{
	return eating;
}

void zombies::seteat(bool n)
{
	eating = n;
}


int zombies::getharm()
{
	return harm;
}

//2024.6.9
// 1 for common(no color), 2 for blue(ice effect and slow), 3 for purple(tempted)
void zombies::setcolor(int co)
{
	color = co;
}

//2024.6.9
int zombies::recoverspeed()
{
	const int comp[8] = { 4,4,6,4,4,10,3,4 };
	speed = comp[type - 1];
	return speed;
}

void zombies::setfrozen(bool n)
{
	frozen = n;
}

bool zombies::getfrozen()
{
	return frozen;
}


int zombies::getcolor()
{
	return color;
}


void zombies::recoverblood()
{
	const int bl_comp[8] = { 200,560,200,1300,1300,1600,1160,3600 };
	blood = bl_comp[type-1];
}

bool zombies::get_iresist()
{
	return ice_resist;
}

bool zombies::get_tresist()
{
	return tempt_resist;
}


void zombies::harmcut()
{
	const int ha_comp[8] = { 9,9,9,9,9,9,180,216 };
	harm = ha_comp[type-1]/2;
}

void zombies::harmrecover()
{
	const int ha_comp[8] = { 9,9,9,9,9,9,180,216 };
	harm = ha_comp[type - 1];
}

void zombies::zeroharm()
{
	harm = 0;
}

int zombies::gettype()
{
	return type;
}


void zombies::shift(int r,int c)
{
	//int xx = c * 67 + 330+67+33;
	// +12/+33 to ensure zombies of the upper line locates at the correct line finally(when t<"2.8s"(actually can't satisfy forever)->lower to about 1.2s),not forming strong contrast meanwhile
	//int yy = r * 78 + 90+12;
	if (fan_tag>0)
	{
		if (fan_tag == 1)
		{
			int xx = (c + 1) * 67 + 330;
			int yy = r * 78 + 90;
			dx = xx - x;
			dy = yy - y;
			cout << "zm dy: " <<dy << endl;
			fan_tag = 2;
		}
		//fan_tag = 2;
		// possible final shifting x value:int that can be divided by 8(max is 72)
		x += dx/8;
		//y += (0 == (yy - oldy) / 77 ? 0 : (yy - oldy) / 77);
		//dy can be divided by 78(???)
		y += dy / 9;
		cout << "new x: " << x << endl;
		cout << "new y: " << y << endl;
	}
}


void zombies::add_fantag(int r, int c)
{
	if (!heavy&&(x - 330) / 67 - c<3 && (x - 330) / 67 - c>-2 && (y - 90) / 78 - r<2 && (y - 90) / 78 - r >-2)
	{
		cout << "Fan_tag added!" << endl;
		fan_tag = 1;
		seteat(false);
		setspeed(0);
	}
}

void zombies::fantag_reverse(int r)
{
	if (r < 0&&fan_tag>0)
	{
		fan_tag = 0;
		recoverspeed();
		return;
	}
	if (fan_tag > 0)
	{
		dy = 90 + r * 78 - y;
		if (dy > 0)
		{
			if (dy*dy<=(78-dy)*(78-dy))
				y += dy;
			else {
				y -= (78 - dy);
			}
		}
		else {
			if (dy < 0)
			{
				if (dy * dy <= (78 + dy) * (78 + dy))
					y += dy;
				else {
					y += (78 + dy);
				}
			}
		}
		fan_tag = 0;
		recoverspeed();
	}
}
















