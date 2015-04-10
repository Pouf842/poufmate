#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "Core/Position.h"
#include "piece.h"
#include <vector>
#include <exception>

class Interface;

class Controller
{
protected:
    Interface * mpoInterface;
public:
    Controller();
    ~Controller();

    virtual void Start();
    virtual void Quit();
    virtual void SetMenuChoice(unsigned short) throw(std::exception);
    virtual void DropPiece(const Position &) throw(std::exception);
    virtual void GrabPiece(const Position &) throw(std::exception);
    virtual void SelectNewPiece(Piece::PIECE_COLOR, Piece::PIECE_TYPE) throw(std::exception);
    virtual void CancelLastMove();
    virtual std::vector<Position> oGetPossibleMoves(const Position &) const throw(std::exception);
    virtual Piece::PIECE_TYPE eGetNewPieceType();
};

#endif