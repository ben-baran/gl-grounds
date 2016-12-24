#pragma once

#include <src/engine/Entity.hpp>
#include "UICLayout.hpp"
#include "SingleLayout.hpp"

//UI Component
class UIC: public Entity
{

public:
	UIC(double x0, double y0, double x1, double y1,
		std::string title = "Window", bool resizable = true, UICLayout *layout = new SingleLayout());
};
