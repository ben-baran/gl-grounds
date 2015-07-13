#pragma once

#include <string>
#include <src/engine/Run.hpp>

class Prototype: public Run
{
public:
	Prototype(std::string title);
protected:
	void setup();
	void update(double dt);
	void cleanup();
};
