#ifndef __MOVEMENT_H_
#define __MOVEMENT_H_

#include "piece.h"
#include "position.h"
#include "board.h"

class Movement
{
  protected :
    static Board * spoBoard;
	Position moPos1;
	Position moPos2;

	Piece * mpoMovingPiece;
	Piece * mpoCapturedPiece;

  public :
	Movement(Position oPos1,
			 Position oPos2);
	static void SetBoard(Board * oNewBoard);
	Position oGetCoords1() const;
	Position oGetCoords2() const;
	virtual void CancelMovement(Board &) const;
	Piece * poGetMovingPiece() const;
	Piece * poGetCapturedPiece() const;
	Piece::Color eGetPlayerColor() const;
	virtual void Execute();
};

#endif