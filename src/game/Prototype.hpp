#pragma once

#include <string>
#include <src/engine/Run.hpp>

class Prototype: public Run
{
	void setup();
	void update(double dt);
	void cleanup();
};
