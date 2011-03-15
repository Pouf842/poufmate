#ifndef CHECKDECKRESULTHANDLER_H
#define CHECKDECKRESULTHANDLER_H

class CheckDeckResultHandler
{
public:
	CheckDeckResultHandler();
    virtual ~CheckDeckResultHandler() {}
    virtual void checkResult(bool result) = 0;
};

#endif // CHECKDECKRESULTHANDLER_H
