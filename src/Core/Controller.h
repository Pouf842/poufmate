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
    Controller(Interface * = NULL);
    ~Controller();

    virtual void Start();

    /* V to C*/
    virtual void SetMenuChoice(unsigned short) throw(std::exception);
    virtual void DropPiece(const Position &) throw(std::exception);
    virtual void GrabPiece(const Position &) throw(std::exception);
    virtual void SelectNewPiece(Piece::PIECE_COLOR, Piece::PIECE_TYPE) throw(std::exception);
    virtual void CancelLastMove();
    virtual std::vector<Position> oGetPossibleMoves(const Position &) throw(std::exception);
    virtual void Quit();

    /* M to C*/
    virtual void PieceMoved(const Position &, const Position &);
    virtual void PieceRemoved(const Position &);
    virtual void PieceAdded(const Position &, Piece *);
};

#endif