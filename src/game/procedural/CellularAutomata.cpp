#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include "CellularAutomata.hpp"

void CellularAutomata::generateWithRules(bool **arr, int nx, int ny,
										 std::initializer_list<int> aliveRules,
										 std::initializer_list<int> deadRules,
										 int iterations, double probability,
										 int probabilityPrecision)
{
	srand(time(nullptr));
	bool arrCopy[nx][ny];
	for(int i = 0; i < nx; i++) for(int j = 0; j < ny; j++)
	{
		arr[i][j] = (rand() % probabilityPrecision) < probability * probabilityPrecision;
	}

	for(int i = 0; i < iterations; i++)
	{
		std::copy(&arr[0][0], &arr[0][0] + nx * ny, &arrCopy[0][0]);
		
		for(int x = 0; x < nx; x++) for(int y = 0; y < ny; y++)
			{
				int count = 0;
				for(int sX = -1; sX < 2; sX++) for(int sY = -1; sY < 2; sY++) if(sX != 0 || sY != 0)
						{
							int checkX = x + sX, checkY = y + sY;
							if(checkX >= 0 && checkY >= 0 && checkX < nx && checkY < ny && arrCopy[checkX][checkY]) count++;
						}
				
				if(arr[x][y])
				{
					bool satisfied = false;
					for(int rule : aliveRules) if(rule == count)
					{
						satisfied = true;
						break;
					}
					if(!satisfied) arr[x][y] = false;
				}
				else
				{
					bool satisfied = false;
					for(int rule : deadRules) if(rule == count)
					{
						satisfied = true;
						break;
					}
					if(satisfied) arr[x][y] = true;
				}
			}
	}
}
