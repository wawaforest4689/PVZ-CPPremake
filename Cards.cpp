#include "Cards.h"

Cards::Cards()
{
	//15 aims at 7.5s,60 aims at 30s,100 aims at 50s
	time_array[0] = 15;
	time_array[1] = 15;
	time_array[2] = 60;
	time_array[3] = 15;
	time_array[4] = 60;
	time_array[5] = 60;// 60
	time_array[6] = 100;
	time_array[7] = 15;// 15
	time_array[8] = 15;
	time_array[9] = 60;
	time_array[10] = 15;
	time_array[11] = 100;
	time_array[12] = 15;
	time_array[13] = 15;
	time_array[14] = 15;
	time_array[15] = 15;
	time_array[16] = 60;
	time_array[17] = 15;
}


const int* Cards::get_tarray()
{
	const int* temp=&time_array[0];
	return temp;
}

