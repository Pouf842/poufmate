#ifndef __POUFMATE_H_
#define __POUFMATE_H_

#include "Controller.h"

class Game;

class PoufMate : public Controller
{
protected :
    Game * mpoGame;
    std::vector<std::string> moMainMenu;
public:
    PoufMate();
    ~PoufMate();
    virtual void Start();
    virtual void SetMenuChoice(unsigned short sChoiceIndex) throw(std::exception);
    virtual void Quit();
    void Back();
};

#endif