#include <src/engine/util/Res.hpp>
#include "SolidPolygon.hpp"

#include <src/engine/physics/RectangleCollider.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <src/engine/physics/PolygonCollider.hpp>

int SolidPolygon::attributes[] = {3, 3};

void SolidPolygon::constructVAO()
{
	GLfloat vertices[6 * points.size()];
	GLuint indices[3 * (points.size() - 2)];

	for(int i = 0; i < points.size(); i++)
	{
		vertices[i * 6] = points[i].first;
		vertices[i * 6 + 1] = points[i].second;
		vertices[i * 6 + 2] = getLayer();
		vertices[i * 6 + 3] = r;
		vertices[i * 6 + 4] = g;
		vertices[i * 6 + 5] = b;
	}

	for(int i = 0; i < points.size() - 2; i++)
	{
		indices[i * 3] = 0;
		indices[i * 3 + 1] = i + 1;
		indices[i * 3 + 2] = i + 2;
	}

	vao = new VAO(vertices, sizeof(vertices), indices, sizeof(indices), attributes, sizeof(attributes) / sizeof(int), GL_STATIC_DRAW);
}

SolidPolygon::SolidPolygon(std::vector<std::pair<float, float>> &points, float r, float g, float b, double layer)
		: points(points)
		, r(r)
		, g(g)
		, b(b)
{
	Renderable::setLayer(layer);
	constructVAO();
	shader = Res::loadShader("res/shader/simple/color");
}

SolidPolygon::~SolidPolygon()
{
	delete vao;
}

void SolidPolygon::setLayer(double layer)
{
	Renderable::setLayer(layer);
	delete vao;
	constructVAO();
}

void SolidPolygon::render()
{
	shader->use();
	vao->draw();
}

void SolidPolygon::render(glm::mat4 transformMatrix)
{
	shader->use();
	glUniformMatrix4fv(shader->getLocation("transform"), 1, GL_FALSE, glm::value_ptr(transformMatrix));
	vao->draw();
}

Collider &SolidPolygon::provideCollider()
{
	return *(new PolygonCollider(points));
}
