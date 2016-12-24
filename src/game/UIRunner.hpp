#pragma once

#include <src/engine/Run.hpp>

class UIRunner: public Run
{
	void setup();
	void update(double dt);
	void cleanup();
};
