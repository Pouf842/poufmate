#include "game.h"

int main()
{
	try
	{
		Game oNewGame;
		oNewGame.Run();
	}
	catch(exception & e)
	{
		cout << "Uncatched exception : " << e.what() << endl;
	}
	catch(...)
	{
		cout << "Unknow uncatched exception" << endl;
	}
}