#include "interface.h"

using namespace std;

Interface * Interface::mpoInstance = NULL;

Interface::~Interface()
{
}

void Interface::AddMessage(string strMessage)
{
	moMessages.push_back(strMessage);
}