#ifndef __BOARD_H_
#define __BOARD_H_

#include <iostream>
#include "square.h"
#include "position.h"

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
	bool bIsSquareEmpty(Position) const;
	void MovePiece(Position, Position);
	Piece::Color eGetSquareColor(Position) const;
	Piece * poGetPiece(Position) const;
	void SetPiece(Position, Piece * poNewPiece);
};

ostream & operator<<(ostream & os, const Board & b);

#endif