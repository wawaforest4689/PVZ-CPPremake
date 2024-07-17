#include "UI2.h"
#include <graphics.h>

using namespace std;

#define width 1010
#define height 620

extern HWND hwnd;
IMAGE intr_and_select;
IMAGE locked;
IMAGE unlocked;
IMAGE added_map;
ExMessage msg3;

UI2::UI2(int po,int ma,double hs)
	:player1(),pos(po),marker(ma),high_sc(hs),log_out(1),back(0)
{
	loadimage(&intr_and_select, "materials1/menu/new_intr2.png", width, height);
	loadimage(&locked, "materials1/menu/locked2.png",118,120);
	loadimage(&unlocked, "materials1/menu/unlocked.png",118,120);
}


void UI2::setplayer(Players& in_player)
{
	log_out = 0;
	player1 = in_player;
}

void UI2::show()
{
	int i = 0;
	bool judge1 = 0;
	double high_sc = 0;
	//const double* progress = player1.getprogress();
	LOGFONT f;
	gettextstyle(&f);
	f.lfHeight = 30;
	f.lfWeight = 10;
	strcpy_s(f.lfFaceName, "Segoe UI Black");
	settextstyle(&f);
	setcolor(BLACK);
	cleardevice();
	mciSendString("play 75 repeat", 0, 0, 0);
	for (; i < 30; i++)
	{
		if (player1.getprogress()[i] == 0)
		{
			break;
			//display_enhance4(770, 240, 118, 120, locked);
		}
	}
	char name[11] = {'\0'};
	char text[35];
	player1.getname().copy(name, player1.getname().size());

	if (i != 0)
	{
		marker = pos = i;
		sprintf_s(text, sizeof(text), "materials1/scissored_bg/%d.png", pos);
		loadimage(&added_map, text, 78, 60);
	}
	else
	{
		marker = 0;
		pos = 1;
		//display_enhance4(770, 240, 118, 120, locked);
		//outtextxy(813, 87 + 240, "1 - 1");
	}
	while (1)
	{
		BeginBatchDraw();
		display_enhance4(0, 0, width, height, intr_and_select);
		outtextxy(550 - textwidth(player1.getname().c_str()) / 2, 564 - 2, name);

		//**--2024.6.26--**
		setfillcolor(RED);
		fillrectangle(923, 108, 923 + 75, 108 + 40);
		outtextxy(923 + 14, 108 + 5, "Back");
		//**--		   --**
	
		if (click())
			break;
		if (pos < marker + 1 && pos>0)
		{
			high_sc = player1.getprogress()[pos - 1];
			sprintf_s(text, sizeof(text), "Highest score: %.2f", high_sc);
			outtextxy(750, 450 - 7, text);
			display_enhance4(770, 240, 118, 120, unlocked);
			display_enhance4(790, 248, 78, 60, added_map);
			sprintf_s(text, sizeof(text), "%d - %d", (pos - 1) / 10 + 1, (pos - 1) % 10 + 1);
			outtextxy(813-10, 78 + 240, text);
		}
		if (pos > marker && pos < 31)
		{
			sprintf_s(text, sizeof(text), "%d - %d", (pos-1) / 10 + 1, (pos-1) % 10 + 1);
			display_enhance4(770, 240, 118, 120, locked);
			outtextxy(813-10, 78 + 240, text);
		}
		EndBatchDraw();
	}
}

// click check to skim levels
//2024.6.8
bool UI2::click()
{
	char text[35];
	//msg3 = getmessage(EX_KEY | EX_MOUSE);
	if (peekmessage(&msg3))
	{
		if (msg3.message == WM_LBUTTONDOWN)
		{
			if (msg3.x <= 728 + 17 && msg3.x >= 728 - 17 && msg3.y <= 300 + 17 && msg3.y >= 300 - 17)
			{
				if (pos > 1 && pos <= marker + 1)
				{
					pos--;
					//high_sc = player1.getprogress()[pos - 1];
					sprintf_s(text, sizeof(text), "materials1/scissored_bg/%d.png", pos);
					loadimage(&added_map, text, 78, 60);
					//sprintf_s(text, sizeof(text), "Highest score: %.2f", high_sc);
					//outtextxy(750, 450 - 7, text);
					//display_enhance4(770, 240, 118, 120, unlocked);
					//display_enhance4(770, 240, 78, 58, added_map);
					//sprintf_s(text, sizeof(text), "%d - %d", (pos - 1) / 10 + 1, (pos - 1) % 10 + 1);
					//outtextxy(813, 87 + 240, text);
				}
				if (pos<31 && pos>marker + 1)
				{
					pos--;
					//sprintf_s(text, sizeof(text), "%d - %d", (pos-1) / 10 + 1, (pos-1) % 10 + 1);
					//display_enhance4(770, 240, 118, 120, locked);
					//outtextxy(813, 87 + 240, text);
				}
			}
			if (msg3.x <= 932 + 17 && msg3.x >= 932 - 17 && msg3.y <= 300 + 17 && msg3.y >= 300 - 17)
			{
				if (pos > marker - 1 && pos < 30)
				{
					pos++;
					//sprintf_s(text, sizeof(text), "%d - %d", (pos-1) / 10 + 1, (pos-1) % 10+1);
					//display_enhance4(770, 240, 118, 120, locked);
					//outtextxy(813, 87 + 240, text);
				}
				if (pos > 0 && pos < marker)
				{
					pos++;
					//high_sc = player1.getprogress()[pos - 1];
					sprintf_s(text, sizeof(text), "materials1/scissored_bg/%d.png", pos);
					loadimage(&added_map, text, 78, 60);
					//sprintf_s(text, sizeof(text), "Highest score: %.2f", high_sc);
					//outtextxy(750, 450 - 7, text);
					//display_enhance4(770, 240, 118, 120, unlocked);
					//display_enhance4(770, 240, 78, 58, added_map);
					//sprintf_s(text, sizeof(text), "%d - %d", (pos - 1) / 10 + 1, (pos - 1) % 10 + 1);
					//outtextxy(813, 87 + 240, text);
				}
			}
			if (msg3.x >= 923 && msg3.x <= 923 + 75 && msg3.y >= 108 && msg3.y <= 108 + 40)
			{
				back = true;
				return true;
			}
		}
		if (msg3.message == WM_KEYDOWN && msg3.vkcode == VK_RETURN)
		{
			cout << "pos: " << pos << endl;
			if (pos <= marker + 1)
			{
				Level curr_level;
				curr_level.setcrowd(pos / 4 + 2);
				//const int comp2[10] = { 0,9,14,18,20,20,18,14,9,0 };
				const int comp[8] = { 0,9,14,18,20,20,18,14 };
				int hard = (pos % 4 + 1) * (comp[pos / 4] / 4) + comp[pos / 4] % 4;
				curr_level.setkind(1);
				curr_level.setstructure(pos/4+1,hard);
				//curr_level.setkind(1);
				curr_level.setstatus_and_map(pos);
				curr_level.settime(pos / 2 + 3);
				mciSendString("stop 75", 0, 0, 0);
				if (curr_level.run())
				{
					if (player1.getprogress()[pos - 1] < curr_level.getscore())
						player1.quit_and_save(pos - 1, curr_level.getscore());
					marker++;
					pos++;
				}
				// no matter quitting or passing
				return true;
			}
		}
	}
	return false;
}


// tackle with black bg problem
void UI2::display_enhance4(int n, int m, int a, int b, IMAGE& input)
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


bool UI2::get_logout()
{
	cout << "log_out: " << log_out<<endl;
	return log_out;
}


void UI2::set_logout()
{
	log_out = true;
}

