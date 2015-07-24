#include <src/engine/util/Res.hpp>
#include "SolidMarchingSquares.hpp"

using std::vector;

int SolidMarchingSquares::attributes[] = {3, 3};

void SolidMarchingSquares::constructVAO()
{

}

SolidMarchingSquares::SolidMarchingSquares(vector<vector<bool>> &baseMap, int nx, int ny,
										   double startX, double startY, double cellWidth, double cellHeight,
										   float r, float g, float b, double layer)
	: nx(nx + 1)
	, ny(ny + 1)
	, startX(startX)
	, startY(startY)
	, cellWidth(cellWidth)
	, cellHeight(cellHeight)
	, r(r)
	, g(g)
	, b(b)
{
	map = vector<vector<int>>(nx + 1, vector<int>(ny + 1, 0));

	for(int i = 0; i <= nx; i++) for(int j = 0; j <= ny; j++)
	{
		int val = 0;
		if(i > 0 && j > 0) val &= (1 << 0) * baseMap[i - 1][j - 1];
		if(i < nx && j > 0) val &= (1 << 1) * baseMap[i][j - 1];
		if(i < nx && j < ny) val &= (1 << 2) * baseMap[i][j];
		if(i > 0 && j < ny) val &= (1 << 3) * baseMap[i - 1][j];
		map[i][j] = val;
	}
	constructVAO();
	shader = Res::loadShader("res/shader/simple/color");
}

SolidMarchingSquares::~SolidMarchingSquares()
{
	delete vao;
}

void SolidMarchingSquares::setLayer(double layer)
{
	Renderable::setLayer(layer);
}

void SolidMarchingSquares::render()
{

}

void SolidMarchingSquares::render(glm::mat4 transformMatrix)
{

}

Collider &SolidMarchingSquares::provideCollider()
{
	return <#initializer#>;
}
