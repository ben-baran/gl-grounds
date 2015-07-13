#pragma once

class Run
{
protected:
	virtual void setup() = 0;
	virtual void update(double dt) = 0;
	virtual void cleanup() = 0;
};
