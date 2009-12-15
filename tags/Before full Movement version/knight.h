#ifndef __KNIGHT_H_
#define __KNIGHT_H_

#include "piece.h"
#include "position.h"

class Knight : public Piece
{
  public :
	Knight(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif