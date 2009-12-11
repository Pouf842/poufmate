#ifndef __POSITION_H_
#define __POSITION_H_

#include <string>

class Position
{
  public :
	int mX;
	int mY;
	bool mbEmpty;
	Position();
	Position(unsigned int X, unsigned int Y);
	Position(const Position & oPos);
	Position(std::string strCoords);
	bool bIsEmpty();
	void Empty();
	Position & operator=(std::string strCoords);
	bool operator==(const Position & oPos);
	bool operator!=(const Position & oPos);
};

#endif