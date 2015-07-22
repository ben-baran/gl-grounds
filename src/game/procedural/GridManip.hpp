#pragma once

#include <initializer_list>
#include <vector>

class GridManip
{
public:
	static int neighborCount(std::vector<std::vector<bool>> &map, int x, int y);
	static void fillRandom(std::vector<std::vector<bool>> &map, double probability = 0.5, int probabilityPrecision = 1000);
	static void cellularGenerate(std::vector<std::vector<bool>> &map,
								 std::initializer_list<int> aliveRules,
								 std::initializer_list<int> deadRules,
								 int iterations = 5);
	static void removeSingles(std::vector<std::vector<bool>> &map);
	static void surround(std::vector<std::vector<bool>> &map, int layers);
};
