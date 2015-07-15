#pragma once

#include <src/engine/Run.hpp>

class TestRunner: public Run
{
	void setup();
	void update(double dt);
	void cleanup();
};
