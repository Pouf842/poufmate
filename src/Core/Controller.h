#ifndef __CONTROLLER_H_
#define __CONTROLLER_H_

#include "Core/Position.h"
#include "piece.h"
#include <vector>
#include <exception>

class Module;
class Interface;

class Controller
{
protected:
    Module *    mpoCurrentModule;
    Interface * mpoCurrentInterface;
public:
    Controller();
    ~Controller();

    virtual void Start() = 0;

    /**
     * View to Controller
     */
    virtual void SetMenuChoice(unsigned short sChoiceIndex) throw(std::exception) = 0;
    virtual void DropPiece(const Position & oDropPosition) throw(std::exception) = 0;
    virtual void GrabPiece(const Position & oPiecePosition) throw(std::exception) = 0;
    virtual void SelectNewPiece(Piece::PIECE_COLOR eColor, Piece::PIECE_TYPE eType) throw(std::exception) = 0;
    virtual void Escape() = 0;
    virtual std::vector<Position> oGetPossibleMoves(const Position & oPiecePosition) const throw(std::exception) = 0;

    /*
     * Model to Controller
     */
    virtual Piece::PIECE_TYPE eGetNewPieceType() = 0;
};

#endif