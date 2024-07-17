//2024.6.7
#pragma once
#include "Players.h"
#include "Level.h"

class UI2
{
public:
	UI2(int=0,int=0,double=0);
	void show();
	void setplayer(Players&);
	bool get_logout();
	void set_logout();
	bool getback() { return back; };
	void setback() { back = false; };
	void display_enhance4(int,int,int,int,IMAGE&);
private:
	bool click();
	Players player1;
	//Level curr_level;
	int marker;
	int pos;	//default is 0, only effective in the range 1-30
	double high_sc;
	bool log_out;
	bool back;
};

