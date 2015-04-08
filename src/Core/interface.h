#ifndef __INTERFACE_H_
#define __INTERFACE_H_

#define GET_INTERFACE_FUNCTION "poGetInterface"
/**
* Interface User/Computer.
* Contains all the possibles interactions of the user with the game
* Derivate it to make your own type of display for the game.
* It's a singleton. Each game should be display only once.
* The displays are pushed, then commited by a call to CommitDisplay
*/

#include <vector>
#include "Core/board.h"

class Controller;

class Interface
{
public:
    Controller * mpoController;
    void SetController(Controller *);
    virtual void SetMenuState(std::vector<std::string> const * = NULL) = 0;
    virtual void SetGameState(const Board &) = 0;
    virtual Piece::PIECE_TYPE eGetPromotionNewPiece() = 0;
    virtual void Run() = 0;
    virtual void Quit() = 0;

    virtual ~Interface()
    {
    };
};

extern "C" __declspec(dllexport) Interface * poGetInterface(Controller *);

#endif
