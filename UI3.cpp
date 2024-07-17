#include "UI3.h"
#include "cstdlib"

UI3::UI3()
	:challenge_start(0)
{

}

void UI3::show()
{
	challenge.setkind(6);
	challenge.setstructure(8, 11);
	srand(static_cast<unsigned int>(time(0)));
	int number = rand() % 30 + 1;
	challenge.setstatus_and_map(number);
	challenge.run();
	curr_player.up_time(challenge.gettime());
	challenge_start = false;
}


void UI3::setplayer(Players& in_player)
{
	curr_player = in_player;
}









