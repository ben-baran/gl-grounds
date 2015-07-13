#pragma once

#include <src/engine/Run.hpp>

class Prototype: public Run
{
protected:
	void setup();
	void update(double dt);
	void cleanup();
};
