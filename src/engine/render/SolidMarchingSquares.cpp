#include <src/engine/util/Res.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "SolidMarchingSquares.hpp"
#include <src/engine/physics/RectangleCollider.hpp>

using std::vector;

inline std::pair<double, double> mp(double a, double b)
{
	return std::make_pair(a, b);
};

int SolidMarchingSquares::attributes[] = {3, 3};

std::vector<std::vector<std::pair<double, double>>> SolidMarchingSquares::partCoordinates
{
		{},
		{mp(0.0, 1.0), mp(0.0, 0.5), mp(0.5, 1.0)},
		{mp(0.5, 1.0), mp(1.0, 0.5), mp(1.0, 1.0)},
		{mp(0.0, 1.0), mp(0.0, 0.5), mp(1.0, 0.5), mp(1.0, 1.0)},
		{mp(0.5, 0.0), mp(1.0, 0.5), mp(1.0, 0.0)},
		{mp(0.0, 1.0), mp(0.0, 0.5), mp(0.5, 1.0), mp(0.5, 0.0), mp(1.0, 0.5), mp(1.0, 0.0)},
		{mp(0.5, 1.0), mp(1.0, 1.0), mp(1.0, 0.0), mp(0.5, 0.0)},
		{mp(0.0, 0.5), mp(0.0, 1.0), mp(1.0, 1.0), mp(1.0, 0.0), mp(0.5, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 0.5), mp(0.5, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 1.0), mp(0.5, 1.0), mp(0.5, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 0.5), mp(0.5, 0.0), mp(0.5, 1.0), mp(1.0, 1.0), mp(1.0, 0.5)},
		{mp(0.0, 0.0), mp(0.0, 1.0), mp(1.0, 1.0), mp(1.0, 0.5), mp(0.5, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 0.5), mp(1.0, 0.5), mp(1.0, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 1.0), mp(0.5, 1.0), mp(1.0, 0.5), mp(1.0, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 0.5), mp(0.5, 1.0), mp(1.0, 1.0), mp(1.0, 0.0)},
		{mp(0.0, 0.0), mp(0.0, 1.0), mp(1.0, 1.0), mp(1.0, 0.0)}
};

std::vector<std::vector<int>> SolidMarchingSquares::partIndices
{
		{},
		{0, 1, 2},
		{0, 1, 2},
		{0, 1, 2, 2, 3, 0},
		{0, 1, 2},
		{0, 1, 2, 3, 4, 5},
		{0, 1, 2, 2, 3, 0},
		{0, 1, 2, 0, 2, 3, 0, 3, 4},
		{0, 1, 2},
		{0, 1, 2, 2, 3, 0},
		{0, 1, 2, 3, 4, 5},
		{0, 1, 2, 0, 2, 3, 0, 3, 4},
		{0, 1, 2, 2, 3, 0},
		{0, 1, 2, 0, 2, 3, 0, 3, 4},
		{0, 1, 2, 0, 2, 3, 0, 3, 4},
		{0, 1, 2, 2, 3, 0}
};

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
	delete vao;
	constructVAO();
}

void SolidMarchingSquares::render()
{
	shader->use();
	vao->draw();
}

void SolidMarchingSquares::render(glm::mat4 transformMatrix)
{
	shader->use();
	glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
	vao->draw();
}

Collider &SolidMarchingSquares::provideCollider()
{
	return *(new RectangleCollider(0.0, 0.0, 0.0, 0.0));
}
