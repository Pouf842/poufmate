#ifndef __ENTRY_H_
#define __ENTRY_H_

#include <string>
#include "Pieces\piece.h"

class Position;


class Entry
{
  public:
	/**
	 * Type of entries
	 */
	enum ENTRY_TYPE
	{
		ET_COMMAND=0,
		ET_POSITION,
		ET_PIECE,
	};

	enum ENTRY_COMMAND
	{
		EC_CANCEL_MOVE=0,
		EC_RESET_GAME,
		EC_STOP_GAME,
		EC_QUIT_GAME,

		/** Edition only **/
		EC_ONE_PLAYER_GAME,
		EC_TWO_PLAYERS_GAME,

		EC_NONE,
	};

	Entry();
	/*
	 * Constructor for a command type entry
	 */
	Entry(ENTRY_COMMAND eCommand);
	
	/*
	 * Constructor for a position type entry
	 */
	Entry(Position oPosition);

	/**
	 * Constructor for a piece type entry
	 */
	Entry(Piece::PIECE_TYPE, Piece::PIECE_COLOR);
	virtual ~Entry();

	bool bIsCommand() const;
	bool bIsPiece() const;
	Position oGetPos() const;
	ENTRY_COMMAND eGetCommand() const;
	Piece::PIECE_TYPE  eGetPieceType() const;
	Piece::PIECE_COLOR eGetPieceColor() const;

  protected :
	Position moPos;
	Piece::PIECE_TYPE mePieceType;
	Piece::PIECE_COLOR mePieceColor;
	bool mbIsCommand;
	bool mbIsPiece;
	ENTRY_COMMAND meCommand;
};

#endif