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
    virtual void Quit();
};

#endif