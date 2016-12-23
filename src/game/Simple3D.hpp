#pragma once
#include <src/engine/Run.hpp>

class Simple3D: public Run
{
    void setup();
    void update(double dt);
    void cleanup();
};
