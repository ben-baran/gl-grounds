#pragma once

#include <vector>

class GridWalk
{
public:
	static void generateDistanceField(std::vector<std::vector<int>> &base, std::vector<std::vector<int>> &field, int x, int y);
	static void createRegions(std::vector<std::vector<int>> &field, std::vector<std::vector<int>> &regions,
							  std::vector<std::vector<std::pair<int, int>>> regionList);
};
