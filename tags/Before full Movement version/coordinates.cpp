#include "coordinates.h"
#include <exception>

using namespace std;

Coordinates::Coordinates()
{
	Empty();
}

Coordinates::Coordinates(unsigned int X, unsigned int Y) : mX(X), mY(Y), mbEmpty(false)
{
	if(mX > 7 || mY > 7)
		throw exception("Invalid coordinates");
}

Coordinates::Coordinates(std::string strCoords)
{
	*this = strCoords;
}

Coordinates::Coordinates(const Coordinates & oCoords)
{
	mX = oCoords.mX;
	mY = oCoords.mY;
	mbEmpty = oCoords.mbEmpty;
}

bool Coordinates::bIsEmpty()
{
	return mbEmpty;
}

void Coordinates::Empty()
{
	mbEmpty = true;
	mX = -1;
	mY = -1;
}

Coordinates & Coordinates::operator=(std::string strCoords)
{
	if(strCoords.size() != 2
	|| !isdigit(strCoords[0])
	|| !isdigit(strCoords[1]))
		throw exception(("Invalid coordinates string : " + strCoords).c_str());

	mX = strCoords[0] - '0';
	mY = strCoords[1] - '0';

	if(mX > 7 || mY > 7)
		throw exception(("Invalid coordinates : " + strCoords).c_str());

	mbEmpty = false;

	return *this;
}

bool Coordinates::operator==(const Coordinates & oCoords)
{
	return (mX == oCoords.mX && mY == oCoords.mY);
}
