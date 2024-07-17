#include "UI.h"
#include "UI2.h"
#include "UI3.h" 
//#include <vector> // due to a lack of ability, can only employ the standard vector repo for help(temperarily)

using namespace std;


HWND hwnd;
IMAGE start[80];
IMAGE logging;
IMAGE imgbg1;
IMAGE imgmenu1;
IMAGE imgmenu2;
IMAGE exit0;
IMAGE exit1;
IMAGE change1;
IMAGE change2;
IMAGE cha_card1;
IMAGE cha_card2;
IMAGE alter;
ExMessage msg2;
Players player;
//bool judge;

#define width 1010
#define height 620


// required functions
void gameinit0();
void menu(UI&, UI2&,UI3&);
//2024.06.01
void load_log(UI&);
//void font_setting();
int getdelay();
void display_enhance3(int,int,int,int,IMAGE);

int main()
{
	UI ui0;
	UI2 ui1;
	UI3 ui2;
	int timer = 0;
	bool flag2 = true;
	gameinit0(); // should be called earlier than menu
	//level.setcrowd(2);
	//level.run();
	mciSendString("open materials1/music/75.mp3 alias 75", 0, 0, 0);
	while (1)
	{
		if (ui1.get_logout()||ui0.get_ruin())
		{
			mciSendString("stop 75", 0, 0, 0);
			cleardevice();
			load_log(ui0);
			ui1.setplayer(player);
			//font_setting();
			menu(ui0,ui1,ui2);
		}
		else {
			if (ui0.getchange())
			{
				while (1)
				{
					BeginBatchDraw();
					putimage(0, 0, &alter);
					ui0.Draw(2);
					if (peekmessage(&msg2))
					{
						ui0.editing(msg2);
						ui0.button_trigger(msg2, 2);	//big trap!!!
					}
					EndBatchDraw();
					if (!ui0.getchange())
					{
						menu(ui0, ui1,ui2); 
						break;
					}
					if (ui0.get_ruin()) {
						break;
					}
				}
			}
			else {
				if (ui2.getstart())
				{
					ui2.show();
				}
				else {
					if (ui1.getback())
					{
						menu(ui0, ui1, ui2);
					}
					else {
						ui1.show();
					}
				}
			}
		}
	}
	mciSendString("close 75", 0, 0, 0);
	system("pause");
	return 0;
}


// 图形装载初始化函数
void gameinit0() 
{
	char name[128];
	for (int i = 1; i < 81; i++)
	{
		sprintf_s(name, "materials1/loading_log/loading/%d.jpg", i);
		loadimage(&start[i-1], name, width, height);
	}
	loadimage(&logging, "materials1/loading_log/log.png",width, height);
	loadimage(&imgbg1, "materials1/menu/main_menu.png", width, height);
	loadimage(&imgmenu1, "materials1/menu/menu11.png", 460, 160);
	loadimage(&imgmenu2, "materials1/menu/menu22.png", 460, 160);
	loadimage(&exit0, "materials1/menu/exit0.png", 90, 110);
	loadimage(&exit1, "materials1/menu/exit1.png", 90, 110);
	loadimage(&change1, "materials1/menu/change1.png", 364, 57);
	loadimage(&change2, "materials1/menu/change2.png", 364, 57);
	loadimage(&alter, "materials1/loading_log/alter.png", 1010, 620);
	loadimage(&cha_card1, "materials1/menu/cha_en1.png", 333, 120);
	loadimage(&cha_card2, "materials1/menu/cha_en2.png", 333, 120);

	// about 1
	hwnd = initgraph(width, height,1);

	// srand setting can be put here!(<1s can be then achieved, but maybe longer than 1s is fine)

	LOGFONT f;
	gettextstyle(&f);
	//f.lfHeight = 25;
	//f.lfWeight = 15;
	//strcpy_s(f.lfFaceName, "Segoe UI Black");
	f.lfQuality = ANTIALIASED_QUALITY; //抗锯齿效果
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	setcolor(BLACK);


}


// main menu control
void menu(UI& ui0, UI2& ui1,UI3& ui2)
{
	//IMAGE imgbg1;
	//IMAGE imgmenu1;
	//IMAGE imgmenu2;
	int flag3 = 0;
	int flag4 = 0;
	int flag5 = 0;
	int flag6 = 0;
	//loadimage(&imgbg1, "materials1/menu/main_menu.jpg", 1010, 620);
	//cout << 1;
	//loadimage(&imgmenu1, "materials1/menu/menu1.jpg", 415, 150);
	//loadimage(&imgmenu2, "materials1/menu/menu2.jpg", 415, 150);
	while (1)
	{
		BeginBatchDraw();
		// cout<<1;
		putimage(0, 0, &imgbg1);

		display_enhance3(480, 65, 460, 160, flag3 ? imgmenu1 : imgmenu2);
		display_enhance3(890, 460, 90, 110, flag4 ? exit1 : exit0);
		display_enhance3(30, 129, 364, 57, flag5 ? change2 : change1);
		display_enhance3(527, 338, 333, 120, flag6 ? cha_card2 : cha_card1);
		ExMessage msg;
		if (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x < 925 && msg.x>510 && msg.y > 65 && msg.y < 216)
			{
				flag3 = 1;
			}
			else
			{
				if (msg.message == WM_LBUTTONUP && flag3 == 1)
				{
					if (msg.x < 925 && msg.x>510 && msg.y > 65 && msg.y < 216)
					{
						ui1.setback();
						break;
					}
					else
					{
						flag3 = 0;
					}
				}
				else {
					if (msg.message == WM_LBUTTONDOWN && msg.x >= 890 && msg.x <= 890 + 90 && msg.y >= 460 && msg.y <= 460 + 110)
					{
						flag4 = 1;
					}
					else {
						if (msg.message == WM_LBUTTONUP&& flag4)
						{
							if (msg.x >= 890 && msg.x <= 890 + 90 && msg.y >= 460 && msg.y <= 460 + 110)
							{
								if (MessageBox(hwnd, "确定要退出吗？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
								{
									player.userlogout();
									ui1.set_logout();
									break;
								}
							}
							else {
								flag4 = false;
							}
						}
						else {
							if (msg.message == WM_LBUTTONDOWN && msg.x >= 30 && msg.x <= 30 + 364 && msg.y >= 129 && msg.y <= 129 + 57)
							{
								flag5 = 1;
							}
							else {
								if (msg.message == WM_LBUTTONUP && flag5)
								{
									if (msg.x >= 30 && msg.x <= 30 + 364 && msg.y >= 129 && msg.y <= 129 + 57)
									{
										ui0.setchange();
										break;
									}
									else {
										flag5 = 0;
									}
								}
								else {
									if (msg.message == WM_LBUTTONDOWN && msg.x >= 527 && msg.x <= 527 + 332 && msg.y >= 338+(msg.x-527)/6 && msg.y <= 457 - (859-msg.x)/6)
									{
										flag6 = 1;
									}
									else {
										if (msg.message == WM_LBUTTONUP && flag6)
										{
											if (msg.x >= 527 && msg.x <= 527 + 332 && msg.y >= 338 + (msg.x - 527) / 6 && msg.y <= 457 - (859 - msg.x) / 6)
											{
												ui2.setstart();
												break;
											}
											else {
												flag6 = 0;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		EndBatchDraw();
	}
}
//2024.04.01——2024.05.25 第一阶段完成（僵尸剥植物、普通豌豆射手攻击僵尸、阳光生成与积累）

//2024.06.01
void load_log(UI& ui0)
{
	ui0.set_ruin();
	ui0.make_fail();
	int timer2 = 0,timer3=0;
	int i = 0;
	// solve log out problem, 2024.6.26
	timer3=getdelay();
	while(timer2<8000)	//the original mp4 file lasts for 8 seconds
	{
		BeginBatchDraw();
		display_enhance3(0, 0, 1010,620, start[i]);
		i = (i + 1) % 80;
		cout << "i: " << i << endl;
		timer3 = timer2;
		while (timer2 - timer3 < 45)
		{
			timer2 += getdelay();
			cout << "timer2: " << timer2 << endl;
		}
		EndBatchDraw();
	}

	while (1)
	{
		BeginBatchDraw();
		putimage(0, 0, &logging);
		ui0.Draw(1);
		if (peekmessage(&msg2))
		{
			ui0.editing(msg2);
			ui0.button_trigger(msg2,1);	//big trap!!!
		}
		EndBatchDraw();
		if (ui0.state())
		{
			player = ui0.player_locate();
			break;
		}
	}
}

//2024.06.01
/*void font_setting()
{
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 25;
	f.lfWeight = 15;
	strcpy_s(f.lfFaceName, "Segoe UI Black");
	settextstyle(&f);
}
*/


int getdelay()
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
		cout << "current time: " << currenttime << endl;
		cout << "lasttime: " << lasttime << endl;
		return interval;
	}
}

// tackle with black bg problem
void display_enhance3(int n, int m, int a, int b, IMAGE input)
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


//2024.05.26-2024.06.16		（第二阶段基本完成：账户注册与登录、关卡类创建与相关内容、关卡最高得分计算与记录文件读写
// 、游戏暂停与继续、寒冰豌豆射手减速与冻结功能实现、1-5类僵尸参数调整、坚果墙与两种射手参数调整、阳光参数调整、界面播放背景音乐）


