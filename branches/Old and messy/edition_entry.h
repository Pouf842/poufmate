#ifndef __EDITION_ENTRY_H_
#define __EDITION_ENTRY_H_

#include "piece.h"
#include <string>

class EditionEntry
{
  public:
	EditionEntry(std::string strCommand);
	EditionEntry(Position, Piece::PieceType eType, Piece::Color eColor = Piece::WHITE);
	virtual ~EditionEntry();

	bool bIsCommand();
	std::string strGetCommand();
	Piece::PieceType eGetPieceType();
	Piece::Color eGetPieceColor();
	Position oGetPosition();

  protected :
	Piece::PieceType meNewPieceType;
	Piece::Color meNewPieceColor;
	Position moNewPiecePosition;
	bool mbIsCommand;
	std::string mstrCommand;
};

#endif