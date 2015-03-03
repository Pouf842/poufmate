#include <exception>
#include "Game.h"

using namespace std;

int main()
{
	try
	{
		Game oGame;
		oGame.run();
	}
	catch(const exception & e)
	{
	}
}