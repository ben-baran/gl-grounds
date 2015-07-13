#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Transform::getMatrix()
{
	return (*preposition) * parent->getMatrix() * (*baseOriginalInverse) * base;
}

Transform *Transform::rotate(double theta)
{
	base = glm::rotate(base, theta, glm::vec3(0, 0, 1));
	return this;
}

Transform *Transform::scale(double scaleX, double scaleY)
{
	base = glm::scale(base, glm::vec3(scaleX, scaleY, 1));
	return this;
}

Transform *Transform::translate(double dx, double dy)
{
	base = glm::translate(base, glm::vec3(dx, dy, 0));
	return this;
}

Transform *Transform::multiply(Transform *other)
{
	base = glm::matrixCompMult(base, other->base);
	return this;
}

void Transform::attach(Transform *parent)
{
	this->parent = parent;
	preposition = new glm::mat4(glm::matrixCompMult(base, glm::inverse(parent->getMatrix())));
	baseOriginalInverse = new glm::mat4(glm::inverse(base));
}

Transform *Transform::multiply(Transform *a, Transform *b)
{
	return glm::matrixCompMult(a, b);
}
