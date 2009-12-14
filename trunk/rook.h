#ifndef __ROOK_H_
#define __ROOK_H_

#include "piece.h"
#include "position.h"

class Rook : public Piece
{
  protected :
  public :
	Rook(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif