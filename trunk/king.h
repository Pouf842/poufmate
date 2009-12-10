#ifndef __KING_H_
#define __KING_H_

#include "piece.h"
#include "position.h"

class King : public Piece
{
  public :
	King(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif