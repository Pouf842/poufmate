#ifndef __BOARD_H_
#define __BOARD_H_

#include <iostream>
#include "square.h"
#include "coordinates.h"

using namespace std;

class Board
{
  protected :
	Square moSquares[8][8];
	void SwitchPieces(Square & oFirstSquare, Square & oSecondSquare) const;

  public :
	void InterfaceOnStream(ostream &) const;
	void Init();
	bool bIsSquareEmpty(unsigned int, unsigned int) const;
	bool bIsSquareEmpty(Coordinates) const;
	void MovePiece(Coordinates, Coordinates);
	Piece::Color eGetSquareColor(Coordinates) const;
	Piece * poGetPiece(Coordinates) const;
	void SetPiece(Coordinates, Piece * poNewPiece);
};

ostream & operator<<(ostream & os, const Board & b);

#endif