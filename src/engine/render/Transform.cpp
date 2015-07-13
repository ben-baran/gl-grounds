#include "Transform.hpp"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 &Transform::getMatrix()
{
	if(!attached) return base;
	if(changed) computed = preposition * parent->getMatrix() * baseOriginalInverse * base;
	changed = false;
	return computed;
}

Transform &Transform::rotate(float theta)
{
	changed = true;
	base = glm::rotate(base, theta, glm::vec3(0, 0, 1));
	return *this;
}

Transform &Transform::scale(double scaleX, double scaleY)
{
	changed = true;
	base = glm::scale(base, glm::vec3(scaleX, scaleY, 1));
	return *this;
}

Transform &Transform::translate(double dx, double dy)
{
	changed = true;
	base = glm::translate(base, glm::vec3(dx, dy, 0));
	return *this;
}

void Transform::attach(Transform *parent)
{
	attached = true;
	this->parent = parent;
	preposition = glm::matrixCompMult(base, glm::inverse(parent->getMatrix()));
	baseOriginalInverse = glm::inverse(base);
}

void Transform::unattach()
{
	attached = false;
}