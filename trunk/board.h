#ifndef __BOARD_H_
#define __BOARD_H_

#include <iostream>
#include "square.h"

using namespace std;

class Board
{
  protected :
	Square moSquares[8][8];
	void SwitchPieces(Square & oFirstSquare, Square & oSecondSquare) const;

  public :
	void InterfaceOnStream(ostream &) const;
	void Init();
	bool bIsSquareEmpty(unsigned int X, unsigned int Y) const;
	void MovePiece(unsigned int X1, unsigned int Y1, unsigned int X2, unsigned int Y2);
	Piece::Color eGetSquareColor(unsigned int X, unsigned int Y) const;
	Piece * poGetPiece(unsigned int X, unsigned int Y) const;
	void SetPiece(unsigned int X, unsigned int Y, Piece * poNewPiece);
};

ostream & operator<<(ostream & os, const Board & b);

#endif