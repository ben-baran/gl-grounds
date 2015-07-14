#pragma once

#include <string>

class Run
{
public:
	Run(std::string title);
protected:
	virtual void setup() = 0;
	virtual void update(double dt) = 0;
	virtual void cleanup() = 0;
private:
	void baseUpdate(double dt);
};
