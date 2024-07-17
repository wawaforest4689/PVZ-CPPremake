#pragma once
#include "graphics.h"
#include "zombies.h"


#define znum 60
class CPlants
{
public:
	CPlants(int sc=0, int bl=0, int ty=0,int ro=-1,int co=-1,int frame=0);
	int getsc();
	int getbl();
	int gettype();
	bool getaction() { return action; };
	//void settype(int);
	void setbl(int);
	//void setsc(int);
	void setrow(int r) { row = r; };
	void setcol(int c) { col = c; };
	void display_enhance5(int,int,int,int,IMAGE&);
	virtual void attack(zombies& zm) {};
	virtual void draw() {};
	virtual ~CPlants() {}
	bool get_sacrify() { return sacrify; };
	int frame;
	bool zm_on;
	int catched;
protected:
	int row;
	int col;
	bool action;
	bool sacrify;
private:
	int sunshine_cost;
	int blood;
	int type;
};



