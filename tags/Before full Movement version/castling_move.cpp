#include "castling_move.h"
#include "board.h"

CastlingMove::CastlingMove(Coordinates oCoords1, Coordinates oCoords2, Piece * poMovingPiece) : Movement(oCoords1, oCoords2, poMovingPiece, 0)
{
}

void CastlingMove::CancelMovement(Board & oBoard) const
{
	oBoard.SetPiece(oGetCoords1(), poGetMovingPiece());
	oBoard.SetPiece(oGetCoords2(), 0);

	poGetMovingPiece()->SetFirstMove(true);

	unsigned int iXKing = (eGetPlayerColor() == Piece::WHITE ? 7 : 0);

	Piece * poTower = 0;
	switch(oGetCoords2().mY)
	{
	  case 2 :
		poTower = oBoard.poGetPiece(Coordinates(iXKing, 3));
		oBoard.SetPiece(Coordinates(iXKing, 3), 0);
		oBoard.SetPiece(Coordinates(iXKing, 7), poTower);
		poTower->SetFirstMove(true);
		break;
	  case 6 :
		poTower = oBoard.poGetPiece(Coordinates(iXKing, 5));
		oBoard.SetPiece(Coordinates(iXKing, 5), 0);
		oBoard.SetPiece(Coordinates(iXKing, 7), poTower);
		poTower->SetFirstMove(true);
		break;
	}
}