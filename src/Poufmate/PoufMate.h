#ifndef __POUFMATE_H_
#define __POUFMATE_H_

#include "Controller.h"

class PoufMate : public Controller
{
public:
    PoufMate();
    ~PoufMate();
    virtual void Start();
    virtual void SetMenuChoice(unsigned short sChoiceIndex) throw(std::exception);
    virtual void DropPiece(const Position & oDropPosition) throw(std::exception);
    virtual void GrabPiece(const Position & oPiecePosition) throw(std::exception);
    virtual void SelectNewPiece(Piece::PIECE_COLOR eColor, Piece::PIECE_TYPE eType) throw(std::exception);
    virtual void Escape();
    virtual std::vector<Position> oGetPossibleMoves(const Position & oPiecePosition) const throw(std::exception);
    virtual Piece::PIECE_TYPE eGetNewPieceType();
};

#endif