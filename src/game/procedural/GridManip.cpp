#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <queue>
#include "GridManip.hpp"

using std::vector;
using std::queue;

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

bool GridManip::unifyRegions(std::vector<std::vector<bool>> &map, double fillPerc)
{
	int nx = map.size(), ny = map[0].size();
	vector<vector<int>> regions(nx, vector<int>(ny, -1));
	vector<std::pair<int, int>> regionPoints;
	vector<int> regionCounts;

	int nRegions = 0;

	for(int i = 0; i < nx; i++) for(int j = 0; j < ny; j++) if(regions[i][j] == -1 && !map[i][j])
	{
		int count = floodFill(map, regions, i, j, nRegions);
		if(count != 0)
		{
			regionPoints.push_back(std::make_pair(i, j));
			regionCounts.push_back(count);
			nRegions++;
		}
	}

	for(int i = 0; i < nRegions; i++) if(regionCounts[i] * 1.0 / nx / ny > fillPerc)
	{
		for(int j = 0; j < nRegions; j++) if(i != j) floodFill(map, regionPoints[j].first, regionPoints[j].second, true);
		return true;
	}

	return false;
}

int GridManip::floodFill(std::vector<std::vector<bool>> &map, std::vector<std::vector<int>> &regions, int x, int y, int fill)
{
	int filled = 0;
	int nx = map.size(), ny = map[0].size();
	queue<std::pair<int, int>> floodQueue;
	floodQueue.push(std::make_pair(x, y));
	while(floodQueue.size() > 0)
	{
		auto coords = floodQueue.front();
		floodQueue.pop();
		x = coords.first;
		y = coords.second;

		if(x >= 0 && y >= 0 && x < nx && y < ny && regions[x][y] == -1 && !map[x][y])
		{
			regions[x][y] = fill;
			filled++;
			floodQueue.push(std::make_pair(x + 1, y));
			floodQueue.push(std::make_pair(x - 1, y));
			floodQueue.push(std::make_pair(x, y + 1));
			floodQueue.push(std::make_pair(x, y - 1));
		}
	}

	return filled;
}

int GridManip::floodFill(std::vector<std::vector<bool>> &map, int x, int y, bool fill)
{
	int filled = 0;
	int nx = map.size(), ny = map[0].size();
	queue<std::pair<int, int>> floodQueue;
	floodQueue.push(std::make_pair(x, y));
	while(floodQueue.size() > 0)
	{
		auto coords = floodQueue.front();
		floodQueue.pop();
		x = coords.first;
		y = coords.second;

		if(coords.first >= 0 && y >= 0 && x < nx && y < ny && map[x][y] != fill)
		{
			map[x][y] = fill;
			filled++;
			floodQueue.push(std::make_pair(x + 1, y));
			floodQueue.push(std::make_pair(x - 1, y));
			floodQueue.push(std::make_pair(x, y + 1));
			floodQueue.push(std::make_pair(x, y - 1));
		}
	}

	return filled;
}

std::pair<int, int> GridManip::emptyLoc(std::vector<std::vector<bool>> &map)
{
	int nx = map.size(), ny = map[0].size();

	while(true)
	{
		int x = rand() % nx, y = rand() % ny;
		if(!map[x][y]) return std::make_pair(x, y);
	}
}

std::pair<int, int> GridManip::emptyLocOtherQuadrant(std::vector<std::vector<bool>> &map, std::pair<int, int> &other)
{
	int nx = map.size(), ny = map[0].size(), qx = other.first * 2 / nx, qy = other.second * 2 / ny;
	int curQx = qx, curQy = qy, chosen = rand() % 3;
	if(chosen == 0)
	{
		curQx = 1 - qx;
		curQy = 1 - qy;
	}
	else if(chosen == 1) curQx = 1 - qx;
	else if(chosen == 2) curQy = 1 - qy;

	while(true)
	{
		int x = rand() % (nx / 2), y = rand() % (ny / 2);
		x += curQx * nx / 2;
		y += curQy * ny / 2;
		if(!map[x][y]) return std::make_pair(x, y);
	}
}
