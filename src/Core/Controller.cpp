#include "Controller.h"
#include <iostream>

using namespace std;

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::Start()
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

void Controller::Quit()
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

void Controller::SetMenuChoice(unsigned short sChoiceIndex) throw(exception)
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

void Controller::DropPiece(const Position & oDropPosition) throw(exception)
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

void Controller::GrabPiece(const Position & oPiecePosition) throw(exception)
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

void Controller::SelectNewPiece(Piece::PIECE_COLOR eColor, Piece::PIECE_TYPE eType) throw(exception)
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

void Controller::CancelLastMove()
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

vector<Position> Controller::oGetPossibleMoves(const Position & oPiecePosition) const throw(exception)
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}

Piece::PIECE_TYPE Controller::eGetNewPieceType()
{
    try
    {
        throw exception("This method is not implemented for this Controller");
    }
    catch(exception & e)
    {
        cout << __FILE__ << ":" << __LINE__ << " : " << endl;
        throw e;
    }
}