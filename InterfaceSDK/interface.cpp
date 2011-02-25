#include "../interface.h"

using namespace std;

Interface::~Interface()
{
}

void Interface::AddMessage(string strMessage)
{
	moMessages.push_back(strMessage);
}