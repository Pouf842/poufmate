#include "Core\position.h"
#include <exception>

using namespace std;

Position::Position()
{
	Empty();
}

Position::Position(unsigned int X, unsigned int Y) : mX(X), mY(Y), mbEmpty(false)
{
	if(mX > 7 || mY > 7)
		throw exception("Invalid Position");
}

Position::Position(std::string strCoords)
{
	*this = strCoords;
}

Position::Position(const Position & oPos) :	mX(oPos.mX), mY(oPos.mY), mbEmpty(oPos.mbEmpty)
{
}

bool Position::bIsEmpty() const
{
	return mbEmpty;
}

void Position::Empty()
{
	mbEmpty = true;
	mX = -1;
	mY = -1;
}

Position & Position::operator=(std::string strCoords)
{
	if(strCoords.size() < 2
	|| !isdigit(strCoords[0])
	|| !isdigit(strCoords[1]))
		throw exception(("Invalid Position string : " + strCoords).c_str());

	mX = strCoords[0] - '0';	// Convert a character to a digit
	mY = strCoords[1] - '0';

	if(mX > 7 || mY > 7)
		throw exception(("Invalid Position : " + strCoords).c_str());

	mbEmpty = false;

	return *this;
}

bool Position::operator==(const Position & oPos) const
{
	return (mX == oPos.mX && mY == oPos.mY);
}

bool Position::operator!=(const Position & oPos) const
{
	return !(*this == oPos);
}

std::string Position::ToString() const
{
	string strReturn = "";
	strReturn += '0' + mX;
	strReturn += '0' + mY;

	return strReturn;
}