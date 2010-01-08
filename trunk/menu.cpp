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

vector<string> Menu::oGetOptions() const
{
	return moOptions;
}

unsigned int Menu::size() const
{
	return moOptions.size();
}

string Menu::operator[](unsigned int i) const
{
	return moOptions[i];
}