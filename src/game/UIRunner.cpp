#include <src/ui/UIC.hpp>
#include "UIRunner.hpp"

void UIRunner::setup()
{
	WindowUIC w0 = new WindowUIC(0, 0, 0.5, 1.0, true, new ListLayout(), "Window 0"); // coordinates, resizable, layout, title
	w0.add(new CheckboxUIC("Check this"));
	for(int i = 0; i < 10; i++) w0.add(new LabelUIC("This is a label"));
	w0.add(new DropdownUIC({"Look", "at", "these", "options"}));
	w0.add(new SplitLayout(0.4));

}

void UIRunner::update(double dt)
{

}

void UIRunner::cleanup(){}
