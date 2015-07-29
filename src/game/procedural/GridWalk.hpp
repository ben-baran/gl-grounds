#pragma once

#include <vector>

class GridWalk
{
public:
	static void generateDistanceField(std::vector<std::vector<int>> &base, std::vector<std::vector<int>> &field, int x, int y);
};
