#ifndef __COORDINATES_H_
#define __COORDINATES_H_

#include <string>

class Coordinates
{
  public :
	int mX;
	int mY;
	bool mbEmpty;
	Coordinates();
	Coordinates(unsigned int X, unsigned int Y);
	Coordinates(const Coordinates & oCoords);
	Coordinates(std::string strCoords);
	bool bIsEmpty();
	void Empty();
	Coordinates & operator=(std::string strCoords);
	bool operator==(const Coordinates & oCoords);
};

#endif