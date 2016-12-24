#pragma once

#include <initializer_list>
#include <vector>

class GridManip
{
public:
	static int neighborCount(std::vector<std::vector<bool>> &map, int x, int y);
	static void fillRandom(std::vector<std::vector<bool>> &map, double probability = 0.5, int probabilityPrecision = 100000);
	static void cellularGenerate(std::vector<std::vector<bool>> &map,
								 std::initializer_list<int> aliveRules,
								 std::initializer_list<int> deadRules,
								 int iterations = 5);
	static void removeSingles(std::vector<std::vector<bool>> &map);
	static void surround(std::vector<std::vector<bool>> &map, int layers);
	static bool unifyRegions(std::vector<std::vector<bool>> &map, double fillPerc = 0.3);
	static int floodFill(std::vector<std::vector<bool>> &map, std::vector<std::vector<int>> &regions, int x, int y, int fill);
	static int floodFill(std::vector<std::vector<bool>> &map, int x, int y, bool fill = true);

	static std::pair<int, int> emptyLoc(std::vector<std::vector<bool>> &map);
	static std::pair<int, int> emptyLocOtherQuadrant(std::vector<std::vector<bool>> &map, std::pair<int, int> &other);
	static std::pair<int, int> emptyLoc(std::vector<std::vector<int>> &map);
	static std::pair<int, int> emptyLocOtherQuadrant(std::vector<std::vector<int>> &map, std::pair<int, int> &other);
};
