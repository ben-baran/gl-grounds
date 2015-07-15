#pragma once

#include <string>

class Run
{
public:
	static void start(Run *currentRun);
protected:
	virtual void setup() = 0;
	virtual void update(double dt) = 0;
	virtual void cleanup() = 0;

	void end();
private:
	static Run *currentRun;
	static void baseUpdate(double dt);
};
