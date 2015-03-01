#ifndef __CLOCK_H_
#define __CLOCK_H_

class Clock
{
protected :
	float iBegin;
	float iEnd;
public :
	void start();
	void stop();
	void newFrame();
	float dt();
};

#endif