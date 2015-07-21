#include <src/engine/util/Res.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/engine/physics/RectangleCollider.hpp>
#include "SolidGrid.hpp"

int SolidGrid::attributes[] = {3, 3};

SolidGrid::SolidGrid(vector<vector<bool>> &map, int nx, int ny,
					 double startX, double startY, double cellWidth, double cellHeight,
					 float r, float g, float b, double layer)
{
	Renderable::setLayer(layer);

	int cellCount = 0;
	for(int i = 0; i < nx; i++) for(int j = 0; j < ny; j++) if(map[i][j]) cellCount++;

	int offset = 0;
	GLfloat vertices[24 * cellCount];
	GLuint indices[6 * cellCount];
	for(int i = 0; i < nx; i++) for(int j = 0; j < ny; j++) if(map[i][j])
	{
		indices[offset / 4]     = offset / 6;
		indices[offset / 4 + 1] = indices[offset / 4 + 3] = offset / 6 + 1;
		indices[offset / 4 + 2] = indices[offset / 4 + 5] = offset / 6 + 3;
		indices[offset / 4 + 4] = offset / 6 + 2;

		double x = startX + i * cellWidth, y = startY + j * cellHeight;

		vertices[0 + offset] = vertices[6 + offset] = x + cellWidth;
		vertices[1 + offset] = vertices[19 + offset] = y + cellHeight;
		vertices[12 + offset] = vertices[18 + offset] = x;
		vertices[7 + offset] = vertices[13 + offset] = y;

		for(int i = 0; i < 4; i++)
		{
			vertices[i * 6 + 2 + offset] = (float) getLayer();
			vertices[i * 6 + 3 + offset] = r;
			vertices[i * 6 + 4 + offset] = g;
			vertices[i * 6 + 5 + offset] = b;
		}

		offset += 24;
	}

	vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);
	shader = Res::loadShader("res/shader/simple/color");
}

void SolidGrid::render()
{
	shader->use();
	vao->draw();
}

void SolidGrid::render(glm::mat4 transformMatrix)
{
	shader->use();
	glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
	vao->draw();
}

Collider &SolidGrid::provideCollider()
{
	return *(new RectangleCollider(0.0, 0.0, 0.0, 0.0));
}
