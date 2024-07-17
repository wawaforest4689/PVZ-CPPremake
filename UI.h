//2024.06.01

#pragma once
#include <string>
#include "Players.h"
#include "cursor.h"
#include "rect.h"
#include <Windows.h>
//#include "tools.h"

using namespace std;

#define button_width 50
#define button_height 25

class UI
{
public:
	UI(int=button_width, int=button_height,int=0, int=0, int=40,int=45);	//40=15+bar_height, 45=20+button_height
	~UI();
	void Draw(int);
	void editing(ExMessage&);
	void button_trigger(ExMessage&,int);
	//void transfer();
	//void self_setcolor();	//the color of the buttons, future function
	bool state();
	Players& player_locate();
	bool getchange();
	void setchange() { change = 1; };
	bool get_ruin() { return ruin; };
	void set_ruin() { ruin = false; };
	void make_fail() { success = false; };
	void music();
private:
	rect rect1;
	rect rect2;
	string text1;
	string text2;
	int button_w;
	int button_h;
	int button_x;
	int button_y;
	int distance1;
	int distance2;
	int textw1;
	int textw2;
	int edit;
	COLORREF color;
	Players current_player;
	cursor cur;
	bool success;
	bool change;
	bool ruin;
	char name[21];
	char asterrisk[21];
	char temp[21];
};

