//2024.07.01¡ª¡ªUI for challenge mode level
#pragma once

#include "Level.h"
#include "Players.h"
class UI3
{
public:
	UI3();
	void show();
	void setplayer(Players&);
	void setstart() { challenge_start = true; };
	bool getstart() { return challenge_start; };
private:
	Players curr_player;
	Level challenge;
	bool challenge_start;
};

