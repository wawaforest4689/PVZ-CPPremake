#include <graphics.h>

//#pragma once
#ifndef ZOMBIES_H
#define ZOMBIES_H

class zombies
{
public:
	zombies(int=1);
	zombies(const zombies&);
	//zombies();
	//~zombies();
	int getx();
	int gety() const;
	int getframe();
	bool getstate() const;
	int getspeed() const;
	int recoverspeed();
	void walk();
	void eat();
	//void idle();
	void die();
	//void superdie();
	void setx(int);
	void sety(int);
	void setspeed(int);
	void setstate(bool);
	void setframe(int);
	void setdiff(int);
	void harmcut();
	void harmrecover();
	void zeroharm();
	int gettype();
	int getdiff();
	void setblood(int);
	int getblood();
	int getharm();
	bool getdead();
	void setdead(bool);
	void seteat(bool);
	void setcolor(int);
	void setfrozen(bool);
	void recoverblood();
	int getcolor();
	bool getfrozen();
	bool geteat();
	bool get_iresist();
	bool get_tresist();
	void shift(int r, int c);	//used for special plants like fans
	void add_fantag(int r,int c);
	void fantag_reverse(int);
private:
	int type;
	int x;
	int y;
	int dy;
	int dx;
	int frame;
	bool unused;
	int speed;
	int tiny_diff2;
	int blood;
	int harm;
	int color;
	bool frozen;
	bool ice_resist;
	bool tempt_resist;
	bool dead;
	bool eating;
	bool heavy;
	bool fan_tag;
};

#endif