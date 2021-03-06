#include "game.h"
#include <sstream>
#include "Movements/include_movements.h"
#include "Pieces/includePieces.h"
#include "interface.h"
#include "PoufMate.h"

using namespace std;

Game::Game(Interface * poInterface, PoufMate * poBack) : Controller(poInterface), mpoMainMenu(poBack)
{
	Initialize();
}

void Game::Initialize()
{
	// Initialize the board to a new one (in case of re-initializing)
	moBoard = Board();

	/* Initialise the positions of the kings */
	moKings[Piece::PC_WHITE] = Position(7, 4);	
	moKings[Piece::PC_BLACK] = Position(0, 4);

    InitBoard();
    moSelectedPosition.Empty();

	meCurrentPlayer = Piece::PC_WHITE;	// White moves first
	mbIsOver = false;
	mbIsWhiteCheckMate = false;
	mbIsBlackCheckMate = false;
	mbIsStaleMate = false;
	mbIsWhiteInCheck = false;
	mbIsBlackInCheck = false;

    Movement::SetBoard(&moBoard);	// Set the board for movements (@see Movement::spoBoard)
    moBoard.AddInterface(mpoInterface);
}

Game::Game(Interface * poInterface, PoufMate * poPoufMate, const Board & oBoard) : Controller(poInterface), mpoMainMenu(poPoufMate)
{
	try
	{
		moBoard = oBoard;
        moSelectedPosition.Empty();
        moBoard.AddInterface(mpoInterface);

		Position oWhiteKing;
		Position oBlackKing;

		/* Searching for the two kings to initialize moKings */
		bool bWhiteFounded = false;
		bool bBlackFounded = false;

		Movement::SetBoard(&moBoard);

		/* For each line */
		for(unsigned int i = 0; i < 8 && (!bWhiteFounded || !bBlackFounded); ++i)
		{
			/* For each column */
			for(unsigned int j = 0; j < 8 && (!bWhiteFounded || !bBlackFounded); ++j)
			{
				if(!moBoard.bIsSquareEmpty(i, j))
				{
					Piece * poCurrentPiece = moBoard.poGetPiece(i, j);

					if(poCurrentPiece->eGetType() == Piece::PT_KING)
					{
						if(poCurrentPiece->eGetColor() == Piece::PC_WHITE)
						{
							if(bWhiteFounded)
								throw exception("You can't play a party with more than one king for each player");
							else
								bWhiteFounded = true;
						}
						else
						{
							if(bBlackFounded)
								throw exception("You can't play a party with more than one king for each player");
							else
								bBlackFounded = true;
						}
						
						moKings[poCurrentPiece->eGetColor()] = Position(i, j);	// Initialize moKings for the color
					}
				}
			}
		}

		if(!bWhiteFounded || !bBlackFounded)
			throw exception("You can't play a party without a king for each player");

		meCurrentPlayer = Piece::PC_WHITE;	// White moves first
		RefreshCheckBooleans();

		if(abs(moKings[Piece::PC_WHITE].mX - moKings[Piece::PC_BLACK].mX) <= 1
		&& abs(moKings[Piece::PC_WHITE].mY - moKings[Piece::PC_BLACK].mY) <= 1)	// Kings are 1 square away
			throw exception("The kings must be more than 1 square away from each other. This game is impossible");

		if(mbIsOver)
		{
			ostringstream strOver;

			if(mbIsWhiteCheckMate)
				strOver << "White player is checkmate !" << endl;
			else if(mbIsBlackCheckMate)
				strOver << "Black player is checkmate !" << endl;
			else if(mbIsStaleMate)
				strOver << "It's a stale !" << endl;

			throw exception(strOver.str().c_str());
		}
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void Game::InitBoard()
{
    for(unsigned int i = 0; i < 8; ++i)
        for(unsigned int j = 0; j < 8; ++j)
            if(!moBoard.bIsSquareEmpty(i, j))
            {
                delete moBoard.poGetPiece(i, j);
                moBoard.SetPiece(Position(i, j), NULL);
            }

    /* Creating pawns */
    for(unsigned int i = 0; i < 8; ++i)
    {
        moBoard.SetPiece(Position(1, i), new Pawn(Piece::PC_BLACK));
        moBoard.SetPiece(Position(6, i), new Pawn(Piece::PC_WHITE));
    }

    /* Creating rooks */
    moBoard.SetPiece(Position(0, 0), new Rook(Piece::PC_BLACK));
    moBoard.SetPiece(Position(0, 7), new Rook(Piece::PC_BLACK));
    moBoard.SetPiece(Position(7, 0), new Rook(Piece::PC_WHITE));
    moBoard.SetPiece(Position(7, 7), new Rook(Piece::PC_WHITE));

    /* Creating knights */
    moBoard.SetPiece(Position(0, 1), new Knight(Piece::PC_BLACK));
    moBoard.SetPiece(Position(0, 6), new Knight(Piece::PC_BLACK));
    moBoard.SetPiece(Position(7, 1), new Knight(Piece::PC_WHITE));
    moBoard.SetPiece(Position(7, 6), new Knight(Piece::PC_WHITE));

    /* Creating bishops */
    moBoard.SetPiece(Position(0, 2), new Bishop(Piece::PC_BLACK));
    moBoard.SetPiece(Position(0, 5), new Bishop(Piece::PC_BLACK));
    moBoard.SetPiece(Position(7, 2), new Bishop(Piece::PC_WHITE));
    moBoard.SetPiece(Position(7, 5), new Bishop(Piece::PC_WHITE));

    /* Creating queens */
    moBoard.SetPiece(Position(0, 3), new Queen(Piece::PC_BLACK));
    moBoard.SetPiece(Position(7, 3), new Queen(Piece::PC_WHITE));

    /* Creating kings */
    moBoard.SetPiece(Position(0, 4), new King(Piece::PC_BLACK));
    moBoard.SetPiece(Position(7, 4), new King(Piece::PC_WHITE));
}

void Game::SwitchPlayer()
{
	meCurrentPlayer = (meCurrentPlayer == Piece::PC_WHITE ? Piece::PC_BLACK : Piece::PC_WHITE);
    cout << "Current player is " << (meCurrentPlayer == Piece::PC_WHITE ? "white" : "black") << endl;
}

bool Game::bIsCastlingPathOk(Position oPos1, Position oPos2)
{
	Piece::PIECE_COLOR eColor = moBoard.eGetSquareColor(oPos1);	// Color of the castling player
	Piece * poPiece = moBoard.poGetPiece(oPos1);
	bool bFirstMove = poPiece->bIsFirstMove();	// Keeping it to restore it after the check
	
	int iStep = (oPos1.mY > oPos2.mY ? -1 : 1);
	/* For each squares between the king and the finishing square */
	for(unsigned int i = oPos1.mY + iStep; i != oPos2.mY; i += iStep)
	{
		Position oPosInter(moKings[eColor].mX, i);	// Intermediate position

		if(moBoard.bIsSquareEmpty(oPosInter))	// If the intermediate square is empty
		{
			moBoard.MovePiece(moKings[eColor], oPosInter);	// Move the king to the intermediate square
			moKings[eColor] = oPosInter;	// Update the king position

			if(bIsInCheck(eColor))	// If the king is in check, the castling is not possible
			{
				moBoard.poGetPiece(moKings[eColor])->SetFirstMove(bFirstMove);	// Restore the bFirstMove boolean of the king
				moBoard.MovePiece(moKings[eColor], oPos1);	// Return the king to its initial position
				moKings[eColor] = oPos1;			// Restore the king's position
				return false;
			}
		}
		else
			return false;	// If the square is not empty
	}

    moBoard.MovePiece(moKings[eColor], oPos1);	// Return the king to its initial position
	moKings[eColor] = oPos1;			// Restore the king's position

	moBoard.poGetPiece(moKings[eColor])->SetFirstMove(bFirstMove);	// Restore the bFirstMove boolean of the king

	return true;	// The castling path is clear
}

bool Game::bIsPromotion(Position oPos1, Position oPos2) const
{
	Piece * oPiece = moBoard.poGetPiece(oPos1);	// Moving piece

	if(oPiece->eGetType() == Piece::PT_PAWN	// If the piece is a pawn
	&& oPos2.mX == (oPiece->eGetColor() == Piece::PC_WHITE ? 0 : 7))	// and if it reaches the other side of the board (0 for the whites, 7 for the blacks)
		return true;	// It's a promotion
	else
		return false;	// else, it's not
}

bool Game::bIsCastling(Position oPos1, Position oPos2) const
{
	if(moBoard.eGetSquareType(oPos1) == Piece::PT_KING	// If the piece is a king
	&& oPos1.mX == oPos2.mX	// and the movement is horizontal
	&& (oPos2.mY == oPos1.mY - 2 || oPos2.mY == oPos1.mY + 2))	// and of two squares
		return true;	// It's a castling move
	else
		return false;	// else, it isn't
}

/*vector<Position> Game::oGetPossibilities(unsigned int i, unsigned int j)
{
	return oGetPossibilities(Position(i, j));
}*/

vector<Position> Game::oGetPossibleMoves(const Position & oPos) throw(std::exception)
{
	try
	{
		vector<Position> oPossibilites;

	//	oPossibilites.push_back(oPos);	// The square itself is a possibility

		/* For each squares of the board */
		for(unsigned int i = 0; i < 8; ++i)
		{
			for(unsigned int j = 0; j < 8; ++j)
			{
				Position oPos2(i, j);

				if(bIsMovementCorrect(oPos, oPos2))	// If the movement is correct
				{
					try
					{
						/* Determining the type of the movement */
						Movement * poMove = NULL;

						if(bIsCastling(oPos, oPos2))
						{
							if(!bIsCastlingPathOk(oPos, oPos2))
								throw exception("Your king would be in check during castling");
							if(bIsInCheck(moBoard.eGetSquareColor(oPos)))
								throw exception("Castling is not allowed if you're in check");

							poMove = new CastlingMove(oPos, oPos2);
						}
						else if(moBoard.poGetPiece(oPos)->bIsFirstMove())
							poMove = new FirstMove(oPos, oPos2);
						else if(bIsEnPassantOk(oPos, oPos2))
							poMove = new EnPassant(oPos, oPos2, (*moHistory.rbegin()));
						else
							poMove = new Movement(oPos, oPos2);

						/* Executing the movement */
						ExecuteMovement(poMove);

						if(!bIsInCheck(moBoard.eGetSquareColor(oPos2)))	// If the player is not in check, the movement is possible
							oPossibilites.push_back(oPos2);

						UndoLastMove();	// Cancel the movement
					}
					catch(exception &)	// Catching exception for impossible movements
					{
					}
				}
			}
		}

		return oPossibilites;
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

bool Game::bIsInCheck(Piece::PIECE_COLOR eColor) const
{
	Position oKing(moKings[eColor]);	// Position of the player's king

	/* For each squares of the board */
	for(unsigned int i = 0; i < 8; ++i)
	{
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);

			// If there is a piece of the opposite color on that square
			if(!moBoard.bIsSquareEmpty(oPos) && moBoard.eGetSquareColor(oPos) != eColor)
			{
				if(bIsMovementCorrect(oPos, oKing))	// And if that piece can capture the king
					return true;					// The player is in check
			}
		}
	}

	return false;
}

bool Game::bIsCheckMate(Piece::PIECE_COLOR ePlayer)
{
	try
	{
		if(!bIsInCheck(ePlayer))	// If the player is not in check, he can't be checkmate
			return false;

		/* For each squares of the board */
		for(unsigned int i = 0; i < 8; ++i)
		{
			for(unsigned int j = 0; j < 8; ++j)
			{
				Position oPos1(i, j);

				/* If the square contains a piece of the player */
				if(!moBoard.bIsSquareEmpty(oPos1) && moBoard.eGetSquareColor(oPos1) == ePlayer)
				{
					/* For each squares of the board */
					for(unsigned int k = 0; k < 8; ++k)
					{
						for(unsigned int l = 0; l < 8; ++l)
						{
							Position oPos2(k, l);

							/* If the piece can go from the first square to the second */
							if(bIsMovementCorrect(oPos1, oPos2))
							{
								try
								{
									/* Determining the type of the movement */
									Movement * poMove = NULL;
									
									if(bIsCastling(oPos1, oPos2))
									{
										if(bIsInCheck(ePlayer))
											throw exception("Castling is not allowed if you're in check");

										if(!bIsCastlingPathOk(oPos1, oPos2))
											throw exception("Your king would be in check during castling");

										poMove = new CastlingMove(oPos1, oPos2);
									}
									else if(moBoard.poGetPiece(oPos1)->bIsFirstMove())
										poMove = new FirstMove(oPos1, oPos2);
									else if(bIsEnPassantOk(oPos1, oPos2))
										poMove = new EnPassant(oPos1, oPos2, (*moHistory.rbegin()));
									else
										poMove = new Movement(oPos1, oPos2);

									ExecuteMovement(poMove);	// Move the piece

									if(!bIsInCheck(ePlayer))	// Check if the player is still in check
									{
										UndoLastMove();		// If not, cancel the move, and return that the player is not in check
										return false;
									}

									UndoLastMove();	// Cancel the move anyway
								}
								catch(exception &)	// Catch the exception for impossible moves
								{
								}
							}
						}
					}
				}
			}
		}

		return true;	// If no moves turn the player in a non-in-check state, the player is checkmate
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void Game::CheckSelectionCoords(Position oPos) const
{	
	try
	{
		if(moBoard.bIsSquareEmpty(oPos))
			throw exception("There is no piece on this square");

		if(moBoard.eGetSquareColor(oPos) != meCurrentPlayer)
			throw exception("This piece does not belong to you");
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

bool Game::bIsMovementCorrect(Position oPos1, Position oPos2) const
{
	if((oPos1 == oPos2)	// No move
	|| (moBoard.bIsSquareEmpty(oPos1))	// No piece to move
	|| (!moBoard.bIsSquareEmpty(oPos2) && moBoard.eGetSquareColor(oPos1) == moBoard.eGetSquareColor(oPos2))	// The two pieces are on the same side
	|| (!moBoard.poGetPiece(oPos1)->bIsMovementCorrect(oPos1, oPos2, moBoard)))	// The movement is not correct for this piece
		return false;

	return true;	// If none of the precedent verifications failed, the movement is correct
}

bool Game::bIsOver() const
{
	return mbIsOver;
}

void Game::CancelLastMove()
{
    UndoLastMove();
    SwitchPlayer();
}

void Game::UndoLastMove()
{
	try
	{
		if(moHistory.size() == 0)
			throw exception("Empty history");

		Movement * oLastMovement = moHistory.back();	// Getting the last move
		oLastMovement->CancelMovement();				// Cancel it

		/* Update the kings position if necessary */
		if(oLastMovement->poGetMovingPiece()->eGetType() == Piece::PT_KING)
			moKings[oLastMovement->eGetPlayerColor()] = oLastMovement->oGetCoords1();

		delete moHistory.back();	// Destroy the last move
		moHistory.pop_back();		// Supress the pointer from the list
	}
	catch(exception & e)
	{
		cout << __FUNCTION__ << ":" << __LINE__ << endl;
		throw e;
	}
}

void Game::ExecuteMovement(Movement * poMove)
{
	/* Update kings position if necessary */
	if(poMove->poGetMovingPiece()->eGetType() == Piece::PT_KING)	// If the moving piece is a king
		moKings[poMove->poGetMovingPiece()->eGetColor()] = poMove->oGetCoords2();

	poMove->Execute();

	moHistory.push_back(poMove);
}

bool Game::bIsGameInStaleMate()
{
	/* For each squares of the board */
	for(unsigned int i = 0; i < 8; ++i)
		for(unsigned int j = 0; j < 8; ++j)
		{
			Position oPos(i, j);

			if(!moBoard.bIsSquareEmpty(oPos) && moBoard.eGetSquareColor(oPos) == meCurrentPlayer)
				if(oGetPossibleMoves(oPos).size() != 0)	// If a move is possible for the current player
					return false;
		}

	return true;
}

bool Game::bIsEnPassantOk(Position oPos1, Position oPos2) const
{
	if(moBoard.bIsSquareEmpty(oPos1)															// If there is no piece to move, or if
	|| moBoard.eGetSquareType(oPos1) != Piece::PT_PAWN												// the piece to move is not a pawn, or if
	|| abs(oPos1.mX - oPos2.mX) != 1 || abs(oPos1.mY - oPos2.mY) != 1							// the move is not a diagonal move, or if
	|| !moBoard.bIsSquareEmpty(oPos2)															// the target square is not empty, or if
	|| moBoard.bIsSquareEmpty(Position(oPos1.mX, oPos2.mY))										// the captured square is empty, or if
	|| moBoard.eGetSquareType(Position(oPos1.mX, oPos2.mY)) != Piece::PT_PAWN						// the captured piece is not a pawn, or if
	|| moBoard.eGetSquareColor(oPos1) == moBoard.eGetSquareColor(Position(oPos1.mX, oPos2.mY)))	// the captured piece is of the same color than the moving piece
		return false;	// It's not an en passant
	else
		return true;
}

Piece::PIECE_COLOR Game::eGetCurrentPlayer() const
{
	return meCurrentPlayer;
}

Position Game::oGetKingPosition(Piece::PIECE_COLOR eColor) const
{
	return moKings[eColor];
}


bool Game::bIsPlayerInCheck(Piece::PIECE_COLOR ePlayer) const
{
    if(ePlayer == Piece::PC_WHITE)
	    return mbIsWhiteInCheck;
    else
        return mbIsBlackInCheck;
}

bool Game::bIsPlayerCheckMate(Piece::PIECE_COLOR ePlayer) const
{
    if(ePlayer == Piece::PC_WHITE)
	    return mbIsWhiteCheckMate;
    else
        return mbIsBlackCheckMate;
}

bool Game::bIsStaleMate() const
{
	return mbIsStaleMate;
}

Position Game::oGetSelectedPosition() const
{
	return moSelectedPosition;
}

void Game::SetSelectedPosition(Position oPos)
{
	moSelectedPosition = oPos;
}

void Game::RefreshCheckBooleans()
{
	mbIsWhiteInCheck = bIsInCheck(Piece::PC_WHITE);
	mbIsBlackInCheck = bIsInCheck(Piece::PC_BLACK);
	mbIsWhiteCheckMate = bIsCheckMate(Piece::PC_WHITE);
	mbIsBlackCheckMate = bIsCheckMate(Piece::PC_BLACK);
	mbIsStaleMate = bIsGameInStaleMate();

	mbIsOver = mbIsWhiteCheckMate || mbIsBlackCheckMate || mbIsStaleMate;
}

void Game::GrabPiece(const Position & oPiecePosition) throw(std::exception)
{
    try
    {
		if(moBoard.bIsSquareEmpty(oPiecePosition))
			throw exception("That square is empty !");
        else if(moBoard.eGetSquareColor(oPiecePosition) != meCurrentPlayer)
			throw exception("That piece does not belong to you !");

        moSelectedPosition = oPiecePosition;
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        throw e;
    }
}

void Game::DropPiece(const Position & oDropPosition)
{
    try
    {
        if(moSelectedPosition.bIsEmpty())
            throw exception("No piece selected");

        if(oDropPosition == moSelectedPosition)
            moSelectedPosition.Empty();
        else
        {
            Movement * poNextMove;

            /* Determinate the movement's type and update poNextMove */
            if(bIsCastling(moSelectedPosition, oDropPosition))	// Castling
            {
            	if(bIsInCheck(meCurrentPlayer))
            		throw exception("Castling is not allowed if you're in check");
            
            	if(!bIsCastlingPathOk(moSelectedPosition, oDropPosition))
            		throw exception("Your king would be in check during castling");
            
            	poNextMove = new CastlingMove(moSelectedPosition, oDropPosition);
            }
            else if(bIsPromotion(moSelectedPosition, oDropPosition))	// Promotion
                poNextMove = new Promotion(moSelectedPosition, oDropPosition, mpoInterface->eGetPromotionNewPiece());
            else if(moBoard.poGetPiece(moSelectedPosition)->bIsFirstMove())	// First move
            	poNextMove = new FirstMove(moSelectedPosition, oDropPosition);
            else if(bIsEnPassantOk(moSelectedPosition, oDropPosition))
            	poNextMove = new EnPassant(moSelectedPosition, oDropPosition, (*moHistory.rbegin()));
            else
            	poNextMove = new Movement(moSelectedPosition, oDropPosition);	// Other move
            
            /* Execute the move */
            ExecuteMovement(poNextMove);
            
            /* If the move puts the player in check, it is not valid */
            if(bIsInCheck(meCurrentPlayer))
            {
            	UndoLastMove();
            	throw exception("That move puts you in check");
            }
            
            moSelectedPosition.Empty();
            SwitchPlayer();	// Next player
            
            /* If the player is checkmate, display a message and stop the game */
            if(bIsCheckMate(meCurrentPlayer))
            {
            	(meCurrentPlayer == Piece::PC_WHITE ? mbIsWhiteCheckMate : mbIsBlackCheckMate) = true;
            	mbIsOver = true;
            }
            else if(bIsGameInStaleMate())
            {
            	mbIsStaleMate = true;
            	mbIsOver = true;
            }
            else if(bIsInCheck(meCurrentPlayer))	// Display the current player as in check
            	(meCurrentPlayer == Piece::PC_WHITE ? mbIsWhiteInCheck : mbIsBlackInCheck) = true;
            
            RefreshCheckBooleans();
        }
    }
    catch(std::exception & e)
    {
        std::cout << __FUNCTION__ << ":" << __LINE__ << " : " << std::endl;
        moSelectedPosition.Empty();
        throw e;
    }
}

void Game::SelectNewPiece()
{
}

Board & Game::oGetBoard()
{
    return moBoard;
}

void Game::Quit()
{
    mpoMainMenu->Back();
}