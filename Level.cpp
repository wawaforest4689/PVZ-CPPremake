#include "Level.h"

using namespace std;

extern HWND hwnd;


// ccount stands for the total number of plants with achieved functions, 2024.7.1
enum { sunflower = 0, peashooter, wallnut, eater, melon, fan, coconutcannon, icepeashooter, 
	firepeashooter = 8, infinut, bonkchoy, snapdragon, hypnoshroom, threepeater,repeater,maize,mine,weed,ccount };


IMAGE bgp;
IMAGE barr;
IMAGE imgcar[8];
IMAGE imgcarc[8];
IMAGE imgplam[8];
IMAGE imgplas[8][30];
IMAGE imgsunshine[29];
IMAGE ptr[32][25];
IMAGE ptrb[16][20];
IMAGE ptrp[16][20];
IMAGE bullet[4];
IMAGE ice_bullet[4];
IMAGE fire_bullet[5];
IMAGE board;
IMAGE subtitle[4];
IMAGE stop;
IMAGE Flag;
IMAGE Head;
IMAGE Process;
IMAGE wave;
IMAGE last;
IMAGE bottom_ice;
IMAGE eat[28];
IMAGE digest[20];
IMAGE bite[20];
IMAGE Squeeze[28];
IMAGE Drag[4];
bullets bullset[40];
bullets trbullset[30];
bullets firebullset[20];
Ice_bullets ice_bullset[20];
ExMessage msg;
extern Players player;

// fully divided by 10

//bool flag = 0;	//determine whether able to plant certain plant
int record[ccount] = { 0 };
int curX = 0, curY = 0; // used for updating window when moving the cursor
int index = 0; //verify the certian selected plant
int light_collect = 50;
int remain_crowds=0;
//int record2[8][10] = { 0 };
int timer4 = 0;
double compare = 0;
const int* tarray;

// 定义格子地图结构体,如果只是申明全局变量row和col，则不能存储多个植物的位置信息；因此全局变量index也有此缺陷
/*struct plants
{
	int type;
	int framec;
	int catched;
	int blood;
	int sun_cost;
	bool action;
	bool zm_on;
};
plants zhiwu[5][8];*/

struct sunshine
{
	int x, y;
	int framed;
	int unused;
	int maxy;
	int tiny_diff;
};

sunshine sunshineset[20]; // since the minimum falling interval is 6s, and it takes some time for all the
// sunshine balls within a crowd (max=5) to vanish, so 20 may be better than 10

/*struct bullets
{
	int x;
	int y;
	int speed;
	int frame;
	bool used;
	bool blast;  //子弹碎裂旗帜
};*/

vector<CPlants*> plset(40);
vector<CPlants*> baseptr(18);

Level::Level(int cr, int ki, int st, int ma, unsigned short int standard, bool fl,bool qu, double pr, int le, int to, int dp, int tp, double sc)
	:zcrowds(cr),kind(ki),status(st),map(ma),standard_min(standard),flag3(fl),quit(qu),process(pr),sunshine_left(le),total_sunshine(to),dead_plants(dp),total_plants(tp),score(sc),count(0),random(180),count3(0),random3(700),wave_signal(0),bound2(14),count4(0),count2(0),bound(32),
	huge_timer(0),count6(0),count7(0)
{
	/*for (int i = 0; i < 8; i++)
	{
		cardscool[i] = 0;
		bar[i] = 0;
	}*/
	// quick test for new plants
	for (int i = 0; i < 8; i++)
	{
		cardscool[i] = 0;
		bar[i] =i+1;
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			record2[i][j] = 0;
		}
	}
}

void Level::setcrowd(int cr)
{
	zcrowds = cr;
}

void Level::setkind(int ki)
{
	kind = ki;
}

void Level::setstatus_and_map(int sm)
{
	status = sm;
	map = sm;
}

void Level::settime(unsigned short int time)
{
	standard_min = time;
}


double Level::getscore()
{
	sunshine_left = light_collect;
	if (kind == 1)
	{

		// 40=5x8, total number of grids in a map
		//5 scores to handle with finishing time problem,1+2+7
		score = 0.2 * 100 * ((sunshine_left - 50) / 25) / (total_sunshine / 25) + 0.7 * 100 * (1.0 - dead_plants / total_plants) + 0.1 * 100 * (1 - (huge_timer / 60000.0) / standard_min) + 5;
		return score;
	}
	else {
		if (kind == 6)
		{
			//1+1+8
			score = 0.1 * 100 * ((sunshine_left - 50) / 25) / (total_sunshine / 25) + 0.1 * 100 * (1.0 - dead_plants / total_plants) + 0.8 * 100 * (1 - 1 / pow((huge_timer / 30000.0), 0.333));
		}
		return score;
	}
}

int Level::getdelay2(int n)
{
	if (n == 1)
	{
		static unsigned long long int lasttime = 0;
		unsigned long long int currenttime = GetTickCount();
		if (lasttime == 0)
		{
			lasttime = currenttime;
			return 0;
		}

		else
		{
			int interval = currenttime - lasttime;
			lasttime = currenttime;
			return interval;
		}
	}
	else
	{
		if (n == 2)
		{
			static unsigned long long int lasttime2 = 0;
			unsigned long long int currenttime = GetTickCount();
			if (lasttime2 == 0)
			{
				lasttime2 = currenttime;
				return 0;
			}

			else
			{
				int interval = currenttime - lasttime2;
				lasttime2 = currenttime;
				return interval;
			}
		}
		else {
			static unsigned long long int lasttime3 = 0;
			unsigned long long int currenttime = GetTickCount();
			if (lasttime3 == 0)
			{
				lasttime3 = currenttime;
				return 0;
			}

			else
			{
				int interval = currenttime - lasttime3;
				lasttime3 = currenttime;
				return interval;
			}
		}
	}
}

// tackle with black bg problem
void Level::display_enhance(int n, int m, int a, int b, IMAGE input)
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


// file existence judging
bool Level::file(const char* name)
{
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp, name, "r");
	if (fp == NULL)
		return 0;
	fclose(fp);
	return 1;
}

// 渲染函数
void Level::updatewindow()
{
	BeginBatchDraw();
	putimage(0, 0, &bgp);
	putimage(370, 0, &barr);
	/*for (int i = 0; i < ccount; i++)
	{
		int x = 460 + i * 60;
		int y = 0;
		putimage(x, y, &imgcar[i]);
	}
	// putting it last may be rational
	*/

	for (int a = 0; a < 40; a++)
	{
		if (plset[a]->gettype() > 0 && !plset[a]->getaction())
		{
			cout << "type: " << plset[a]->gettype() << endl;
			int num = plset[a]->frame;
			int number = plset[a]->gettype() - 1;
			switch (number + 1)
			{
			case eater + 1:
				display_enhance(430 + 67 * (a % 8), 164 + 78 * (a / 8), 105, 90, imgplas[number][num]);
				break;
			case fan + 1:
				display_enhance((a%8)*67+430, (a/8)*78+164, 70, 80, Drag[3]);
				break;
			default:
				display_enhance(430 + 67 * (a % 8), 164 + 78 * (a / 8), 67, 78, imgplas[number][num]);
				break;
			}


		}
	}

		// display plant image when dragging
		if (index)
		{
			display_enhance(curX - 34, curY - 39, 67, 78, imgplam[index - 1]);
		}

		for (int i = 0; i < 8; i++)
		{
			if (cardscool[i] == 0&&light_collect>=(baseptr[bar[i]-1]->getsc()))
			{
				int x = 460 + i * 60;
				int y = 0;
				putimage(x, y, &imgcar[i]);
			}
			else {
				int x = 460 + i * 60;
				int y = 0;
				putimage(x, y, &imgcarc[i]);
			}
		}

		// sunshine amount count
		LOGFONT f;
		gettextstyle(&f);
		f.lfHeight = 25;
		f.lfWeight = 15;
		settextstyle(&f);
		char score[8];
		sprintf_s(score, sizeof(score), "%d", light_collect);
		outtextxy(392, 74, score);

		//swallow();
		//drag();

		draw_zombies();
		attack();
		//squeeze();

		for (int i = 0; i < sizeof(bullset)/sizeof(bullset[0]); i++)
		{
			if (bullset[i].used&& bullset[i].delay == 0)
			{
				display_enhance(bullset[i].x, bullset[i].y, 30, 30, bullet[bullset[i].frame]);
				cout << "bullet frame: " << bullset[i].frame << endl;
			}

		}

		for (int i = 0; i < sizeof(trbullset) / sizeof(trbullset[0]); i++)
		{
			if (trbullset[i].used && trbullset[i].delay == 0)
			{
				display_enhance(trbullset[i].x, trbullset[i].y, 30, 30, bullet[bullset[i].frame]);
			}

		}

		for (int i = 0; i < sizeof(ice_bullset) / sizeof(ice_bullset[0]); i++)
		{
			if (ice_bullset[i].used)
			{
				display_enhance(ice_bullset[i].x, ice_bullset[i].y, 30, 30, ice_bullet[ice_bullset[i].frame]);
			}
			if (firebullset[i].used)
			{
				display_enhance(ice_bullset[i].x, ice_bullset[i].y, 30, 30, ice_bullet[ice_bullset[i].frame]);
			}
		}

		int max = sizeof(sunshineset) / sizeof(sunshineset[0]);
		for (int i = 0; i < max; i++)
		{
			if (sunshineset[i].unused >= 0 && sunshineset[i].unused <= 23 && sunshineset[i].tiny_diff == 0) // 23*45ms≈1s
			{
				int x = sunshineset[i].x;
				int y = sunshineset[i].y;
				int frame = sunshineset[i].framed;

				display_enhance(x, y, 79, 79, imgsunshine[frame]);
				if (sunshineset[i].unused == 23)
				{
					sunshineset[i].unused = 24;
					cout << 4;
				}
			}
		}

		update_probar();

		EndBatchDraw();
}

bool Level::run()
{	
	int timer = 0;
	bool flag2 = true;
	cleardevice();
	//shuffle();
	gameinit1();
	// 	//int znum = 0; // quantity range
	mciSendString("stop 75", 0, 0, 0);
	mciSendString("play 75 repeat", 0, 0, 0);
	//srand(static_cast<unsigned int>(time(0)));
	/*zombies** zmset2 = new zombies * [20 + 2 * num]();
	for (int i = 0; i < num; i++)
	{
		zmset2[i] = new zombies(1);
	}*/
	while (1)
	{
		userclick();
		usertype(msg);
		timer += getdelay2(1);
		int temp2 = getdelay2(2);
		if (temp2<1000)
			huge_timer += temp2;
		if (timer > 50)
		{
			flag2 = true;
			timer = 0;
		}
		if (flag2)
		{
			flag2 = false;
			updategame();
			updatewindow();
			victory();
		}
		if (quit)
		{
			break;
		}
		//victory();
		//drag(); update costs much more time than functions like userclick
		//Sleep(20);
	}
	//delete[] imgplas;
	//*imgplas = NULL;

	// questions about whether needing to cycle through the array to delete
	//delete[] zmset;
	//zmset = nullptr;
	for (int i = 0; i < 40; i++)
	{
		delete plset[i];
		plset[i] = nullptr;
	}
	for (int j = 0; j < 18; j++)
	{
		delete baseptr[j];
		baseptr[j] = nullptr;
	}
	cout << "win or lose: " << flag3 << endl;
	return flag3;
	//system("pause");
}


// 图形装载初始化函数
void Level::gameinit1()
{
	quit = false;
	flag3 = true;
	remain_crowds = zcrowds;
	process = 0;
	timer4 = 0;
	compare = 0;
	tarray = cards.get_tarray();
	char text[35];
	sprintf_s(text,sizeof(text),"materials1/scissored_bg/%d.png", map);
	loadimage(&bgp, text, width, height);
	loadimage(&barr, "materials1/icons/plants/cards/bar.jpg", 560, 104);
	loadimage(&board, "materials1/level_board/success.png", 500, 510);
	loadimage(&Process, "materials1/level_board/process_bar.jpg", 180, 20);
	loadimage(&Flag, "materials1/level_board/flag.png", 20, 20);
	loadimage(&Head, "materials1/level_board/head.jpg", 20, 20);
	loadimage(&wave, "materials1/level_board/wave.png", 620, 100);
	loadimage(&last, "materials1/level_board/last.png", 425, 100);

	for (int i = 0; i < 4; i++)
	{
		loadimage(&subtitle[i], "materials1/level_board/failure.png", 498*(i+1)/4, 439*(i+1)/4);
	}
	loadimage(&stop, "materials1/level_board/pause.jpg", 700, 500);

	for (int i = 0; i < 40; i++)
	{
		plset[i] = new CPlants(0,0,0,i/8,i%8,0);
	}

	for (int i = 0; i < 20; i++)
	{
		sunshineset[i].x = 0;
		sunshineset[i].y = 0;
		sunshineset[i].framed = 0;
		sunshineset[i].maxy = 0;
		sunshineset[i].unused = 24;
		sunshineset[i].tiny_diff = 0;
	}

	char name[128];
	for (int i = 0; i < 8; i++)
	{
		sprintf_s(name, sizeof(name), "materials1/icons/plants/cards/card_%d.png", bar[i]);
		// LPCSTR and LPCWSTR problem is quite confusing!
		loadimage(&imgcar[i], name, 50, 90);

		sprintf_s(name, sizeof(name), "materials1/icons/plants/cards/card_%dc.jpg", bar[i]);
		loadimage(&imgcarc[i], name, 50, 90);

		sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_%d/plant_%d.png", bar[i], bar[i]);
		loadimage(&imgplam[i], name, 67, 78);
		// two dimensional array initialization
		//imgplas = new IMAGE* [ccount];
		/*for (int i = 0; i < ccount; i++)
		{
			imgplas[i] = new IMAGE[25]();
		}*/
		for (int i = 0; i < 8; i++)
		{
			/*if (bar[i] == fan + 1) {
				record[i] = 1; 
				cout << "record " << i << record[i] << endl;
				continue;
			}*/
			for (int j = 0; j < 30; j++)
			{
				sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_%d/plant_%d (%d).gif", bar[i], bar[i], j + 1);
				if (file(name))
				{
					//cout << 1;
					continue;
				}
				else
				{
					record[i] = j;
					break;
				}

			}
			cout << "record " << i << record[i] << endl;
			//imgplas[i] = new IMAGE[record[i]]();
			for (int j = 0; j < record[i]; j++)
			{
				switch (bar[i])
				{
				case eater+1:
					sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_%d/plant_%d (%d).gif", bar[i], bar[i], j + 1);
					loadimage(&imgplas[i][j], name, 105, 90);
					break;
				default:
					sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_%d/plant_%d (%d).gif", bar[i], bar[i], j + 1);
					loadimage(&imgplas[i][j], name, 67, 78);
					break;
				}
			}
		}
	}

	for (int i = 0; i < 29; i++)
	{
		sprintf_s(name, sizeof(name), "materials1/icons/sunshine/%d.jpg", i);
		loadimage(&imgsunshine[i], name, 79, 79);
	}


	// assume that the most probable maximum maybe five motions
	for (int n = 1; n < 9; n++)
	{
		for (int i = 0; i < 5; i++)
		{
			sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%d/zm_%d_%d_0.gif", n, n, i + 1, n, i + 1);
			if (file(name))
			{
				record2[n-1][0]++;
				cout << record2[n-1][0] << endl;
				for (int j = 0; j < 40; j++)
				{
					sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%d/zm_%d_%d_%d.gif", n, n, i + 1, n, i + 1, j);
					if (file(name))
					{
						record2[n-1][i + 1]++;
					}
					else {
						cout << record2[n-1][i + 1];
						break;
					}
				}
			}
		}
		for (int i = 0; i < record2[n-1][0]; i++)
		{
			for (int j = 0; j < record2[n-1][i + 1]; j++)
			{
				cout << j << " ";
				sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%d/zm_%d_%d_%d.gif", n, n, i + 1, n, i + 1, j);
				loadimage(&ptr[4*n-4+i][j], name, 160, 160);
				if (i < 2)
				{
					sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%db/zm_%d_%d_%d.gif", n, n, i + 1, n, i + 1, j);
					if (file(name))
					{
						loadimage(&ptrb[2*n-2+i][j], name, 160, 160);
						cout << "blue color......" << endl;
					}
					sprintf_s(name, sizeof(name), "materials1/zm/zm_%d/zm_%d_%dp/zm_%d_%d_%d.gif", n, n, i + 1, n, i + 1, j);
					if (file(name))
					{
						loadimage(&ptrp[2*n-2+i][j], name, 160, 160);
						cout << "purple color......" << endl;
					}
				}
			}
		}
		cout << "type " << n << " Finish images loading!" << endl;
	}
	
	// about 1
	//hwnd = initgraph(width, height, 1);

	// srand setting can be put here!(<1s can be then achieved, but maybe longer than 1s is fine)


	loadimage(&bullet[0], "materials1/bullet/pea.gif", 30, 30);
	loadimage(&ice_bullet[0], "materials1/bullet/snowpea.gif",30,30);
	loadimage(&fire_bullet[0], "materials1/bullet/firepea1.gif", 30, 30);
	loadimage(&fire_bullet[1], "materials1/bullet/firepea2.gif", 30, 30);
	loadimage(&fire_bullet[2], "materials1/bullet/firepea3.png", 30, 30);
	loadimage(&fire_bullet[3], "materials1/bullet/firepea4.png", 30, 30);
	loadimage(&fire_bullet[4], "materials1/bullet/firepea5.png", 30, 30);
	loadimage(&bottom_ice, "materials1/effect/ice/icetrap.jpg", 67, 20);
	for (int i = 1; i < 4; i++)
	{
		loadimage(&bullet[i], "materials1/bullet/pea2.gif", 10 * i, 10 * i);
		loadimage(&ice_bullet[i], "materials1/bullet/snowpea2.gif", 10 * i, 10 * i);
	}
	for (int i = 0; i < 40; i++)
	{
		bullset[i].frame = 0;
		bullset[i].speed = 24;
		bullset[i].used = 0;
		bullset[i].x = 0;
		bullset[i].y = 0;
		bullset[i].blast = 0;
		bullset[i].delay = 0;
	}
	for (int i = 0; i < 30; i++)
	{
		trbullset[i].frame = 0;
		trbullset[i].speed = 24;
		trbullset[i].used = 0;
		trbullset[i].x = 0;
		trbullset[i].y = 0;
		trbullset[i].blast = 0;
		trbullset[i].delay = 0;
	}
	for (int i=0;i<20;i++)
	{		
		ice_bullset[i].frame = 0;
		ice_bullset[i].speed = 24;
		ice_bullset[i].used = 0;
		ice_bullset[i].x = 0;
		ice_bullset[i].y = 0;
		ice_bullset[i].blast = 0;
		ice_bullset[i].delay = 0;
		firebullset[i].frame = 0;
		firebullset[i].speed = 24;
		firebullset[i].used = 0;
		firebullset[i].x = 0;
		firebullset[i].y = 0;
		firebullset[i].blast = 0;
		firebullset[i].delay = 0;
	}
	if (kind==1)
		light_collect = 50;
	else {
		if (kind == 6)
			light_collect = 500;
	}
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 25;
	f.lfWeight = 15;
	strcpy_s(f.lfFaceName, "Segoe UI Black");
	settextstyle(&f);
	settextstyle(&f);

	
	//2024.6.5, dynamic and undetermined, should be transfered to another initializing function later
	//2024.6.7
	//baseptr[0] = new Sun_flower;
	baseptr[0] = new CPlants(50,300,1);
	baseptr[1] = new Pea_shooter;
	baseptr[2] = new Wall_nut;
	baseptr[3] = new Eater;
	baseptr[4] = new Melon;
	baseptr[5] = new Fan;
	baseptr[6] = new CPlants(400,300,7);
	baseptr[7] = new Ice_pea_shooter;
	for (int i = 8; i < 18; i++)
	{
		baseptr[i] = new CPlants(150, 300, i);
	}

	for (int i = 0; i < 13; i++)
	{
		sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_5/plant_5_2/plant_5_2 (%d).gif", i + 1);
		loadimage(&Squeeze[i], name, 160, 156);
	}
		for (int i = 0; i < 20; i++)
		{

			//it should not remain 67x78 because the original images(291x250) are often right spare
			sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_4/plant_4_3/plant_4_3 (%d).gif", i + 1);
			loadimage(&bite[i], name, 105, 90);
			sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_4/plant_4_4/plant_4_4 (%d).gif", i + 1);
			loadimage(&digest[i], name, 105, 90);
		}
		for (int i =0; i < 28; i++)
		{
			sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_4/plant_4_2/plant_4_2 (%d).gif", i + 1);
			loadimage(&eat[i], name, 105, 90);
		}
		for (int i = 0; i < 3; i++)
		{
			sprintf_s(name, sizeof(name), "materials1/icons/plants/plant_6/plant_6_2/plant_6_2 (%d).gif", i + 1);
			loadimage(&Drag[i], name, 157, 160);
		}
		loadimage(&Drag[3], "materials1/icons/plants/plant_6/plant_6 (1).gif", 70, 80);
}

// achieve swinging of plants
void Level::updategame()
{
		for (int i = 0; i < 40; i++)
		{
			if ((plset[i]->gettype()) > 0 && plset[i]->get_sacrify())
			{
				delete plset[i];
				plset[i] = new CPlants(0, 0, 0, i / 8, i % 8, 0);
				continue;
			}
				//cout << "plant 0 0:" << plset[0]->gettype() << plset[0]->getaction() << endl;
				if ((plset[i]->gettype()) > 0 && !(plset[i]->getaction()))
				{
					(plset[i]->frame)++;
					int a = (plset[i]->gettype()) - 1;
					// plset[a].framec=(plset[a].framec+1)%record[a];
					int b = (plset[i]->frame);
					//if (&imgplas[i][j] == nullptr) seems invalid
					if (b == record[a])
					{
						(plset[i]->frame) = 0;
						//cout << plset[a].framec;
					}
					//cout << "updategame frame:" << plset[i]->frame << endl;


				}

		}
		// important position!
		int temp = getdelay2(3);
		for (int k = 0; k < 8; k++)
		{
			if (cardscool[k] > 0)
			{
				if (temp<1000)
					cardscool[k] -= temp;
			}
			else
			{
				cardscool[k] = 0;
			}
		}

	// two different level settings(2024.6.30)
	switch (kind)
	{
	case 1:
		//3 is suitable when sunflower is useless(not finished developing yet)
		create_sunshine(3);
		update_sunshine();
		create_zombies(6,9,1);
		update_zombies();
		//zmpos_check();
		//attack();
		updatebullets();
		touchcheck();
		break;
	
	//2024.6.30, challenge mode
	case 6:
		//2 maybe suitable when sunflower is useless
		create_sunshine(2);
		update_sunshine();
		create_zombies(12,18,0);
		update_zombies();
		//zmpos_check();
		//attack();
		updatebullets();
		touchcheck();
		break;
	default:
		break;
	}

}



// solve cursor moving relevant delay problem (failure due to long spending time on updating functions)

/*void Level::drag()
{
	BeginBatchDraw();
	if (index)
	{
		putimage(curX - 34, curY - 39, &imgplam[index - 1], SRCPAINT);
		//cout << 1;
	}
	EndBatchDraw();
}*/


void Level::userclick()
{
	//ExMessage msg;
	static bool flag = 0;
	if (peekmessage(&msg))
	{
		if (msg.message == WM_LBUTTONDOWN && msg.x >= 460 && msg.x <= 460 + 8 * 60 && msg.y <= 90)
		{
			index = (msg.x - 460) / 60 + 1;
			cout << "index-1" << index - 1 << endl;
			cout << "sunshine_cost" << baseptr[bar[index - 1]-1]->getsc() << endl;
			if (light_collect >= (baseptr[bar[index - 1]-1]->getsc())&&cardscool[index-1]==0)
				flag = 1;

			// index reset here is considered more reasonable!
			else
			{
				index = 0;
			}

		}
		else
		{
			if (msg.message == WM_LBUTTONDOWN && flag == 0)
			{
				collect_sunshine(&msg);
			}
			if (msg.message == WM_MOUSEMOVE && flag == 1)
			{
				curX = msg.x;
				curY = msg.y;
			}
			else
			{
				if (msg.message == WM_LBUTTONUP && msg.y < 554 && msg.y>164 && msg.x < 960 && msg.x>430 && flag == 1)
				{
					int row = (msg.y - 164) / 78;
					int col = (msg.x - 430) / 67;
					//cout << row << " " << col << endl;
					if (plset[row*8+col]->gettype() == 0)
					{
						delete plset[row * 8 + col];
						switch (bar[index - 1])
						{
						case 1:
							plset[row * 8 + col] = new CPlants(50, 300, 1);
							break;
						case 2:
							plset[row * 8 + col] = new Pea_shooter;
							break;
						case 3:
							plset[row * 8 + col] = new Wall_nut;
							break;
						case 4:
							plset[row * 8 + col] = new Eater;
							break;
						case 5:
							plset[row * 8 + col] = new Melon;
							break;
						case 6:
							plset[row * 8 + col] = new Fan;
							break;
						case 7:
							plset[row * 8 + col] = new CPlants(400, 300, 7);
							break;
						case 8:
							plset[row * 8 + col] = new Ice_pea_shooter;
							break;
						case 9:
							plset[row * 8 + col] = new Firepeashooter;
							break;
						case 10:
							plset[row * 8 + col] = new CPlants(150, 6000, 10);
							break;
						case 11:
							plset[row * 8 + col] = new CPlants(150, 300, 11);
							break;
						case 12:
							plset[row * 8 + col] = new CPlants(350, 300, 12);
							break;
						case 13:
							plset[row * 8 + col] = new CPlants(100, 300, 13);
							break;
						case 14:
							plset[row * 8 + col] = new CPlants(300, 300, 14);
							break;
						case 15:
							plset[row * 8 + col] = new CPlants(200, 300, 15);
							break;
						case 16:
							plset[row * 8 + col] = new CPlants(100, 300, 16);
							break;
						case 17:
							plset[row * 8 + col] = new CPlants(75, 300, 17);
							break;
						case 18:
							plset[row * 8 + col] = new CPlants(100, 300, 18);
							break;
						default:
							break;
						}
						plset[row * 8 + col]->setrow(row);
						plset[row * 8 + col]->setcol(col);
						cout << "Plant with type " << bar[index - 1] << " is planted!" << endl;
						/*
						plset[row*8+col].type = bar[index-1];
						plset[row*8+col].frame = 0;
						plset[row*8+col].catched = 0;
						plset[row*8+col].blood = (baseptr[bar[index - 1]-1]->getbl());
						plset[row*8+col].sun_cost = (baseptr[bar[index - 1]-1]->getsc());*/
						light_collect -= plset[row*8+col]->getsc();
						total_plants++;
						/*switch (bar[index - 1]) {
						case 4:
							eaters[row * 8 + col].row = row;
							eaters[row * 8 + col].col = col;
							break;
						case 5:
							melons[row * 8 + col].row = row;
							melons[row * 8 + col].col = col;
							break;
						case 6:
							fans[(row - 1) * 6 + col - 1].row = row;
							fans[(row - 1) * 6 + col - 1].col = col;
							break;
						default:
							break;
						}*/

						
					}
					cardscool[index - 1] = 500*tarray[bar[index - 1]-1];

					index = 0;
					flag = 0;
				}
				if (msg.message == WM_LBUTTONUP && msg.x >= 460 + (index - 1) * 60 && msg.x <= 460 + index * 60 && msg.y <= 90)
				{
					index = 0;
					flag = 0;
				}
				// notice the postion of the latter code
				//index=0; can be omitted?  ——can't
				//index = 0;
				//flag = 0;
			}

		}
	}
}

// sunshine creation function
void Level::create_sunshine(int speed)
{
	count++;
	if (count >= random)
	{
		//cout << 2;
		//srand(static_cast<unsigned int>(time(0))); //may run less than 1s in fact, however 45ms*400>1000ms=1s because of the former operation
		count = 0;
		random = 200 + rand() % 68; // let the falling interval remains between about "9s-12s"
		int max = sizeof(sunshineset) / sizeof(sunshineset[0]);
		srand(static_cast<unsigned int>(time(0)));
		int number = rand() % 5 + speed;
		total_sunshine += number * 25;
		int step = 0;
		for (int i = 0; i < max && sunshineset[i].unused > 23; i++)
		{
			number--;
			cout << 3;
			if (number >= 0)
			{
				sunshineset[i].unused = 0;
				sunshineset[i].framed = 0;
				sunshineset[i].maxy = 164 - 79 + (rand() % 5 + 1) * 78;
				sunshineset[i].x = 430 + rand() % 502; // 502=1010-430-79+1
				sunshineset[i].y = 0;
				sunshineset[i].tiny_diff = step;
				step++;
			}
			else
			{
				break;
			}
		}
	}
}

void Level::update_sunshine()
{
	int max = sizeof(sunshineset) / sizeof(sunshineset[0]);
	for (int i = 0; i < max; i++)
	{
		if (sunshineset[i].unused == 0 && sunshineset[i].tiny_diff == 0)
		{
			sunshineset[i].framed = (sunshineset[i].framed + 1) % 29; // simply use ++ can not solve the upper bound problem, see updategame() function
			sunshineset[i].y += 4;
		}
		if (sunshineset[i].tiny_diff > 0)
		{
			//static int count2 = 0;
			//static int bound = 32;
			count2++;
			if (count2 == bound)
			{
				sunshineset[i].tiny_diff--;
				srand(static_cast<unsigned int>(time(0))); // constrained to the principle of the srand function, time interval can not be less than 1s
				count2 = 0;
				bound = rand() % 35 + 46;   // control the time interval within a crowd to stay between "1.0s-1.8s"
			}
		}
		if (sunshineset[i].y >= sunshineset[i].maxy)
		{
			sunshineset[i].framed = (sunshineset[i].framed + 1) % 29;
			sunshineset[i].unused += 1;
		}
	}
}

void Level::collect_sunshine(ExMessage* msg)
{
	int max = sizeof(sunshineset) / sizeof(sunshineset[0]);
	for (int i = 0; i < max; i++)
	{
		int x = sunshineset[i].x;
		int y = sunshineset[i].y;
		if (sunshineset[i].unused <= 23 && msg->x >= x + 22 && msg->x <= x + 54 && msg->y >= y + 22 && msg->y <= y + 54)
		{
			sunshineset[i].unused = 24;
			light_collect += 25;
			mciSendString("pause 75", 0, 0, 0);
			mciSendString("setaudio materials1/icons/sunshine/sunshine.mp3 volume to 300", 0, 0, 0);
			mciSendString("play materials1/icons/sunshine/sunshine.mp3", 0, 0, 0);
			mciSendString("resume 75", 0, 0, 0);
		}
	}
}


void Level::create_zombies(int base,int range,bool limit)
{
		//static int count3 = 0;
		count3++;
		//static int random3 = 400;
		if (count3 == random3)
		{
			srand(static_cast<unsigned int>(time(0)));
			//cout << 2;
			//srand(static_cast<unsigned int>(time(0))); //may run less than 1s in fact, however 45ms*500>1000ms=1s because of the former operation
			count3 = 0;
			random3 = 1700 + rand() % 400; // let the falling interval remains between about 13.5s-27s->30s-40s->85s-105s
			if (limit)
			{
				if (remain_crowds > 0)
				{
					remain_crowds--;
					process = 1.0 - (remain_crowds * 1.0 / zcrowds);
					cout << "process: " << process << endl;
					int quantity = rand() % range + base;
					int step2 = 0;
					for (int i = 0; i < znum; i++)
					{
						if (quantity >= 0)
						{
							if (zmset[i].getstate() == true)
							{
								cout << "555";
								quantity--;
								int y = rand() % 5 * 78 + 90; //90 is based on tests and trials
								zmset[i].setstate(false);
								zmset[i].recoverspeed();
								zmset[i].recoverblood();
								zmset[i].harmrecover();
								zmset[i].setx(1010);
								zmset[i].sety(y);
								zmset[i].setdiff(step2);
								zmset[i].seteat(false);	   //final assurance
								zmset[i].setdead(false);	//final assurance
								zmset[i].setframe(0);	//final assurance
								zmset[i].setcolor(1);
								zmset[i].setfrozen(0);
								step2++;
							}
						}
						else
						{
							break;
						}
					}
				}
			}
			else
			{
				wave_signal = true;
				int quantity = rand() % range + base;
				int step2 = 0;
				for (int i = 0; i < znum; i++)
				{
					if (quantity >= 0)
					{
						if (zmset[i].getstate() == true)
						{
							cout << "555";
							quantity--;
							int y = rand() % 5 * 78 + 90; //90 is based on tests and trials
							zmset[i].setstate(false);
							zmset[i].recoverspeed();
							zmset[i].recoverblood();
							zmset[i].harmrecover();
							zmset[i].setx(1010);
							zmset[i].sety(y);
							zmset[i].setdiff(step2);
							zmset[i].seteat(false);	   //final assurance
							zmset[i].setdead(false);	//final assurance
							zmset[i].setframe(0);	//final assurance
							zmset[i].setcolor(1);
							zmset[i].setfrozen(0);
							step2++;
						}
					}
				}
			}
		}
}

void Level::update_zombies()
{
	// take uniform actions method(characterized method is also accepted)
	//static int count6 = 0;
	count6++;
	if (count6 > 5)
	{
		count6 = 0;
		for (int i = 0; i < znum; i++)
		{
			if (zmset[i].getstate() == false && zmset[i].getdead() == 0 && zmset[i].geteat() == 0 && zmset[i].getdiff() == 0)
			{
				int x = zmset[i].getx() - zmset[i].getspeed();
				zmset[i].setx(x);
				int frame=0;
				if (!zmset[i].getfrozen())
				{
					//cout << "not frozen......" << endl;
					//cout << zmset[i].getrecord()[1]<<endl;
					//if (!(zmset[i].getcolor() == 2))
					frame = (zmset[i].getframe() + 1) % record2[zmset[i].gettype()-1][1];
					/*else
					{
						compare+=ice_bullset[0].getspeed_cut();
						if (compare >= 1)
						{
							compare = 0;
							frame = (zmset[i].getframe() + 1) % zmset[i].getrecord()[1];
						}
					}*/
					zmset[i].setframe(frame);
					cout << zmset[i].getframe()<<endl;
				}
			}
			if (zmset[i].getdead())
			{
				zmset[i].seteat(false);	//2024.6.5 check and complement
				int zrow = (zmset[i].gety() - 90) / 78;// 90 is based on tests
				int zcol = (zmset[i].getx() - 330) / 67;
				plset[zrow*8+zcol]->zm_on = 0;
				zmset[i].fantag_reverse(-1);
				if (zmset[i].getframe() < record2[zmset[i].gettype()-1][3] - 1)
				{
					zmset[i].setframe(zmset[i].getframe() + 1);
				}
				else
				{
					zmset[i].setstate(true);
					zmset[i].setdead(false);
					zmset[i].setframe(0);	//for reminding use
				}
			}
			if (zmset[i].geteat()&&!zmset[i].getstate()&&!zmset[i].getdead())
			{
				zmset[i].setframe((zmset[i].getframe() + 1) % record2[zmset[i].gettype()-1][2]);
			}
			if (zmset[i].getdiff() > 0)
			{
				//static int count4 = 0;
				//static int bound2 = 14;
				count4++;
				if (count4 >= bound2)
				{
					cout << "777";
					srand(static_cast<unsigned int>(time(0)));
					count4 = 0;
					bound2 = rand() % 6 + 11;
					int diff = zmset[i].getdiff() - 1;
					zmset[i].setdiff(diff);
				}
			}
			if (zmset[i].getx() < 335)
			{
				flag3 = false;
				/*cout << "Game over!" << endl;
				MessageBox(hwnd, "over", "over", 0);
				exit(0);*/
			}
		}
	}

}

void Level::draw_zombies()
{
	for (int i = 0; i < znum; i++)
	{
		if (zmset[i].getstate() == false && zmset[i].getdead() == 0 && zmset[i].geteat() == 0 && zmset[i].getdiff() == 0)
		{
			zmset[i].walk();
			//cout << "frame: " << zmset[i].getframe();
			if (zmset[i].getfrozen())
			{
				display_enhance(zmset[i].getx() + 100, zmset[i].gety() + 140, 67, 20, bottom_ice);
				//putimage(zmset[i].getx() + 100, zmset[i].gety() + 140,  &bottom_ice);
				cout << "zm frozen: " << zmset[i].getx() << "  " << zmset[i].gety() << endl;
			}
		}
		if (zmset[i].getdead())
		{
			zmset[i].die();
		}
		if (zmset[i].geteat()&&!zmset[i].getstate()&&!zmset[i].getdead())
		{
			zmset[i].eat();
		}

		
	}

}

//2024.05.02,2024.05.23
void Level::attack()
{
	//zmpos_check();
	//static int count5 = 0;

			for (int i = 0; i < 40; i++)
			{
				if (plset[i]->gettype() == 0)	continue;
				for (int j = 0; j < znum; j++)
				{
					if (zmset[j].getstate() || zmset[j].getdead())	continue;
					plset[i]->attack(zmset[j]);
				}
				plset[i]->draw();
			}

}


//display bullet	2024.05.23
void Level::updatebullets()
{
	for (int i = 0; i < sizeof(bullset) / sizeof(bullset[0]); i++)
	{
		if (bullset[i].used == 1 && !bullset[i].blast&&bullset[i].x < 1010&&bullset[i].delay==0)
		{
			bullset[i].x += bullset[i].speed;
		}

		// this check can be ignored now?
		if (bullset[i].x >= 1010)
		{
			bullset[i].used = 0;
		}

		if (bullset[i].blast == true)
		{
			//bullset[i].speed = 0; exist in collisioncheck function;
			bullset[i].frame++;
			if (bullset[i].frame == 4)
			{
				bullset[i].used = 0;
				bullset[i].frame = 0;
				bullset[i].blast = false;
			}

		}
		if (bullset[i].delay > 0)
		{
			bullset[i].delay--;
		}
	}

	for (int i = 0; i < sizeof(trbullset) / sizeof(trbullset[0]); i++)
	{
		if (trbullset[i].used == 1 && !trbullset[i].blast && trbullset[i].x < 1010 && trbullset[i].delay == 0)
		{
			trbullset[i].x += trbullset[i].speed;
		}

		// this check can be ignored now?
		if (trbullset[i].x >= 1010)
		{
			trbullset[i].used = 0;
		}

		if (trbullset[i].blast == true)
		{
			//bullset[i].speed = 0; exist in collisioncheck function;
			trbullset[i].frame++;
			if (trbullset[i].frame == 4)
			{
				trbullset[i].used = 0;
				trbullset[i].frame = 0;
				trbullset[i].blast = false;
			}

		}
		if (trbullset[i].delay > 0)
		{
			trbullset[i].delay--;
		}
	}

	for (int i = 0; i < sizeof(ice_bullset) / sizeof(ice_bullset[0]); i++)
	{
		if (ice_bullset[i].used == 1 && ice_bullset[i].x < 1010&&!ice_bullset[i].blast)
		{
			ice_bullset[i].x += ice_bullset[i].speed;
		}

		// this check can be ignored now?
		if (ice_bullset[i].x >= 1010)
		{
			ice_bullset[i].used = 0;
		}

		if (ice_bullset[i].blast == true)
		{
			ice_bullset[i].frame++;
			if (ice_bullset[i].frame == 4)
			{
				ice_bullset[i].used = 0;
				ice_bullset[i].frame = 0;
				ice_bullset[i].blast = false;
			}

		}
	}
	for (int i = 0; i < sizeof(firebullset) / sizeof(firebullset[0]); i++)
	{
		if (firebullset[i].used == 1 && firebullset[i].x < 1010&&!firebullset[i].blast)
		{
			firebullset[i].x += firebullset[i].speed;
			firebullset[i].frame = (firebullset[i].frame + 1) % 2;
		}

		// this check can be ignored now?
		if (firebullset[i].x >= 1010)
		{
			firebullset[i].used = 0;
		}

		if (firebullset[i].blast == true)
		{
			//bullset[i].speed = 0; exist in collisioncheck function;
			firebullset[i].frame++;
			if (bullset[i].frame == 5)
			{
				firebullset[i].used = 0;
				firebullset[i].frame = 0;
				firebullset[i].blast = false;
			}

		}
	}
}


//2024.05.23
void Level::collisioncheck()
{
	// two different styles of cycling embedding because of different requirements
	for (int i = 0; i < 40; i++)
	{
		if (bullset[i].used == 0 || bullset[i].blast) continue;
		for (int j = 0; j < znum; j++)
		{
			if (zmset[j].getstate() || zmset[j].getdead()) continue;
			bullset[i].collide(zmset[j],20);
		}
	}
	for (int i = 0; i < 30; i++)
	{
		if (trbullset[i].used == 0 || trbullset[i].blast) continue;
		for (int j = 0; j < znum; j++)
		{
			if (zmset[j].getstate() || zmset[j].getdead()) continue;
			trbullset[i].collide(zmset[j], 20);
		}
	}
	for (int j = 0; j < znum; j++)
	{
		if (zmset[j].getstate() || zmset[j].getdead()) continue;
		bool judge = 0;
		int zrow = (zmset[j].gety() - 90) / 78;
		for (int i = 0; i < 20; i++)
		{
			if (!ice_bullset[i].used || ice_bullset[i].blast) continue;
			int brow = (ice_bullset[i].y - 164 - 15) / 78;
			int x1 = zmset[j].getx() + 80;
			int x2 = x1 + 40;
			if (brow == zrow&&ice_bullset[i].x>x1&&ice_bullset[i].x<x2)
			{
				cout << "brow" << brow << "zrow" << zrow << endl;
				bool flag=ice_bullset[i].collide(zmset[j]);
				cout << zrow << zmset[j].getx() << "blood:" << zmset[j].getblood();
				judge = 1;
				if (!flag)
				{
					ice[j].re_small();
				}
				else {
					ice[j].re_big();
				}
			}
		}
		if (!judge)
		{
			if (zmset[j].getcolor() == 2)
			{
				ice[j].count();
				ice[j].ice_recover(zmset[j]);
				cout << "ice recovering ..." << endl;
			}
		}
	}
	for (int i = 0; i < 20; i++)
	{
		if (firebullset[i].used == 0 || firebullset[i].blast) continue;
		for (int j = 0; j < znum; j++)
		{
			if (zmset[j].getstate() || zmset[j].getdead()) continue;
			firebullset[i].collide(zmset[j], 40);
		}
	}
}

//2024.05.25
void Level::eatcheck()
{
	count7++;
	if (count7 >= 3)
	{
		count7 = 0;
		for (int i = 0; i < znum; i++)
		{
			if (zmset[i].getstate() || zmset[i].getdead()) continue;
			int zrow = (zmset[i].gety() - 90) / 78;
			// image display problem
			//150 may be very appropriate
			int zcol = (zmset[i].getx() - 430 + 100) / 67;
			if (zcol < 8 && zcol >= 0)
			{
				//for (int j = 0; j < 8; j++)
	//{
		//if (zhiwu[zrow][j].type == 0)	//continue;
				if (plset[zrow*8+zcol]->gettype() == 0)
				{
					if (zmset[i].geteat())
					{
						zmset[i].seteat(false);
					}
				}
				else
				{
					//if (zmset[i].getx() <= j * 67 + 430)
					{
						if (!zmset[i].geteat())
						{
							plset[zrow*8+zcol]->catched++;
							zmset[i].seteat(true);
							zmset[i].setframe(0);
						}
						plset[zrow*8+zcol]->setbl(plset[zrow * 8 + zcol]->getbl() - zmset[i].getharm() * plset[zrow * 8 + zcol]->catched);
						cout << "plant blood: " << plset[zrow*8+zcol]->getbl() << endl;
						cout << "catched: " << plset[zrow*8+zcol]->catched << endl;
						cout << "type: " << plset[zrow*8+zcol]->gettype() << endl;
						if (plset[zrow * 8 + zcol]->getbl() <= 0)
						{
							/*plset[zrow * 8 + zcol].type = 0;
							plset[zrow*8+zcol].blood = 0;
							plset[zrow*8+zcol].sun_cost = 0;
							plset[zrow*8+zcol].catched = 0;
							plset[zrow*8+zcol].framec = 0;
							plset[zrow*8+zcol].action = false;
							eaters[zrow * 8 + zcol].row = eaters[zrow * 8 + zcol].col = -1;
							eaters[zrow * 8 + zcol].ddigest = eaters[zrow * 8 + zcol].eeat = false;
							eaters[zrow * 8 + zcol].loop = 0;
							fans[(zrow - 1) * 6 + zcol - 1].row = fans[(zrow - 1) * 6 + zcol - 1].col = -1;*/
							delete plset[zrow * 8 + zcol];
							plset[zrow * 8 + zcol] = new CPlants(0,0,0,zrow,zcol,0);
							dead_plants++;
							zmset[i].seteat(false);
							zmset[i].setframe(0);
						}
					}
				}
				//}
			}
		}
	}

}

//2024.05.25
void Level::touchcheck()
{
	collisioncheck();
	eatcheck();
}


void Level::victory()
{		
	int timer2 = 0;
	if (kind == 1)
	{
		int i = 0;

		if (process == 1 && flag3)
		{
			for (; i < znum; i++)
			{
				if (!zmset[i].getstate()) break;
			}
			if (i == znum)
			{
				getscore();
				//player.quit_and_save(status, score);
				quit = true;
				kind = 0;
				mciSendString("stop 75", 0, 0, 0);
				mciSendString("play materials1/music/130.mp3", 0, 0, 0);
				stay_and_display(board, 255, 55, 500, 510);
			}
			//return true;
		}

		if (!flag3)
		{
			for (int i = 0; i < 900; i++)
			{
				display_enhance(505 - 498 * (i / 300 + 1) / 8, 310 - 439 * (i / 300 + 1) / 8, 498 * (i / 300 + 1) / 4, 439 * (i / 300 + 1) / 4, subtitle[i / 300]);
				if (i % 300 == 299)
				{
					cleardevice();
				}
			}
			int temp = getdelay2(1);
			while (timer2 < 3000)
			{

				display_enhance(256, 90, 498, 439, subtitle[3]);
				timer2 += getdelay2(1);
			}
			quit = true;
			kind = 0;
			mciSendString("stop 75", 0, 0, 0);
			//return false;
		}
		//return false;
	}
	else {
		if (kind == 6)
		{
			if (!flag3)
			{
				getscore();
				quit = true;
				kind = 0;
				mciSendString("stop 75", 0, 0, 0);
				mciSendString("play materials1/music/130.mp3", 0, 0, 0);
				stay_and_display(board, 255, 55, 500, 510);
			}
		}
	}
}


//input for lvltures already loaded
void Level::stay(IMAGE& lvlture,int x,int y,int w,int h)
{
	bool flag4 = 0;
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 200;
	f.lfWeight = 10;
	settextstyle(&f);
	ExMessage msg;
	while (1)
	{
		BeginBatchDraw();
		display_enhance(x, y, w, h, lvlture);
		outtextxy(x + w / 2 - 140, y + h / 2 - 100, "STOP");
		cout << "waiting for space" << endl;
		if (peekmessage(&msg) && msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE)
		{
			break;
		}
		EndBatchDraw();
	}
}

void Level::stay_and_display(IMAGE& lvlture, int x, int y, int w, int h)
{
	bool flag5 = 0;
	char text[40];
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 40;
	f.lfWeight = 10;
	settextstyle(&f);
	setcolor(YELLOW);
	ExMessage msg;
	while (1)
	{
		BeginBatchDraw();
		//msg = getmessage(EX_CHAR);
		display_enhance(x, y, w, h, lvlture);
		sprintf_s(text, sizeof(text), "dead plants proportion:  %.2f", dead_plants * 1.0 / total_plants);
		outtextxy(x + w / 2 - 250, y + h / 2 - 160, text);
		sprintf_s(text, sizeof(text), "finishing time(sec):  %d", huge_timer / 1000);
		outtextxy(x + w / 2 - 250, y + h / 2 - 80, text);
		sprintf_s(text, sizeof(text), "remaining sunshine proportion:  %.2f", ((sunshine_left - 50) / 25.0) / (total_sunshine / 25));
		outtextxy(x + w / 2 - 250, y + h / 2, text);
		sprintf_s(text, sizeof(text), "total score:  %.2f", score);
		outtextxy(x + w / 2 - 250, y + h / 2 + 120, text);
		if (peekmessage(&msg)&&msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE)
		{
			break;
		}
		EndBatchDraw();
	}
}


void Level::usertype(ExMessage& msg)
{
	if (peekmessage(&msg) && msg.message == WM_KEYDOWN && msg.vkcode == VK_SPACE)
	{
		stay(stop, 155, 60, 700, 500);
	}
}

// 2024.6.9

//const int comp[10]={0,8,14,18,20,20,18,14,8,0};
void Level::setstructure(int type, int hard)
{
	int base[10] = { 0 };
	int break_point = 0;
	for (int i = 0; i < type; i++)
	{
		if (type == 1)
		{
			base[0] = 10;
		}
		if (type == 10)
		{
			base[i] = 1;
		}
		if (type>1&&type<10)
		{
			if (hard != 0)
			{
				base[i] = (10 - type < hard ? 1 : 10+1 - type - hard);
				hard -= 10+1 - type - base[i];
				break_point = i;
			}
			else
			{
				base[i] = 1;
			}
		}
	}
	if (type != 1&&type!=10)
	{
		base[break_point + 1] = 10 - (type - 2) - base[break_point];
	}
	for (int k = 0; k < (znum / 10); k++)
	{
		int j = 1;
		int sum = base[0];
		for (int i = 0; i < 10; i++)
		{
			if (i + 1 <= sum)
			{
				// change into a new zombie generating method
				//for (int k = 0; k < znum / 10; k++)
				//{
				zmset[i + k*10] = zombies(j);
				cout << "zombie with type " << j << " is created!" << endl;
				//}
			}

			else
			{
				sum += base[j];
				j++;
				//for (int k = 0; k < znum / 10; k++)
				//{
				zmset[i + k*10] = zombies(j);
				cout << "zombie with type " << j << " is created!" << endl;
				//}
			}
		}
	}

}



//2024.6.18
/*void Level::swallow()
{
	for (int i = 0; i < znum; i++)
	{
		if (zmset[i].getstate() || zmset[i].getdead()) continue;
			int zrow = (zmset[i].gety() - 90) / 78;
			int zcol = (zmset[i].getx() - 430+100) / 67;
			// eaters can eat enemies at most a grid away(whether there is laziness in bits or?)
			if (zcol < 8  && plset[zrow*8+zcol]->gettype() == eater + 1 && !(eaters[zrow * 8 + zcol].ddigest || eaters[zrow * 8 + zcol].eeat))
			{
				if (zmset[i].gettype() != 8&& zmset[i].gettype() != 9)
				{
					zmset[i].setstate(1);
					plset[zrow*8+zcol].action = true;
					eaters[zrow*8+zcol].eeat=true;
					plset[zrow*8+zcol].framec = 0;
					
				}
				else
				{
					if (!plset[zrow*8+zcol].action)
						plset[zrow*8+zcol].framec = 0;
					plset[zrow*8+zcol].action = true;
					zmset[i].setblood(zmset[i].getblood() - 40);
					eaters[zrow*8+zcol].swallow(2, plset[zrow*8+zcol].framec, zmset[i]);
					if (zmset[i].getblood() > 0)
					{
						plset[zrow*8+zcol].framec= (plset[zrow*8+zcol].framec+1)%20;
					}
					else
					{
						zmset[i].setdead(1);
						if (plset[zrow*8+zcol].framec < 19)
						{
							plset[zrow*8+zcol].framec++;
						}
						else
						{
							plset[zrow*8+zcol].framec = 0;
							plset[zrow*8+zcol].action = false;
						}
					}
				}
			}
			else
			{
				if (zcol < 8 && zcol>0&&plset[zrow*8+zcol-1].type == eater + 1 && !(eaters[zrow * 8 + zcol-1].ddigest || eaters[zrow * 8 + zcol-1].eeat))
				{
					if (zmset[i].gettype() != 8&& zmset[i].gettype() != 9)
					{
						zmset[i].setstate(1);
						plset[zrow*8+zcol-1].action = true;
						eaters[zrow * 8 + zcol-1].eeat = true;
						plset[zrow*8+zcol-1].framec = 0;

					}
					else
					{
						if (!plset[zrow*8+zcol-1].action)
							plset[zrow*8+zcol-1].framec = 0;
						plset[zrow*8+zcol-1].action = true;
						zmset[i].setblood(zmset[i].getblood() - 40);
						eaters[zrow * 8 + zcol-1].swallow(2, plset[zrow*8+zcol-1].framec, zmset[i]);
						if (zmset[i].getblood() > 0)
						{
							plset[zrow*8+zcol].framec = (plset[zrow*8+zcol-1].framec + 1) % 20;
						}
						else
						{
							zmset[i].setdead(1);
							zmset[i].setframe(0);
							if (plset[zrow*8+zcol-1].framec < 19)
							{
								plset[zrow*8+zcol-1].framec++;
							}
							else
							{
								plset[zrow*8+zcol-1].framec = 0;
								plset[zrow*8+zcol-1].action = false;
							}
						}
					}
				}
			}
	}

	for (int i = 0; i < 40; i++)
	{
		if (eaters[i].eeat)
		{
			eaters[i].swallow(1, zhiwu[i / 8][i % 8].framec, zmset[i]);
			if (zhiwu[i / 8][i % 8].framec < 28)
				zhiwu[i / 8][i % 8].framec++;
			else
			{
				zhiwu[i / 8][i % 8].framec = 0;
				eaters[i].eeat = false;
				eaters[i].ddigest = true;
			}
		}
		else
		{
			if (eaters[i].ddigest)
			{
				if (eaters[i].loop < 50)
				{
					eaters[i].swallow(3, zhiwu[i / 8][i % 8].framec, zmset[i]);
					zhiwu[i / 8][i % 8].framec = (zhiwu[i / 8][i % 8].framec + 1) % 20;
					if (zhiwu[i / 8][i % 8].framec == 19) {
						eaters[i].loop++;
						cout << "digestion loop adds 1!" << endl;
					}
				}
				else {
					eaters[i].loop = 0;
					eaters[i].ddigest = 0;
					zhiwu[i / 8][i % 8].action = false;
					zhiwu[i / 8][i % 8].framec = 0;
				}
			}

		}

	}
}
*/

//2024.6.21
void Level::update_probar()
{
	if (kind == 1)
	{
		putimage(80, 600, &Process);
		int length = 170 * process;
		COLORREF color = RGB(0, 255, 51);
		setfillcolor(color);
		setlinecolor(TRANSPARENT);
		fillrectangle(255 - length, 602, 255, 618);
		for (int i = 0; i < zcrowds; i++)
		{
			display_enhance(80 + 180 / zcrowds * i, 600, 20, 20, Flag);
		}
		display_enhance(80 + 180 / zcrowds * remain_crowds, 600, 20, 20, Head);
		// subtitle hint and sound effect,2024.06.22
		if (process < 1) {
			if (compare < process && timer4 < 40) {
				if (!timer4)
				{
					mciSendString("pause 75", 0, 0, 0);
					mciSendString("setaudio materials1/music/106.mp3 volume to 500", 0, 0, 0);
					mciSendString("play materials1/music/106.mp3", 0, 0, 0);
				}
				timer4++;
				cout << "timer4: " << timer4 << "compare: " << compare << endl;
				display_enhance(195, 260, 620, 100, wave);
			}
			if (timer4 >= 40) {
				compare = process;
				timer4 = 0;
				mciSendString("resume 75", 0, 0, 0);
			}
		}
		else {
			if (compare < 1) {
				timer4 = 0;
				compare = 1;
			}
			if (timer4 < 40)
			{
				if (!timer4) {
					mciSendString("pause 75", 0, 0, 0);
					mciSendString("setaudio materials1/music/36.mp3 volume to 750", 0, 0, 0);
					mciSendString("play materials1/music/36.mp3", 0, 0, 0);
				}
				timer4++;
				display_enhance(293, 260, 425, 100, last);
			}
			else {
				mciSendString("resume 75", 0, 0, 0);
			}
		}
	}
	else {
		if (kind == 6)
		{
			if (wave_signal)
			{
				if (!timer4)
				{
					mciSendString("pause 75", 0, 0, 0);
					mciSendString("setaudio materials1/music/106.mp3 volume to 500", 0, 0, 0);
					mciSendString("play materials1/music/106.mp3", 0, 0, 0);
				}
				timer4++;
				cout << "timer4: " << timer4 <<  endl;
				display_enhance(195, 260, 620, 100, wave);
				if (timer4 >= 40) 
				{
					timer4 = 0;
					wave_signal = false;
					mciSendString("resume 75", 0, 0, 0);
				}
			}
		}
	}



}


// 2024.06.22
/*void Level::squeeze()
{
	for (int i = 0; i < znum; i++)
	{
		if (zmset[i].getstate() || zmset[i].getdead()) continue;
		int zrow1 = (zmset[i].gety() - 90) / 78;
		int zcol1 = (zmset[i].getx() - 430 + 100) / 67;
		if (zcol1 < 8 && (zhiwu[zrow1][zcol1].type == melon + 1))
		{
			zhiwu[zrow1][zcol1].action = true;
			bool flag = melons[zrow1 * 8 + zcol1].squeeze();
			if (flag)
			{
				if (zmset[i].gettype() != 8 && zmset[i].gettype() != 9) {
					zmset[i].setdead(1);
					zmset[i].setframe(0);
				}
				else {
					if (zmset[i].getblood() <= 1800)
						zmset[i].setdead(1);
					else {
						zmset[i].setblood(zmset[i].getblood() - 1800);
					}
				}
				//zhiwu[zrow1][zcol1].type = 0;
				// short interval of true and false altering is supported!
				//zhiwu[zrow1][zcol1].action = false;
				//melons[zrow1 * 8 + zcol1].restore();
				//melons[zrow1 * 8 + zcol1].row = melons[zrow1 * 8 + zcol1].col = -1;
			}
		}
		else {
			if (zcol1 < 8 && zcol1>0 && zhiwu[zrow1][zcol1 - 1].type == melon + 1)
			{
				zhiwu[zrow1][zcol1 - 1].action = true;
				bool flag = melons[zrow1 * 8 + zcol1 - 1].squeeze();
				if (flag)
				{
					if (zmset[i].gettype() != 8 && zmset[i].gettype() != 9) {
						zmset[i].setdead(1);
						zmset[i].setframe(0);
					}
					else {
						if (zmset[i].getblood() <= 1800)
							zmset[i].setdead(1);
						else {
							zmset[i].setblood(zmset[i].getblood() - 1800);
						}
					}
				}
			}
			else {
				if (zcol1 < 8 && zcol1>1 && zhiwu[zrow1][zcol1 - 2].type == melon + 1)
				{
					zhiwu[zrow1][zcol1 - 2].action = true;
					bool flag = melons[zrow1 * 8 + zcol1 - 2].squeeze();
					if (flag)
					{
						if (zmset[i].gettype() != 8 && zmset[i].gettype() != 9)
							zmset[i].setdead(1);
						else {
							if (zmset[i].getblood() <= 1800)
								zmset[i].setdead(1);
							else {
								zmset[i].setblood(zmset[i].getblood() - 1800);
							}
						}
					}
				}
			}
		}
	}

	// melon dealing with multiple zombies->solution,2024.06.22
	for (int i = 0; i < 40; i++)
	{
		if (melons[i].getland())
		{
			melons[i].row = melons[i].col = -1;
			melons[i].restore();
			zhiwu[i / 8][i % 8].type = 0;
			zhiwu[i / 8][i % 8].action = 0;
		}
	}
}*/



void Level::shuffle()
{
	int pos = 0;
	vector<int> warehouse;
	for (int i = 0; i < ccount; i++)
	{
		warehouse.push_back(i + 1);
	}
	// must be put outside!
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < ccount; i++)
	{
		do {
			pos = rand() % ccount;
		} while (pos == i);
		swap(warehouse[i], warehouse[pos]);
	}
	for (int i = 0; i < 8; i++)
	{
		bar[i] = warehouse[i];
	}
}


/*void Level::drag()
{
	for (int i = 1; i < 4; i++)
	{
		for (int j = 1; j < 7; j++)
		{
			if (plset[i*8+j].type==fan+1)
			{
				bool judging2 = 0;
				for (int k = i - 1; k <= i + 1; k++)
				{
					for (int l = j - 1; l <= j + 1; l++)
					{
						if (zhiwu[k][l].zm_on)
						{
							judging2 = 1;
							break;
						}

					}
					if (judging2)
						break;
				}
				if (judging2)
				{
					cout << "within range!" << endl;
					plset[a].action = true;
					fans[(i - 1) * 6 + j - 1].drag(1);
					if (fans[(i - 1) * 6 + j - 1].get_lasting()>0)
					{
						if (fans[(i - 1) * 6 + j - 1].affecting())
						{
							cout << "within range2!" << endl;
							for (int a = 0; a < znum; a++)
							{
								if (zmset[a].getdead() || zmset[a].getstate()) continue;
								zmset[a].add_fantag(i, j);
								zmset[a].shift(i, j + 1);
							}
						}
					}
					else {
						for (int a = 0; a < znum; a++)
						{
							if (zmset[a].getdead() || zmset[a].getstate()) continue;
							zmset[a].fantag_reverse();
						}
					}
				}
				else {
					plset[a].action = false;
				}

			}
		}
	}
}*/



/*void Level::zmpos_check()
{
	for (int i = 0; i < znum; i++)
	{
		if (zmset[i].getstate() == 0 && zmset[i].getx() < 1010 - 160&&!zmset[i].getdead())
		{
			int zrow = (zmset[i].gety() - 90) / 78;// 90 is based on tests
			int zcol = (zmset[i].getx() - 330) / 67;
			plset[zrow*8+zcol].zm_on = 1;
			//cout << "zrow: " << zrow << " zcol: " << zcol << endl;
		}
	}
}*/







