#ifndef __BISHOP_H_
#define __BISHOP_H_

#include "piece.h"
#include "position.h"

class Bishop : public Piece
{
  public :
	Bishop(Piece::Color);
	virtual char cGetChar() const;
	virtual bool bIsMovementCorrect(Position, Position, const Board & oBoard) const;
};

#endif