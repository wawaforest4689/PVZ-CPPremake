#include "CPlants.h"
#include <iostream>

using namespace std;

CPlants::CPlants(int sc, int bl, int ty,int ro,int co,int fr)
	:sunshine_cost(sc),blood(bl),type(ty),row(ro),col(co),frame(fr),action(0),catched(0),zm_on(0),sacrify(0)
{

}

int CPlants::getsc()
{
	return sunshine_cost;
}

int CPlants::getbl()
{
	return blood;
}


int CPlants::gettype()
{
	return type;
}


/*void CPlants::setsc(int insc)
{
	sunshine_cost = insc;
}*/


void CPlants::setbl(int inbl)
{
	blood = inbl;
}



// tackle with black bg problem
void CPlants::display_enhance5(int n, int m, int a, int b, IMAGE& input)
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




