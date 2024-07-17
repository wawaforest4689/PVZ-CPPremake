//2024.6.7
#pragma once
#include <iostream>
#include <graphics.h>
#include <stdio.h>
//#include "tools.h"
#include <ctime>
#include <mmsystem.h>
#include "zombies.h"
#include "Players.h"
#include "CPlants.h"
#include  "Pea_shooter.h"
#include "Wall_nut.h"
#include "Ice_pea_shooter.h"
#include "Eater.h"
#include "Melon.h"
#include "Cards.h"
#include "Fan.h"
#include "Firepeashooter.h"
#include "Repeater.h"
#include "Threepeater.h"
#include "bullets.h"
#include "Ice_bullets.h"
#include <cmath>
#include <vector> // due to a lack of ability, can only employ the standard vector repo for help(temperarily)
#pragma comment(lib, "winmm.lib")

using namespace std;

#define width 1010
#define height 620
#define leftedge 430
#define topedge 164
#define gridw 67
#define gridh 78
#define znum 60

class Level
{
public:
	Level(int = 0, int = 0, int = 0, int = 0, unsigned short int = 0, bool = true, bool = false, double = 0, int = 0, int = 0, int = 0, int = 0, double = 0);
	void setcrowd(int);
	void setstructure(int, int);
	void setkind(int);
	void setstatus_and_map(int);
	void settime(unsigned short int);
	double getscore();
	bool run();
	int gettime() { return huge_timer / 1000; };

private:
	void gameinit1();
	void updatewindow();
	void updategame();
	void userclick();
	void create_sunshine(int s);
	void update_sunshine();
	void collect_sunshine(ExMessage*);
	void create_zombies(int b,int r,bool l);
	void update_zombies();
	void draw_zombies();
	void attack();
	//void shoot();
	//void swallow();
	//void squeeze();
	void updatebullets();
	void collisioncheck();
	void eatcheck();
	void touchcheck();
	int getdelay2(int n);
	void display_enhance(int,int,int,int,IMAGE);
	bool file(const char*);
	void stay(IMAGE&,int,int,int,int);
	void stay_and_display(IMAGE&, int, int, int, int);
	void usertype(ExMessage&);
	void victory();
	void update_probar();
	void shuffle();
	//void drag();
	//void zmpos_check();
	int zcrowds;
	// 1 for common mode, 2 for conveyor belt mode, 3 for boss mode, 4 for pots mode, 5 for pvp(plants&&zombies) mode, 6 for challenge mode
	int kind;
	int status; //related to player progress;2024.7.1¡ª¡ªseems invalid now
	int map;
	unsigned short int standard_min;
	bool flag3;	//victory check
	bool quit;	//quitting check
	double process;
	int sunshine_left;
	int total_sunshine;
	int dead_plants;
	int total_plants;
	double score;
	int cardscool[8];
	int random;
	int random3;
	int count;
	int count3;
	int count4;
	int bound2;
	int count2;
	int bound;
	bool wave_signal;	//used in challenge mode,2024.6.30
	int bar[8];
	int huge_timer;
	//int count5;
	int count6;
	int count7;
	int record2[8][10];

	zombies* zmset = new zombies[znum];
	//2024.6.15 an "ice" intended for every zombie
	Ice ice[znum];
	Cards cards;
};

