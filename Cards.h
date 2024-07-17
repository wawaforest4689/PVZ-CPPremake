#pragma once

//date:2024.6.30,may be written as single mode of class?(No constructor then?)
//function:cooling down cards(taking time to recover)

class Cards
{
public:
	Cards();
	const int * get_tarray();
private:
	int time_array[30];
};

