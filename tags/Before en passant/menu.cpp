#include "menu.h"
#include <string>
#include <vector>

using namespace std;

Menu::Menu()
{
}

void Menu::AddOption(string strOption)
{
	moOptions.push_back(strOption);
}

vector<string> Menu::strGetOptions() const
{
	return moOptions;
}

unsigned int Menu::size() const
{
	return moOptions.size();
}