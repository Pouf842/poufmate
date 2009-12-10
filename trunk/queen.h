#ifndef __QUEEN_H_
#define __QUEEN_H_

#include "piece.h"
#include "position.h"

class Queen : public Piece
{
  public :
	Queen(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif