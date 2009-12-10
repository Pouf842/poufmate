#ifndef __PAWN_H_
#define __PAWN_H_

#include "piece.h"
#include "position.h"

class Pawn : public Piece
{
  public :
	Pawn(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif