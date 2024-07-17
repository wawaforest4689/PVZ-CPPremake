#include "UI.h"
extern HWND hwnd;

UI::UI(int w2, int h2,int x2, int y2, int d1,int d2)
	:current_player(),rect1(), rect2(), cur(0,0,1,rect1.height-4),button_w(w2), button_h(h2),button_x(x2), button_y(y2), distance1(d1)
	,distance2(d2), text1(""),text2(""), textw1(0), textw2(0), edit(0), color(RGB(255, 0, 0)),success(false),change(0),ruin(false)
{
	for (int i = 0; i < 20; i++)
	{
		name[i] = '\0' ;
		temp[i] = '\0';
		asterrisk[i] = '*';
	}
	name[20] = '\0';
	temp[20] = '\0';
	asterrisk[20] = '\0';
	/*mciSendString("open materials1/loading_log/styping.mp3 alias sty", 0, 0, 0);
	mciSendString("setaudio sty volume to 800", 0, 0, 0);
	mciSendString("open materials1/loading_log/bell1.mp3 alias bell1", 0, 0, 0);
	mciSendString("setaudio bell volume to 900", 0, 0, 0);
	mciSendString("open materials1/loading_log/delete.mp3 alias del", 0, 0, 0);
	mciSendString("setaudio del volume to 1000", 0, 0, 0);*/
}

void UI::Draw(int n)
{
	rect1.setxy(404, 245);
	rect2.setxy(404, 245 + distance1);
	button_x = rect1.x+75;
	button_y = rect2.y + 40;
	setlinecolor(BLACK);
	settextstyle(20, 0, "楷体");
	//setcolor(BLACK);
	//setbkmode(TRANSPARENT);
	if (n == 1)
	{
		rect1.draw();
		rect2.draw();
		setfillcolor(color);
		fillrectangle(button_x, button_y, button_x + button_w, button_y + button_h);
		fillrectangle(button_x, button_y + distance2, button_x + button_w, button_y + distance2 + button_h);
		outtextxy((int)(button_x), (int)(button_y), "注册");
		outtextxy((int)(button_x), (int)(button_y + distance2), "登录");
	}
	else {
		if (n == 2)
		{
			rect1.draw();
			rect2.draw();
			setfillcolor(color);
			fillrectangle(button_x, button_y, button_x + button_w, button_y + button_h);
			fillrectangle(button_x, button_y + distance2, button_x + button_w, button_y + distance2 + button_h);
			outtextxy((int)(button_x), (int)(button_y), "修改");
			outtextxy((int)(button_x), (int)(button_y + distance2), "销毁");
		}
	}
	outtextxy(rect1.x + 5, rect1.y + 2,"用户名");
	outtextxy(rect2.x + 5, rect2.y + 2, "密码");
	// dynamic showing section
	textw1 = textwidth(text1.c_str());
	textw2 = textwidth(text2.c_str());
	switch (edit)
	{
	case 1:
		cur.setxy(rect1.x + 70 + textw1, rect1.y + 2);
		cur.draw();
		break;
	case 2:
		cur.setxy(rect2.x + 70 + textw2, rect2.y + 2);

		cur.draw();
		break;
	}
	text1.copy(name, text1.size());
	name[text1.size()] = '\0';
	outtextxy(rect1.x + 70, rect1.y + 2, name);
	strncpy_s(temp, asterrisk, text2.size());
	temp[text2.size()] = '\0';
	outtextxy(rect2.x + 70, rect2.y + 2, temp);
}


void UI::editing(ExMessage& msg)
{
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
		if (rect1.in_edit(msg))
		{
			edit = 1;
			rect2.restorecolor();
		}
		if (rect2.in_edit(msg))
		{
			edit = 2;
			rect1.restorecolor();
		}
		/*else {
			edit = 0;
			rect1.restorecolor();
			rect2.restorecolor();
			
		}*/
		break;
	case WM_CHAR:
		if (edit == 1)
		{
			switch (msg.ch) {
			case '\b':
				if (!text1.empty())
				{
					text1.pop_back();
					mciSendString("play materials1/loading_log/delete.mp3", 0, 0, 0);
					cout << "del" << endl;
				}
				else {
					mciSendString("play materials1/loading_log/bell1.mp3", 0, 0, 0);
				}
				break;	//very necessary here to avoid a small error
			case '\r':
			case '\n':
				edit = 0;
				rect1.restorecolor();
				break;
			default:
				text1 += msg.ch;
				mciSendString("play materials1/loading_log/styping.mp3", 0, 0, 0);
				break;
			}
		}
		if (edit == 2)
		{
			switch (msg.ch) {
			case '\b':
				if (!text2.empty())
				{
					text2.pop_back();
					mciSendString("play materials1/loading_log/delete.mp3", 0, 0, 0);
				}
				else {
					mciSendString("play materials1/loading_log/bell1.mp3", 0, 0, 0);
				}
				break;
			case '\r':
			case '\n':
				edit = 0;
				rect2.restorecolor();
				break;
			default:
				text2 += msg.ch;
				mciSendString("play materials1/loading_log/styping.mp3", 0, 0, 0);
				break;
			}
		}
		music();
		break;
	}
}

void UI::button_trigger(ExMessage& msg,int n)
{
	//cout << (msg.message==WM_LBUTTONDOWN)<<" "<<msg.x<<" "<<msg.y<<endl;
	if (n == 1)
	{
		if (msg.message == WM_LBUTTONDOWN&&msg.x >= button_x && msg.x <= button_x + button_w && msg.y >= button_y && msg.y <= button_y + button_h )
		{
			cout << "Button is triggered!" << endl;
			if (!text1.empty() && !text2.empty())
			{
				if (MessageBox(hwnd, "是否确定注册？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					cout << "Begin registering!" << endl;
					if (!current_player.userregister(text1, text2))
					{
						text1.clear();
						text2.clear();
					}
					else
					{
						MessageBox(hwnd, "注册成功", "提示", MB_OK | MB_ICONINFORMATION);
						text1.clear();
						text2.clear();
					}
				}
			}
			else
			{
				MessageBox(hwnd, "用户名或密码不能为空", "提示", MB_OK | MB_ICONWARNING);
				text1.clear();
				text2.clear();
			}
		}

		if (msg.message == WM_LBUTTONDOWN&&msg.x >= button_x && msg.x <= button_x + button_w && msg.y >= button_y + distance2 && msg.y <= button_y + distance2 + button_h)
		{
			if (!text1.empty() && !text2.empty())
			{
				if (MessageBox(hwnd, "是否确定登录？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					if (current_player.userlogin(text1, text2).getname().empty())
					{
						text1.clear();
						text2.clear();
						cout << "Unknown account" << endl;
					}
					else {
						MessageBox(hwnd, "登录成功", "提示", MB_OK | MB_ICONINFORMATION);
						text1.clear();
						text2.clear();
						cout << "empty? " << current_player.getname() << endl;
						success = true;
					}
				}
			}
			else
				{
					MessageBox(hwnd, "用户名或密码不能为空", "提示", MB_OK | MB_ICONERROR);
					text1.clear();
					text2.clear();
				}
		}
	}
	else {
		if (n == 2)
		{
			if (msg.message == WM_LBUTTONDOWN&&msg.x >= button_x && msg.x <= button_x + button_w && msg.y >= button_y && msg.y <= button_y + button_h )
			{
				cout << "Button is triggered!" << endl;
				if (!text1.empty() && !text2.empty())
				{
					if (MessageBox(hwnd, "是否确定修改？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						cout << "Begin changing!" << endl;
						if (!current_player.userchange(text1, text2))
						{
							text1.clear();
							text2.clear();
						}
						else
						{
							MessageBox(hwnd, "修改成功", "提示", MB_OK | MB_ICONINFORMATION);
							text1.clear();
							text2.clear();
						}
					}
				}
				else
				{
					MessageBox(hwnd, "用户名或密码不能为空", "提示", MB_OK | MB_ICONWARNING);
					text1.clear();
					text2.clear();
				}
			}
			if (msg.message == WM_LBUTTONDOWN && msg.x >= button_x && msg.x <= button_x + button_w && msg.y >= button_y+distance2 && msg.y <= button_y + distance2+button_h)
			{
				cout << "Button is triggered!" << endl;
				if (MessageBox(hwnd, "是否确定销毁？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
				{
					if (MessageBox(hwnd, "销毁后不能还原，请再次确认？", "提示", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						cout << "Begin deleting!" << endl;
						text1.clear();
						text2.clear();
						current_player.userdelete();
						
					}
				}
			}

			if (msg.message == WM_LBUTTONDOWN && msg.x >= 90 && msg.x <= 151 && msg.y >= 550 && msg.y <= 583)
			{
				change = 0;
			}
		}
	}
}


bool UI::state()
{
	return success;
}


Players& UI::player_locate()
{
	return current_player;
}


bool UI::getchange()
{
	return change;
}





void UI::music()
{
	mciSendString("seek materials1 / loading_log / styping.mp3 to start", 0, 0, 0);
	mciSendString("seek materials1 / loading_log / delete.mp3 to start", 0, 0, 0);
	mciSendString("seek materials1 / loading_log / bell1.mp3 to start", 0, 0, 0);
	mciSendString("stop materials1 / loading_log / styping.mp3", 0, 0, 0);
	mciSendString("stop materials1 / loading_log / delete.mp3", 0, 0, 0);
	mciSendString("stop materials1 / loading_log / bell1.mp3", 0, 0, 0);
}


UI::~UI()
{
	/*mciSendString("close sty", 0, 0, 0);
	mciSendString("close del", 0, 0, 0);
	mciSendString("close bell1", 0, 0, 0);*/
}



