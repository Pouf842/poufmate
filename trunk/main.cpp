#include "game.h"

int main()
{
	try
	{
		Game oNewGame;	// Create a new game
		oNewGame.Run();	// Run the new game
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