#pragma once

#include <initializer_list>
#include <vector>

class CellularAutomata
{
public:
	static void generateWithRules(std::vector<std::vector<bool>> &map, int nx, int ny,
								  std::initializer_list<int> aliveRules,
								  std::initializer_list<int> deadRules,
								  int iterations = 5, double probability = 0.45,
								  int probabilityPrecision = 1000);
};
