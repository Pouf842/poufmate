#ifndef __MENU_H_
#define __MENU_H_

#include <vector>
#include "module.h"

class Menu
{
  protected :
	  std::vector<std::string> moOptions;

  public :
	Menu();
	Menu(std::vector<std::string>);

	void AddOption(std::string strOption);
	std::vector<std::string> strGetOptions() const;
	unsigned int size() const;
};

#endif
