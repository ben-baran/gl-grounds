#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "GridManip.hpp"

using std::vector;

int GridManip::neighborCount(std::vector<std::vector<bool>> &map, int x, int y)
{
	int nx = map.size(), ny = map[0].size(), count = 0;
	for(int sX = -1; sX < 2; sX++) for(int sY = -1; sY < 2; sY++) if(sX != 0 || sY != 0)
			{
				int checkX = x + sX, checkY = y + sY;
				if(checkX >= 0 && checkY >= 0 && checkX < nx && checkY < ny && map[checkX][checkY]) count++;
			}

	return count;
}

void GridManip::fillRandom(std::vector<std::vector<bool>> &map, double probability, int probabilityPrecision)
{
	int nx = map.size(), ny = map[0].size();
	for(int i = 0; i < nx; i++)
	{
		for(int j = 0; j < ny; j++) map[i][j] = (rand() % probabilityPrecision) < probability * probabilityPrecision;
	}
}

void GridManip::cellularGenerate(vector<vector<bool>> &map,
								 std::initializer_list<int> aliveRules,
								 std::initializer_list<int> deadRules,
								 int iterations)
{
	int nx = map.size(), ny = map[0].size();
	vector<vector<bool>> mapCopy;

	for(int i = 0; i < iterations; i++)
	{
		mapCopy = map;

		for(int x = 0; x < nx; x++) for(int y = 0; y < ny; y++)
			{
				int count = neighborCount(mapCopy, x, y);

				if(map[x][y])
				{
					bool satisfied = false;
					for(int rule : aliveRules) if(rule == count)
						{
							satisfied = true;
							break;
						}
					if(!satisfied) map[x][y] = false;
				}
				else
				{
					bool satisfied = false;
					for(int rule : deadRules) if(rule == count)
						{
							satisfied = true;
							break;
						}
					if(satisfied) map[x][y] = true;
				}
			}
	}
}

void GridManip::removeSingles(vector<vector<bool>> &map)
{
	int nx = map.size(), ny = map[0].size();
	for(int x = 0; x < nx; x++) for(int y = 0; y < ny; y++) if(neighborCount(map, x, y) == 0) map[x][y] = false;
}

void GridManip::surround(std::vector<std::vector<bool>> &map, int layers)
{
	int nx = map.size(), ny = map[0].size();

	for(int i = 0; i < nx; i++)
	{
		map[i].reserve(ny + 2 * layers);
		map[i].insert(map[i].begin(), layers, true);
		for(int j = 0; j < layers; j++) map[i].push_back(true);
	}

	map.reserve(nx + 2 * layers);
	map.insert(map.begin(), layers, vector<bool>(ny + layers * 2, true));
	for(int i = 0; i < layers; i++) map.push_back(vector<bool>(ny + layers * 2, true));
}
